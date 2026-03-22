#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"


void set_child_menubar( Widget* pere,Widget* fils)
{
    if(!Controle_parente(pere,fils)) return;

    gtk_menu_shell_append(GTK_MENU_SHELL(pere->Widget_Ptr),fils->Widget_Ptr);
    print_succes_liaison(pere->Nom);
}
