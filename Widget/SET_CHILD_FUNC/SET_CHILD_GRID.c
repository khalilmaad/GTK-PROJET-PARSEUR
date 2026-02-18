#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"



void set_child_grid(Widget* pere,Widget* fils)
{
    if(!Controle_parente(pere,fils)) return;

    int width  = 1;
    int height  = 1;

    // Expansion
    const char* nombre_colonne = get_attribut("nombre_colonne",fils);
    if (nombre_colonne)
    {
        width = atoi(nombre_colonne);
    }

    // Remplissage
    const char* nombre_ligne = get_attribut("nombre_ligne",fils);
    if (nombre_ligne)
    {
        height = atoi(nombre_ligne);
    }

    const char* pos_colonne = get_attribut("pos_colonne",fils);
    const char* pos_ligne = get_attribut("pos_ligne",fils);

    if (pos_colonne && pos_ligne)
    {

        gtk_grid_attach(GTK_GRID(pere->Widget_Ptr), fils->Widget_Ptr,atoi(pos_colonne),atoi(pos_ligne),width,height);
    }
    else
    {
        printf("\n\033[1;31m[Liaison]\033[0m Liaison au parent \033[1;34m%s\033[0m",pere->Nom);
        printf("\n\033[1;34mMessage : \033[1;31mEchec liaison au parente -> manque attribut indiquant la position d'insertion exemple (pos_colonne=\"0\" pos_ligne=\"0\")");
        exit(1);
    }

    printf("\n\033[1;32m[Liaison]\033[0m Liaison au parent \033[1;34m%s\033[0m",pere->Nom);
}
