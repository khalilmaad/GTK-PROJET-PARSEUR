#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_toolitem(Widget* obj)
{
    GtkToolItem* toolitem = GTK_TOOL_BUTTON(obj->Widget_Ptr);

    // Label
    const char* label = get_attribut("label", obj);
    if (label != NULL)
    {
        gtk_tool_button_set_label(toolitem, label);
    }

    const char* icone = get_attribut("icone", obj);
    if (icone != NULL)
    {
        GtkWidget *image;
        image = gtk_image_new_from_icon_name(icone,
                                             GTK_ICON_SIZE_LARGE_TOOLBAR);

        gtk_tool_button_set_icon_widget(toolitem, image);
        gtk_widget_show(image);  // important
    }
}
