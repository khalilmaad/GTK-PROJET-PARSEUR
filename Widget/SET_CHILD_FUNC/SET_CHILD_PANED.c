#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"



void set_child_paned(Widget* pere,Widget* fils)
{
    if(!Controle_parente(pere,fils)) return;

    const char* insert_cote = get_attribut("insert_cote",fils);
    if (insert_cote)
    {
        if(!compare(insert_cote,"gauche") || !compare(insert_cote,"haut"))
        {
            gtk_paned_add1(GTK_PANED(pere->Widget_Ptr), fils->Widget_Ptr);
        }
        else if(!compare(insert_cote,"droite") || !compare(insert_cote,"bas"))
        {
            gtk_paned_add2(GTK_PANED(pere->Widget_Ptr), fils->Widget_Ptr);
        }
        else
        {
            print_error_liaison(pere->Nom);
            print_message_error_liaison("(valeur de insert_cote=gauche/droite/haut/bas)");
        }
    }
    else
    {
        print_error_liaison(pere->Nom);
        print_message_error_liaison("(insert_cote=gauche/droite/haut/bas)");
    }

    print_succes_liaison(pere->Nom);
}
