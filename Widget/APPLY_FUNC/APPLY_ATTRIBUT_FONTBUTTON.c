#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_fontbutton(Widget* obj)
{
    GtkFontButton* fontbutton = GTK_FONT_BUTTON(obj->Widget_Ptr);

    // Label
    const char* label = get_attribut("label", obj);
    if (label != NULL)
    {
        gtk_font_button_set_preview_text(fontbutton, label);
    }


    const char* titre = get_attribut("titre", obj);
    if (titre != NULL)
    {
        gtk_font_button_set_title(fontbutton, titre);
    }
}
