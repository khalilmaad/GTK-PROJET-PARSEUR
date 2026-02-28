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
            printf("\n\033[1;31m[Liaison]\033[0m Liaison au parent \033[1;34m%s\033[0m",pere->Nom);
            printf("\n\033[1;34mMessage : \033[1;31mEchec liaison au parente -> (\033[1;34minsert_cote=%s\033[1;31m) valeur incoorect (\033[0m",insert_cote);
            exit(1);
        }
    }
    else
    {
        printf("\n\033[1;31m[Liaison]\033[0m Liaison au parent \033[1;34m%s\033[0m",pere->Nom);
        printf("\n\033[1;34mMessage : \033[1;31mEchec liaison au parente -> manque attribut indiquant cote d'insertion (insert_cote=gauche/droite)");
        exit(1);
    }
    printf("\n\033[1;32m[Liaison]\033[0m Liaison au parent \033[1;34m%s\033[0m",pere->Nom);
}

