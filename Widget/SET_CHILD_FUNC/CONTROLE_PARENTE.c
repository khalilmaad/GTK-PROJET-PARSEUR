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
            print_succes_liaison_signal(pere->Nom);
            fils->Widget_Ptr = pere->Widget_Ptr;
            return FALSE;
        }
    }
    print_error_liaison(pere->Nom);
    print_error_mapping_liaison(pere,fils);
    return FALSE;
}
