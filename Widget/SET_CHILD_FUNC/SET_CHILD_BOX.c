#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"



void set_child_box(Widget* pere,Widget* fils)
{
    if(!Controle_parente(pere,fils)) return;

    _Bool Expand = FALSE;
    _Bool Fill = FALSE;
    int padding = 0;

    // Expansion
    const char* etendre = get_attribut("etendre",fils);
    if (etendre)
    {
        Expand = to_bool(etendre);
    }

    // Remplissage
    const char* remplir = get_attribut("remplir",fils);
    if (remplir)
    {
        Fill = to_bool(remplir);
    }

    //Marge intérieure
    const char* marge = get_attribut("marge",fils);
    if (marge)
    {
        padding = atoi(marge);
    }

    const char* insert_cote = get_attribut("insert_cote",fils);
    if (insert_cote)
    {
        if(!compare(insert_cote,"gauche") || !compare(insert_cote,"haut"))
        {
            gtk_box_pack_start(GTK_BOX(pere->Widget_Ptr), fils->Widget_Ptr,Expand,Fill,padding);
        }
        else if(!compare(insert_cote,"droite") || !compare(insert_cote,"bas"))
        {
            gtk_box_pack_end(GTK_BOX(pere->Widget_Ptr), fils->Widget_Ptr,Expand,Fill,padding);
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
