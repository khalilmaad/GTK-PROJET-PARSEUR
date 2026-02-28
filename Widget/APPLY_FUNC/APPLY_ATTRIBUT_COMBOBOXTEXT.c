#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_comboboxtext(Widget* obj)
{
    GtkComboBoxText* combobox = GTK_COMBO_BOX_TEXT(obj->Widget_Ptr);

    const char* selection = get_attribut("selection", obj);
    if (selection != NULL)
    {
        gtk_combo_box_set_active(combobox, atoi(selection));
    }
}
