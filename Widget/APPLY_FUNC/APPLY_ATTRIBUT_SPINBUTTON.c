#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_spinbutton(Widget* obj)
{
    GtkSpinButton* spinbutton = GTK_SPIN_BUTTON(obj->Widget_Ptr);

    const char* min = get_attribut("min", obj);
    const char* max = get_attribut("max", obj);
    if (max && min)
    {
        gtk_spin_button_set_range(spinbutton,atof(min),atof(max));
    }

    const char* step = get_attribut("step", obj);
    const char* page_increment = get_attribut("page_increment", obj);
    if (step && page_increment)
    {
        gtk_spin_button_set_increments(spinbutton,atof(step),atof(page_increment));
    }

    const char* only_numeric = get_attribut("only_numeric", obj);
    if (only_numeric != NULL)
    {
        gtk_spin_button_set_numeric(spinbutton, to_bool(only_numeric));
    }

    const char* value = get_attribut("value", obj);
    if (value != NULL)
    {
        gtk_spin_button_set_value(spinbutton, atof(value));
    }
}
