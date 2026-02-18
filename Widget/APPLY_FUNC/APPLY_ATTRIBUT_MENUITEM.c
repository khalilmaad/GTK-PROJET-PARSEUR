#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_menuitem(Widget* obj)
{
    GtkMenuItem* menuitem = GTK_MENU_ITEM(obj->Widget_Ptr);

    // Label
    const char* label = get_attribut("label",obj);
    if (label)
    {
        gtk_menu_item_set_label(menuitem, label);
    }
}
