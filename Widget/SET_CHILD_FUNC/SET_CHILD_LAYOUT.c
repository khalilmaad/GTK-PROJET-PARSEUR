#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"



void set_child_layout(Widget* pere,Widget* fils)
{
    if(!Controle_parente(pere,fils)) return;


    const char* pos_x = get_attribut("pos_x",fils);
    const char* pos_y = get_attribut("pos_y",fils);

    if (pos_x && pos_y)
    {

        gtk_layout_put(GTK_LAYOUT(pere->Widget_Ptr), fils->Widget_Ptr,atoi(pos_x),atoi(pos_y));
    }
    else
    {
        printf("\n\033[1;31m[Liaison]\033[0m Liaison au parent \033[1;34m%s\033[0m",pere->Nom);
        printf("\n\033[1;34mMessage : \033[1;31mEchec liaison au parente -> manque attribut indiquant la position d'insertion exemple (pos_x=\"0\" pos_y=\"0\")");
        exit(1);
    }

    printf("\n\033[1;32m[Liaison]\033[0m Liaison au parent \033[1;34m%s\033[0m",pere->Nom);
}
