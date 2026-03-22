#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"


void set_child_default( Widget* pere,Widget* fils)
{
    if(!Controle_parente(pere,fils)) return;

    gtk_container_add(GTK_CONTAINER(pere->Widget_Ptr),fils->Widget_Ptr);
    print_succes_liaison(pere->Nom);
}
