#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"


void set_child_overlay( Widget* pere,Widget* fils)
{
    if(!Controle_parente(pere,fils)) return;

    gtk_overlay_add_overlay(GTK_OVERLAY(pere->Widget_Ptr),fils->Widget_Ptr);
    print_succes_liaison(pere->Nom);
}
