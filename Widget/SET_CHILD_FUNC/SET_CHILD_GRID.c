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
        width = string_to_long("nombre_colonne",nombre_colonne);
    }

    // Remplissage
    const char* nombre_ligne = get_attribut("nombre_ligne",fils);
    if (nombre_ligne)
    {
        height = string_to_long("nombre_ligne",nombre_ligne);
    }

    const char* pos_colonne = get_attribut("pos_colonne",fils);
    const char* pos_ligne = get_attribut("pos_ligne",fils);

    if (pos_colonne && pos_ligne)
    {

        gtk_grid_attach(GTK_GRID(pere->Widget_Ptr), fils->Widget_Ptr,string_to_long("pos_colonne",pos_colonne),string_to_long("pos_ligne",pos_ligne),width,height);
    }
    else
    {
        print_error_liaison(pere->Nom);
        print_message_error_liaison("(pos_colonne=\"0\" pos_ligne=\"0\")");
    }

    print_succes_liaison(pere->Nom);
}
