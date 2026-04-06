#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"
#include "../../Simulation/SIMULATION.h"



void apply_attribut_simulation(Widget* obj)
{
    const char* skeleton_img_str = get_attribut("skeleton_img",obj);

    skeleton_img = gdk_pixbuf_new_from_file(skeleton_img_str, NULL);

    new_sim = obj;

    if(old_sim)
    {
        old_sim->fils = obj;
    }
    else
    {
        old_sim = obj;
    }

}
