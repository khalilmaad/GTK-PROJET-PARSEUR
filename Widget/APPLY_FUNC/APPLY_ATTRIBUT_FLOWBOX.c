#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_flowbox(Widget* obj)
{
    GtkFlowBox* flowbox = GTK_FLOW_BOX(obj->Widget_Ptr);


    const char* selection = get_attribut("selection",obj);
    if (selection)
    {
        mapping_value typeselection_mapping[] =
        {
            {"aucun", GTK_SELECTION_NONE},
            {"seule",  GTK_SELECTION_SINGLE},
            {"obligatoire",  GTK_SELECTION_BROWSE},
            {"plusieurs",    GTK_SELECTION_MULTIPLE},
            {NULL, 0}  // Sentinel
        };

        // Recherche dans la table
        for (int i = 0; typeselection_mapping[i].nom != NULL; i++)
        {
            if (strcmp(selection, typeselection_mapping[i].nom) == 0)
            {
                gtk_flow_box_set_selection_mode(flowbox, typeselection_mapping[i].position);
                 goto suivant;
            }
        }
        print_error_mapping_value("selection",typeselection_mapping);
        suivant:
    }

    const char* nombre_max = get_attribut("nombre_max", obj);
    if (nombre_max != NULL)
    {
        gtk_flow_box_set_max_children_per_line(flowbox,string_to_long("nombre_max",nombre_max));
    }

    const char* nombre_min = get_attribut("nombre_min", obj);
    if (nombre_min != NULL)
    {
        gtk_flow_box_set_min_children_per_line(flowbox,string_to_long("nombre_min",nombre_min));
    }

    const char* espacement_colonne = get_attribut("espacement_colonne", obj);
    if (espacement_colonne != NULL)
    {
        gtk_flow_box_set_column_spacing(flowbox,string_to_long("espacement_colonne",espacement_colonne));
    }

    const char* espacement_ligne = get_attribut("espacement_ligne", obj);
    if (espacement_ligne != NULL)
    {
        gtk_flow_box_set_row_spacing(flowbox,string_to_long("espacement_ligne",espacement_ligne));
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
