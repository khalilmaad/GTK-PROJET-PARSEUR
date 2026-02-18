#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"

void apply_attribut_checkbutton(Widget* obj)
{
    GtkCheckButton* checkbutton = GTK_CHECK_BUTTON(obj->Widget_Ptr);

    // Label
    const char* label = get_attribut("label", obj);
    if (label != NULL)
    {
        gtk_button_set_label(GTK_BUTTON(checkbutton), label);
    }

    // Utiliser mnémonique (raccourci clavier)
    const char* use_underline = get_attribut("use_underline", obj);
    if (use_underline != NULL)
    {
        gtk_button_set_use_underline(GTK_BUTTON(checkbutton), to_bool(use_underline));
    }

    // Définir l'état (coché/décoché)
    const char* etat_coche = get_attribut("etat_coche", obj);
    if (etat_coche != NULL)
    {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), to_bool(etat_coche));
    }

    // CheckButton désactivé (inactif)
    const char* active = get_attribut("active", obj);
    if (active != NULL)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(checkbutton), to_bool(active));
    }
}
