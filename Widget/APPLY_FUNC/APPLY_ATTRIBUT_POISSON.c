#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"
#include "../../Simulation/SIMULATION.h"


void apply_attribut_poisson(Widget* obj)
{
    const char* pos_auto_str = get_attribut("pos_aleatoire",obj);
    const char* x_str = get_attribut("x",obj);
    const char* y_str = get_attribut("y",obj);
    const char* icone_espece = get_attribut("icone_espece",obj);
    const char* predator_str = get_attribut("predator",obj);

    _Bool pos_auto = to_bool(pos_auto_str);
    int x = string_to_long("x",x_str);
    int y = string_to_long("y",y_str);


    if(!to_bool(predator_str))
    {
        init_fish(obj,pos_auto,x,y,icone_espece);
    }
    else
    {
        init_predator(obj,pos_auto,x,y,icone_espece);
    }
}
