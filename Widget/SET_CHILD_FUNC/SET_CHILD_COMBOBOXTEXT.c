#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"


void set_child_comboboxtext(Widget* pere,Widget* fils)
{
    if(!Controle_parente(pere,fils)) return;

    const char* texte = get_attribut("texte",fils);
    if (texte)
    {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(pere->Widget_Ptr), texte);
    }
    else
    {
        printf("\n\033[1;31m[Liaison]\033[0m Liaison au parent \033[1;34m%s\033[0m",pere->Nom);
        printf("\n\033[1;34mMessage : \033[1;31mEchec liaison au parente -> manque attribut indiquant cote d'insertion (insert_cote=gauche/droite)");
        exit(1);
    }
    printf("\n\033[1;32m[Liaison]\033[0m Liaison au parent \033[1;34m%s\033[0m",pere->Nom);
}

