#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"

void apply_attribut_checkmenuitem(Widget* obj)
{
    GtkCheckMenuItem* check = GTK_CHECK_MENU_ITEM(obj->Widget_Ptr);

    // Label
    const char* label = get_attribut("label", obj);
    if (label != NULL)
    {
        gtk_menu_item_set_label(GTK_MENU_ITEM(check), label);
    }

    // Utiliser mnémonique (raccourci clavier)
    const char* use_underline = get_attribut("use_underline", obj);
    if (use_underline != NULL)
    {
        gtk_button_set_use_underline(GTK_BUTTON(check), to_bool(use_underline));
    }

    // Définir l'état (coché/décoché)
    const char* etat_coche = get_attribut("etat_coche", obj);
    if (etat_coche != NULL)
    {
        gtk_check_menu_item_set_active(check, to_bool(etat_coche));
    }

    // CheckButton désactivé (inactif)
    const char* active = get_attribut("active", obj);
    if (active != NULL)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(check), to_bool(active));
    }
}
