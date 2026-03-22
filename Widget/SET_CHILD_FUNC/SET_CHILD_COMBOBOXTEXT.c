#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"


void set_child_comboboxtext(Widget* pere,Widget* fils)
{
    if(!Controle_parente(pere,fils)) return;

    const char* texte = get_attribut("texte",fils);
    if (texte)
    {
        pere->apply_attribut_func(pere);
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(pere->Widget_Ptr), texte);
    }
    else
    {
        print_error_liaison(pere->Nom);
        print_message_error_liaison("(texte=\"valeur\")");
    }
    print_succes_liaison(pere->Nom);
}

