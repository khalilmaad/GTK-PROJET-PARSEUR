#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"


void set_child_searchbar( Widget* pere,Widget* fils)
{
    if(!Controle_parente(pere,fils)) return;

    gtk_container_add(GTK_CONTAINER(pere->Widget_Ptr),fils->Widget_Ptr);
    gtk_search_bar_connect_entry(GTK_SEARCH_BAR(pere->Widget_Ptr),GTK_ENTRY(fils->Widget_Ptr));
    print_succes_liaison(pere->Nom);
}
