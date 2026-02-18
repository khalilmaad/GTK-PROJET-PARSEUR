#ifndef APPGTK_H_INCLUDED
#define APPGTK_H_INCLUDED

#include <gtk/gtk.h>
#include <pthread.h>

typedef struct wd Widget;

typedef struct appgtk
{
    GtkWidget* FenetreChargement;
    Widget* arbre_widget;
    char* nomfichier;

    void (*debut_chargement)(struct appgtk*);
    void (*parsing)(struct appgtk*,const char*);
    void (*boucle)(void);
    void (*afficher_interface)(Widget*);
}AppGTK;


AppGTK* init_APP(int argc, char* argv[]);
void AppGTK_debut_chargement(AppGTK*);
void AppGTK_fin_chargement(gpointer data);
void AppGTK_Resultat_Parsing(AppGTK*,const char*);
void AppGTK_boucle();


#endif // APPGTK_H_INCLUDED
