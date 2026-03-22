#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"



void set_child_fixed(Widget* pere,Widget* fils)
{
    if(!Controle_parente(pere,fils)) return;


    const char* pos_x = get_attribut("pos_x",fils);
    const char* pos_y = get_attribut("pos_y",fils);

    if (pos_x && pos_y)
    {

        gtk_fixed_put(GTK_FIXED(pere->Widget_Ptr), fils->Widget_Ptr,string_to_long("pos_x",pos_x),string_to_long("pos_y",pos_y));
    }
    else
    {
        print_error_liaison(pere->Nom);
        print_message_error_liaison("(pos_x=\"0\" pos_y=\"0\")");
    }

    print_succes_liaison(pere->Nom);
}
