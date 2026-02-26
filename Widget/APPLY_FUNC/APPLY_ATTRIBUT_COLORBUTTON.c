#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_colorbutton(Widget* obj)
{
    GtkColorButton* colorbutton = GTK_COLOR_BUTTON(obj->Widget_Ptr);

    const char* titre = get_attribut("titre", obj);
    if (titre != NULL)
    {
        gtk_color_button_set_title(GTK_COLOR_BUTTON(colorbutton),titre);
    }

    const char* couleur = get_attribut("couleur", obj);
    if (couleur != NULL)
    {
        GdkRGBA color;

        gdk_rgba_parse(&color, couleur);
        gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(colorbutton), &color);
    }


    const char* transparence = get_attribut("transparence", obj);
    if (transparence != NULL)
    {
        gtk_color_chooser_set_use_alpha(GTK_COLOR_CHOOSER(colorbutton), to_bool(transparence));
    }


}
