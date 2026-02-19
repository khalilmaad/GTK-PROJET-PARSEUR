#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_expander(Widget* obj)
{
    GtkExpander* expander = GTK_EXPANDER(obj->Widget_Ptr);

    // Label
    const char* label = get_attribut("label", obj);
    if (label != NULL)
    {
        gtk_expander_set_label(expander, label);
    }
}
