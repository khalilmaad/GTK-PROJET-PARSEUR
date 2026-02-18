#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"


_Bool Controle_parente( Widget* pere, Widget* fils)
{
    for(int ind = 0; ind < pere->Nbre_enfant; ind++)
    {
        if(!compare(pere->List_widget_enfant[ind],fils->Nom)){
            if(compare(fils->Nom,"signal") != 0)
            {
                return TRUE;
            }
            printf("\n\033[1;32m[Liaison signal]\033[0m source \033[1;34m%s\033[0m",pere->Nom);
            fils->Widget_Ptr = pere->Widget_Ptr;
            return FALSE;
        }
    }
    printf("\n\033[1;31m[Liaison]\033[0m Liaison au parent \033[1;34m%s\033[0m",pere->Nom);
    printf("\n\033[1;34mMessage : \033[1;31mEchec au controle de parente -> (\033[1;34m%s\033[1;31m) ne prend pas (\033[1;34m%s\033[1;31m)"
           "\n\n\033[0mNom widget prise en charge: ",pere->Nom,fils->Nom);

    for(int i=0; i < pere->Nbre_enfant; i++)
    {
        printf("\n->\033[1;34m%s\033[0m,",pere->List_widget_enfant[i]);
    }
    printf("\n");
    exit(1);
}
