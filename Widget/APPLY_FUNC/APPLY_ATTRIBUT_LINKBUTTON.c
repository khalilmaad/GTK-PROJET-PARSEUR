#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_linkbutton(Widget* obj)
{
    GtkLinkButton* linkbutton = GTK_LINK_BUTTON(obj->Widget_Ptr);

    const char* label = get_attribut("label", obj);
    if (label != NULL)
    {
        gtk_link_button_set_label(linkbutton, label);
    }


    const char* url = get_attribut("url", obj);
    if (url != NULL)
    {
        gtk_link_button_set_uri(linkbutton, url);
    }
}
