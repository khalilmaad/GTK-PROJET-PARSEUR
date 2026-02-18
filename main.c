/*#include "AppGTK/AppGTK.h"


int main(int argc, char* argv[])
{
    AppGTK* monAPP = init_APP(argc,argv);

    monAPP->debut_chargement(monAPP);
    monAPP->parsing(monAPP,"fichier_test.txt");
    monAPP->afficher_interface(monAPP->arbre_widget);
    monAPP->boucle();

    return 0;
}*/


#include <gtk/gtk.h>

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *stack;
    GtkWidget *switcher;

    /* Création de la fenêtre */
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Exemple GtkStack");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    /* Boîte verticale */
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    /* Création du stack */
    stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack),
                                   GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
    gtk_stack_set_transition_duration(GTK_STACK(stack), 500);

    /* Création des pages */
    GtkWidget *label1 = gtk_label_new("Bienvenue sur la page 1");
    GtkWidget *label2 = gtk_label_new("Ceci est la page 2");
    GtkWidget *label3 = gtk_label_new("Voici la page 3");

    /* Ajout des pages avec titre */
    gtk_stack_add_titled(GTK_STACK(stack), label1, "page1", "Accueil");
    gtk_stack_add_titled(GTK_STACK(stack), label2, "page2", "Profil");
    gtk_stack_add_titled(GTK_STACK(stack), label3, "page3", "Paramètres");

    /* Création du switcher */
    switcher = gtk_stack_switcher_new();
    gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(switcher),
                                  GTK_STACK(stack));

    /* Ajout au layout */
    gtk_box_pack_start(GTK_BOX(vbox), switcher, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), stack, TRUE, TRUE, 5);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.gtkstack", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
