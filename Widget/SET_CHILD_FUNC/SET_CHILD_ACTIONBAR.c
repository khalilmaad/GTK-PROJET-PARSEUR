#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"


void set_child_actionbar(Widget* pere,Widget* fils)
{
    if(!Controle_parente(pere,fils)) return;

    const char* insert_cote = get_attribut("insert_cote",fils);
    if (insert_cote)
    {
        if(!compare(insert_cote,"gauche"))
        {
            gtk_action_bar_pack_start(GTK_ACTION_BAR(pere->Widget_Ptr), fils->Widget_Ptr);
        }
        else if(!compare(insert_cote,"droite"))
        {
            gtk_action_bar_pack_end(GTK_ACTION_BAR(pere->Widget_Ptr), fils->Widget_Ptr);
        }
        else
        {
            print_error_liaison(pere->Nom);
            print_message_error_liaison("(valeur de insert_cote=gauche/droite)");
        }
    }
    else
    {
        print_error_liaison(pere->Nom);
        print_message_error_liaison("(insert_cote=gauche/droite)");
    }
    print_succes_liaison(pere->Nom);
}

