#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"


void set_child_flowbox( Widget* pere,Widget* fils)
{
    if(!Controle_parente(pere,fils)) return;

    gtk_flow_box_insert(GTK_FLOW_BOX(pere->Widget_Ptr),fils->Widget_Ptr,-1);
    print_succes_liaison(pere->Nom);
}
