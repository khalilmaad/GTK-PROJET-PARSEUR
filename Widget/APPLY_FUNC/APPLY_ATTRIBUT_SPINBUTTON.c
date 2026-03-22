#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_spinbutton(Widget* obj)
{
    GtkSpinButton* spinbutton = GTK_SPIN_BUTTON(obj->Widget_Ptr);

    const char* min = get_attribut("min", obj);
    const char* max = get_attribut("max", obj);
    if (max && min)
    {
        gtk_spin_button_set_range(spinbutton,string_to_double("min",min),string_to_double("max",max));
    }

    const char* step = get_attribut("step", obj);
    const char* page_increment = get_attribut("page_increment", obj);
    if (step && page_increment)
    {
        gtk_spin_button_set_increments(spinbutton,string_to_double("step",step),string_to_double("page_increment",page_increment));
    }

    const char* only_numeric = get_attribut("only_numeric", obj);
    if (only_numeric != NULL)
    {
        gtk_spin_button_set_numeric(spinbutton, to_bool(only_numeric));
    }

    const char* value = get_attribut("value", obj);
    if (value != NULL)
    {
        gtk_spin_button_set_value(spinbutton, string_to_double("value",value));
    }

    const char* couleur_fond = get_attribut("couleur_fond", obj);
    if (couleur_fond != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-background-color",couleur_fond);
    }

    const char* coin_arrondi = get_attribut("coin_arrondi", obj);
    if (coin_arrondi != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-border-radius",coin_arrondi);
    }

    const char* margin = get_attribut("margin", obj);
    if (margin != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-margin",margin);
    }

    const char* margin_top = get_attribut("margin_top", obj);
    if (margin_top != NULL)
    {
        gtk_widget_set_margin_top(obj->Widget_Ptr,string_to_long("margin_top",margin_top));
    }

    const char* margin_bottom = get_attribut("margin_bottom", obj);
    if (margin_bottom != NULL)
    {
        gtk_widget_set_margin_bottom(obj->Widget_Ptr,string_to_long("margin_bottom",margin_bottom));
    }

    const char* margin_left = get_attribut("margin_left", obj);
    if (margin_left != NULL)
    {
        gtk_widget_set_margin_start(obj->Widget_Ptr,string_to_long("margin_left",margin_left));
    }

    const char* margin_right = get_attribut("margin_right", obj);
    if (margin_right != NULL)
    {
        gtk_widget_set_margin_end(obj->Widget_Ptr,string_to_long("margin_right",margin_right));
    }

    const char* bordure = get_attribut("bordure", obj);
    if (bordure != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-border",bordure);
    }

    const char* box_shadow = get_attribut("box_shadow", obj);
    if (bordure != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-box-shadow",box_shadow);
    }

    const char* couleur_label = get_attribut("couleur_label", obj);
    if (couleur_label != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-color",couleur_label);
    }

    const char* font_weight = get_attribut("font_weight", obj);
    if (font_weight != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-font-weight",font_weight);
    }

    const char* font_size = get_attribut("font_size", obj);
    if (font_size != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-font-size",font_size);
    }

    const char* font_family = get_attribut("font_family", obj);
    if (font_family != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-font-family",font_family);
    }
}
