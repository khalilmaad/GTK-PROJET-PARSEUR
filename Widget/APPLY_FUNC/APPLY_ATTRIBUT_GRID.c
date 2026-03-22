#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"

void apply_attribut_grid(Widget* obj)
{
    GtkGrid* grid = GTK_GRID(obj->Widget_Ptr);

    // Espacement entre enfants
    const char* espacement_colonne_str = get_attribut("espacement_colonne", obj);
    if (espacement_colonne_str != NULL)
    {
        long espacement_colonne = string_to_long("espacement_colonne",espacement_colonne_str);

        if (espacement_colonne >= 0)
        {
            gtk_grid_set_column_spacing(grid, espacement_colonne);
        }
    }

    const char* espacement_ligne_str = get_attribut("espacement_ligne", obj);
    if (espacement_ligne_str != NULL)
    {
        long espacement_ligne = string_to_long("espacement_ligne",espacement_ligne_str);

        if (espacement_ligne >= 0)
        {
            gtk_grid_set_row_spacing(grid, espacement_ligne);
        }
    }

    const char* homogeneite_colonne = get_attribut("homogeneite_colonne", obj);
    if (homogeneite_colonne != NULL)
    {
        gtk_grid_set_column_homogeneous(grid, to_bool(homogeneite_colonne));
    }

    const char* homogeneite_ligne = get_attribut("homogeneite_ligne", obj);
    if (homogeneite_ligne != NULL)
    {
        gtk_grid_set_row_homogeneous(grid, to_bool(homogeneite_ligne));
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
}
