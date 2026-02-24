#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_switch(Widget* obj)
{
    GtkSwitch* Switch = GTK_SWITCH(obj->Widget_Ptr);

    const char* active = get_attribut("active", obj);
    if (active != NULL)
    {
        gtk_switch_set_active(Switch, to_bool(active));
    }
}
