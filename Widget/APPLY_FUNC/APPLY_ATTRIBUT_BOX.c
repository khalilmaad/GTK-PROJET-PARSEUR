#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"

void apply_attribut_box(Widget* obj)
{
    GtkBox* box = GTK_BOX(obj->Widget_Ptr);

    // Orientation
    const char* orientation = get_attribut("orientation", obj);
    if (orientation != NULL)
    {
        if (strcmp(orientation, "vertical") == 0 || strcmp(orientation, "verticale") == 0)
        {
            gtk_orientable_set_orientation(GTK_ORIENTABLE(box), GTK_ORIENTATION_VERTICAL);
        }
    }

    // Espacement entre enfants
    const char* espacement_enfant_str = get_attribut("espacement_enfant", obj);
    if (espacement_enfant_str != NULL)
    {
        long espacement_enfant = string_to_long("espacement_enfant",espacement_enfant_str);

        if (espacement_enfant >= 0)
        {
            gtk_box_set_spacing(box, espacement_enfant);
        }
        else
        {
            gtk_box_set_spacing(box, 10);
        }
    }

    // Homogénéité (tous les enfants ont même taille)
    const char* Homogeneite = get_attribut("homogeneite", obj);
    if (Homogeneite != NULL)
    {
        gtk_box_set_homogeneous(box, to_bool(Homogeneite));
    }

    // Baseline position (pour alignement vertical)
    const char* baseline = get_attribut("baseline", obj);
    if (baseline != NULL)
    {
        // Table de correspondance
        mapping_value alignement[] =
        {
            {"centre", GTK_BASELINE_POSITION_CENTER},
            {"haut",   GTK_BASELINE_POSITION_TOP},
            {"bas",    GTK_BASELINE_POSITION_BOTTOM},
            {NULL, 0}  // Sentinel
        };

        // Recherche dans la table
        for (int i = 0; alignement[i].nom != NULL; i++)
        {
            if (strcmp(baseline, alignement[i].nom) == 0)
            {
                gtk_box_set_baseline_position(box, alignement[i].position);
                goto suivant;
            }
        }
        print_error_mapping_value("baseline",alignement);
        suivant:
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
}
