#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"


void set_child_menuitem( Widget* pere,Widget* fils)
{
    if(!Controle_parente(pere,fils)) return;

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(pere->Widget_Ptr),fils->Widget_Ptr);
    printf("\n\033[1;32m[Liaison]\033[0m Liaison au parent \033[1;34m%s\033[0m",pere->Nom);
}
