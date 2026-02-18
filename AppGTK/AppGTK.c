#include "AppGTK.h"
#include "../ParserXML/ParseXML.h"
#include "../Widget/GENERAL/Widget.h"

void AppGTK_afficher_interface(Widget* arb)
{
    if(arb) gtk_widget_show_all(arb->Widget_Ptr);
    if(arb->frere) AppGTK_afficher_interface(arb->frere);
}

void AppGTK_boucle(){ gtk_main(); }

AppGTK* init_APP(int argc, char* argv[])
{
    gtk_init(&argc, &argv);

    AppGTK* monAPP = (AppGTK*)malloc(sizeof(AppGTK));
    if(!monAPP)
    {
        printf("init_APP | erreur initialisation du projet\n");
        exit(1);
    }
    monAPP->arbre_widget = NULL;
    monAPP->debut_chargement = AppGTK_debut_chargement;
    monAPP->nomfichier = NULL;
    monAPP->FenetreChargement = NULL;
    monAPP->parsing = AppGTK_Resultat_Parsing;
    monAPP->boucle = AppGTK_boucle;
    monAPP->afficher_interface = AppGTK_afficher_interface;

    return monAPP;

}

void AppGTK_debut_chargement(AppGTK* monAPP)
{
    //Fenêtre
    GtkWidget *window = gtk_window_new(GTK_WINDOW_POPUP);
    //gtk_window_set_title(GTK_WINDOW(window), "Chargement");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 250);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    /*GdkRGBA rgba;
    gdk_rgba_parse(&rgba, "white");
    gtk_widget_override_background_color(window, GTK_STATE_FLAG_NORMAL, &rgba);*/

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Box verticale
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), box);

    //Spinner
    GtkWidget *spinner = gtk_spinner_new();
    gtk_box_pack_start(GTK_BOX(box), spinner, TRUE, TRUE, 0);
    gtk_spinner_start(GTK_SPINNER(spinner));

    // Label
    GtkWidget *label = gtk_label_new("Chargement en cours...");
    gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);


    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider,
    "label { font-family: \"Arial\"; font-size: 30px; font-weight: bold; color: grey; }",
    -1, NULL);


    GtkStyleContext *context = gtk_widget_get_style_context(label);
    gtk_style_context_add_provider(context,
        GTK_STYLE_PROVIDER(cssProvider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);



    monAPP->FenetreChargement = window;

    gtk_widget_show_all(window);

    // =============================
    // Force GTK à traiter l'affichage
    while (gtk_events_pending())
        gtk_main_iteration();
    // =============================
}


void AppGTK_fin_chargement(gpointer data)
{
    AppGTK* monAPP = (AppGTK*)data;
    gtk_widget_destroy(monAPP->FenetreChargement);
}



// Fonction exécutée dans le thread
static void* parsing_thread_func(void* data)
{
     AppGTK* monAPP = (AppGTK*)data;

    // Créer le parser et parser le fichier
    ParserXML* monParser = parser_create(monAPP->nomfichier);
    if (monParser != NULL) {
        monParser->parse(monParser);
        monAPP->arbre_widget = monParser->racine;
    }

    // Une fois terminé, fermer la fenêtre de chargement dans le thread GTK principal
    g_idle_add((GSourceFunc)AppGTK_fin_chargement, monAPP);

    return NULL;
}


// Fonction principale
void AppGTK_Resultat_Parsing(AppGTK* monAPP,const char* nomfichier)
{
    pthread_t parsing_thread;
    monAPP->nomfichier = strdup(nomfichier);

    // Créer et lancer le thread
    if (pthread_create(&parsing_thread, NULL, parsing_thread_func, (void*)monAPP) != 0) {
        return;
    }

    // Détacher le thread pour qu'il tourne en arrière-plan
    pthread_detach(parsing_thread);

    // Lancer la boucle GTK
    AppGTK_boucle();

    return;
}
