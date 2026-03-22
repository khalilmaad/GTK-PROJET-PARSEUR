#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"


void set_child_fenetre( Widget* pere, Widget* fils)
{
    if(!Controle_parente(pere,fils)) return;

    if(!compare(fils->Nom,"headerbar"))
    {
        gtk_window_set_titlebar(GTK_WINDOW(pere->Widget_Ptr),fils->Widget_Ptr);
    }
    else{
        gtk_container_add(GTK_CONTAINER(pere->Widget_Ptr),fils->Widget_Ptr);
    }
    print_succes_liaison(pere->Nom);
}
