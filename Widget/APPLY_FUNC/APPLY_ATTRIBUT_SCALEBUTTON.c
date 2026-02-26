#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_scale(Widget* obj)
{
    /*GtkScaleButton* scalebutton = GTK_SCALE_BUTTON(obj->Widget_Ptr);

    // Label
    const char* label = get_attribut("label", obj);
    if (label != NULL)
    {
        gtk_button_set_label(GTK_BUTTON(scalebutton), label);
    }

    const char* icone = get_attribut("icone", obj);
    if (icone != NULL)
    {
        // Icône nommée (thème)
            GtkWidget* image = gtk_image_new_from_icon_name(icone, GTK_ICON_SIZE_BUTTON);
            gtk_button_set_image(GTK_BUTTON(scalebutton), image);
    }

    // Orientation
    const char* orientation = get_attribut("orientation", obj);
    if (orientation != NULL)
    {
        if (strcmp(orientation, "vertical") == 0 || strcmp(orientation, "verticale") == 0)
        {
            gtk_orientable_set_orientation(GTK_ORIENTABLE(scalebutton), GTK_ORIENTATION_VERTICAL);
        }
    }

    const char* min = get_attribut("min", obj);
    if (min)
    {
        GtkAdjustment *adj = gtk_scale_button_get_adjustment(scalebutton);
        gtk_adjustment_set_lower(adj, atof(min));  // nouveau min
        gtk_adjustment_changed(adj);
    }

    const char* max = get_attribut("max", obj);
    if (max)
    {
        GtkAdjustment *adj = gtk_scale_button_get_adjustment(scalebutton);
        gtk_adjustment_set_upper(adj, atof(max)); // nouveau max
        gtk_adjustment_changed(adj);
    }

    const char* step = get_attribut("step", obj);
    const char* page_increment = get_attribut("page_increment", obj);
    if (step && page_increment)
    {
        gtk_scale_button_set_increments(scalebutton,atof(step),atof(page_increment));
    }

    const char* only_numeric = get_attribut("only_numeric", obj);
    if (only_numeric != NULL)
    {
        gtk_spin_button_set_numeric(scalebutton, to_bool(only_numeric));
    }

    const char* value = get_attribut("value", obj);
    if (value != NULL)
    {
        gtk_scale_button_set_value(scalebutton, atof(value));
    }
    */
}
