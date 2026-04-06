#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"


void set_child_simulation( Widget* pere,Widget* fils)
{

    if(!Controle_parente(pere,fils)) return;

    print_succes_liaison(pere->Nom);
}
