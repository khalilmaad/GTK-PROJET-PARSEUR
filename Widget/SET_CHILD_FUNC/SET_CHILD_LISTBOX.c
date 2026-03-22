#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"


void set_child_listbox( Widget* pere,Widget* fils)
{
    if(!Controle_parente(pere,fils)) return;

    gtk_list_box_insert(GTK_LIST_BOX(pere->Widget_Ptr),fils->Widget_Ptr,-1);
    print_succes_liaison(pere->Nom);
}
