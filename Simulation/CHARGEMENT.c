#include "SIMULATION.h"
#include "../ParserXML/ParseXML.h"
#include "../Widget/GENERAL/Widget.h"

void liberer_liste_frere(Widget* tete) {
    while (tete != NULL) {
        Widget* temp = tete;
        tete = tete->frere;  // avancer AVANT de libérer
        free(temp);
    }
}


void liberer_arbre(Widget* racine) {
    if (racine == NULL) return;

    liberer_arbre(racine->fils);   // libérer tous les enfants
    liberer_arbre(racine->frere);  // libérer tous les frères
    free(racine);                  // libérer le nœud lui-même
}

void* Lancer_chargement(void* data)
{
    type_sauvegarde* obj = (type_sauvegarde*)data;

    g_signal_emit_by_name(obj->emetteur_signal_sauvegarde, "debut_recuperation");

    reset_state(NULL,NULL);

    pthread_mutex_lock(&sim_mutex);

    if(old_sim)
    {
        Widget* tmp = old_sim->fils;
        old_sim->fils = NULL;
        liberer_liste_frere(tmp);
    }

    // Remettre fishes et predators à NULL — les threads de libération
    // vont tourner dans le vide car les noeuds sont déjà retirés
    fishes    = NULL;
    predators = NULL;

    pthread_mutex_unlock(&sim_mutex);

    ParserXML* Parseur = parser_create(obj->filename);
    Parseur->parse(Parseur);

    pthread_mutex_lock(&sim_mutex);

    if(old_sim && old_sim->fils)
    {
        old_sim->fils = old_sim->fils->fils;

        g_signal_emit_by_name(obj->emetteur_signal_sauvegarde, "fin_recuperation");

        if(new_sim)
        {
            new_sim->fils = NULL;
            liberer_arbre(Parseur->racine);
        }
    }
    pthread_mutex_unlock(&sim_mutex);

    return NULL;
}

void chargement_simulation(GtkWidget *widget, gpointer data)
{

    type_sauvegarde* obj = malloc(sizeof(type_sauvegarde));
    if(!obj) return;

    obj->emetteur_signal_sauvegarde = widget;
    obj->racine_arbre = NULL;

    GtkFileChooserNative *dialog;
    gint res;

    // Créer la boîte de dialogue
    dialog = gtk_file_chooser_native_new("Enregistrer le fichier",
                                         NULL,
                                         GTK_FILE_CHOOSER_ACTION_OPEN,
                                         "_Lire",
                                         "_Annuler");

    res = gtk_native_dialog_run(GTK_NATIVE_DIALOG(dialog));

    if (res == GTK_RESPONSE_ACCEPT)
    {

        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        obj->filename =strdup(gtk_file_chooser_get_filename(chooser));



        pthread_t parsing_thread;

        // Créer et lancer le thread
        if (pthread_create(&parsing_thread, NULL, Lancer_chargement, (void*)obj) != 0)
        {
            return;
        }

        // Détacher le thread pour qu'il tourne en arrière-plan
        pthread_detach(parsing_thread);
    }

    g_object_unref(dialog);
}
