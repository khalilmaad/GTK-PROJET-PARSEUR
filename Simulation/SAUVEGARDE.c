#include "SIMULATION.h"
#include "../ParserXML/ParseXML.h"
#include "../Widget/GENERAL/Widget.h"



/* Inverse une liste chaînée de frères et retourne le nouveau premier */
Widget* inverser_freres(Widget* tete)
{
    Widget* prev = NULL;
    Widget* curr = tete;
    Widget* next = NULL;

    while (curr != NULL)
    {
        next        = curr->frere;
        curr->frere = prev;
        prev        = curr;
        curr        = next;
    }
    return prev; /* nouveau premier (ancien dernier) */
}

void gererTabulation(FILE* file,guint* nbre)
{
    if(file)
    {
        for (int i = 0; i < *nbre-1; i++)
        {
            fprintf(file,"\t");
            fflush(file);//Pour eviter un depassement de stack si les donnees ecrites sont trops importante en taille

        }
    }
    else
    {
        printf("\nERREUR | gererTabulation\n");
        exit(0);
    }
}


void ecrire_ouvrante(FILE* file,Widget* obj,guint* nbre)
{

    if(obj!=NULL && file)
    {
        gererTabulation(file,nbre);

        fprintf(file,"<%s ",obj->Nom);
        fflush(file);//ecrire directement dans le fichier

        if(obj->Id)
        {
            fprintf(file,"id=\"%s\" ",obj->Id);
            fflush(file);
        }


        for(int i=0; i < obj->Nbre_Attribut ; i++)
        {
            if(!strcmp(obj->List_Attribut[i].Valeur,"")) continue;
            fprintf(file,"%s=\"%s\" ",obj->List_Attribut[i].Nom,obj->List_Attribut[i].Valeur);
            fflush(file);
        }

        for(int i=0; i < obj->Nbre_Attribut_special ; i++)
        {
            if(!strcmp(obj->List_Attribut_special[i].Valeur,"")) continue;
            fprintf(file,"%s=\"%s\" ",obj->List_Attribut_special[i].Nom,obj->List_Attribut_special[i].Valeur);
            fflush(file);
        }

        const char* sible = get_attribut("sible",obj);
        fprintf(file, (obj->fils != NULL && !sible) ? ">\n" : "/>\n");
        fflush(file);
    }
    else
    {
        printf("\nERREUR | ecrire_ouvrante\n");
        exit(0);
    }

}




void ecrire_fermante(FILE* file,Widget* obj,guint* nbre)
{
    if(obj!=NULL && file)
    {
        if(obj->fils != NULL) gererTabulation(file,nbre);

        fprintf(file,"</%s>\n",obj->Nom);
        fflush(file);
    }
    else
    {
        printf("\nERREUR | ecrire_fermante\n");
        exit(0);
    }
}



void ecrire_dans_fichier(FILE* file, Widget* obj, guint* nbre)
{
    if (obj != NULL && file)
    {
        /* ── Inverser la liste des frères pour écrire dans le bon ordre ── */
        Widget* premier = inverser_freres(obj);
        Widget* courant = premier;

        while (courant != NULL)
        {
            *nbre = *nbre + 1;
            if(!strcmp(courant->Nom,"poisson"))
            {
                const char* etat = get_attribut("dead",courant);
                if(etat && to_bool(etat)) goto suivant;
            }
            ecrire_ouvrante(file, courant, nbre);

            suivant:

            const char* sible = get_attribut("sible",courant);
            if (courant->fils && !sible)
            {
                ecrire_dans_fichier(file, courant->fils, nbre);

                ecrire_fermante(file, courant, nbre);
            }

            *nbre = *nbre - 1;
            courant = courant->frere;
        }

        /* ── Remettre la liste dans l'ordre original (non destructif) ── */
        inverser_freres(premier);
    }
}

static void annoncer_fin_sauvegarde(gpointer data)
{
    GtkWidget* emmetteur = (GtkWidget*)data;
    g_signal_emit_by_name(emmetteur, "fin_sauvegarde");
}

void preparer_struct_sauvegarde()
{
    for (List_fishes* crt = fishes; crt; crt = crt->svt)
    {
        Widget* obj = crt->elem->obj_ptr;
        Fish* obj_fish = crt->elem;

        attributs_add(obj,"pos_aleatoire","false");
        attributs_add(obj,"icone_espece",fish_species[obj_fish->species]);

        char bufferX[20];           // espace temporaire
        char bufferY[20];           // espace temporaire

        snprintf(bufferX, sizeof(bufferX), "%d", obj_fish->x);
        snprintf(bufferY, sizeof(bufferY), "%d", obj_fish->y);

        attributs_add(obj,"x",bufferX);
        attributs_add(obj,"y",bufferY);
    }

    for (List_predators* pred_crt = predators; pred_crt; pred_crt = pred_crt->svt)
    {
        Widget* obj = pred_crt->elem->obj_ptr;
        Predator* obj_pred = pred_crt->elem;

        attributs_add(obj,"pos_aleatoire","false");
        attributs_add(obj,"predator","true");
        attributs_add(obj,"icone_espece",fish_species[obj_pred->species]);

        char bufferX[20];           // espace temporaire
        char bufferY[20];           // espace temporaire

        snprintf(bufferX, sizeof(bufferX), "%d", obj_pred->x);
        snprintf(bufferY, sizeof(bufferY), "%d", obj_pred->y);

        attributs_add(obj,"x",bufferX);
        attributs_add(obj,"y",bufferY);
    }
}

void* Enreigistrement_Fichier(void* data)
{
    type_sauvegarde* objets = (type_sauvegarde*)data;
    // Appeler la fonction pour écrire dans le fichier
    guint* nbre=malloc(sizeof(guint));
    *nbre=0;
    FILE *file = fopen(objets->filename, "w");

    printf("\n\n\033[1;32m[backup started] \033[1;34mSauvegarde en cours...\033[0m\n");

    g_signal_emit_by_name(objets->emetteur_signal_sauvegarde, "debut_sauvegarde");

    preparer_struct_sauvegarde();

    ecrire_dans_fichier(file, objets->racine_arbre,nbre);

    printf("\n\033[1;32m[backup completed successfully] \033[1;34mSauvergarde terminee avec succes\033[0m\n\n");
    fclose(file);
    free(nbre);

    // Une fois terminé, emmettre un signal de fin
    g_idle_add((GSourceFunc)annoncer_fin_sauvegarde, objets->emetteur_signal_sauvegarde);

    return NULL;
}





// Fonction qui ouvre la boîte de dialogue et enregistre le fichier
void save_file(GtkWidget *widget, gpointer data)
{

    Widget* objets = (Widget*)data; // Récupérer la structure passée
    if(objets==NULL && !objets->fils)
    {
        printf("\nerreur\n");
        return;
        //exit(0);
    }

    type_sauvegarde* obj = malloc(sizeof(type_sauvegarde));
    if(!obj) return;

    obj->emetteur_signal_sauvegarde = widget;
    obj->racine_arbre = objets->fils;

    GtkFileChooserNative *dialog;
    gint res;

    // Créer la boîte de dialogue
    dialog = gtk_file_chooser_native_new("Enregistrer le fichier",
                                         NULL,
                                         GTK_FILE_CHOOSER_ACTION_SAVE,
                                         "_Enregistrer",
                                         "_Annuler");

    // Proposer un nom de fichier par défaut
    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), "nouveau_fichier.txt");

    res = gtk_native_dialog_run(GTK_NATIVE_DIALOG(dialog));

    if (res == GTK_RESPONSE_ACCEPT)
    {

        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        obj->filename =strdup(gtk_file_chooser_get_filename(chooser));



        pthread_t parsing_thread;

        // Créer et lancer le thread
        if (pthread_create(&parsing_thread, NULL, Enreigistrement_Fichier, (void*)obj) != 0)
        {
            return;
        }

        // Détacher le thread pour qu'il tourne en arrière-plan
        pthread_detach(parsing_thread);
    }

    g_object_unref(dialog);
}





