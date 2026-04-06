#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"
#include "../../Simulation/SIMULATION.h"


void set_child_drawingarea( Widget* pere,Widget* fils)
{

    if(!Controle_parente(pere,fils)) return;

    g_timeout_add(16, tick, NULL);
    print_succes_liaison(pere->Nom);
}
