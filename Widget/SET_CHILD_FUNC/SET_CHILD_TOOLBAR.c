#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"


void set_child_toolbar( Widget* pere,Widget* fils)
{
    if(!Controle_parente(pere,fils)) return;

    gtk_toolbar_insert(GTK_TOOLBAR(pere->Widget_Ptr),GTK_TOOL_ITEM(fils->Widget_Ptr),-1);
    print_succes_liaison(pere->Nom);
}
