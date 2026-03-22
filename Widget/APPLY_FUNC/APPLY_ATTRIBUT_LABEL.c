#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_label(Widget* obj)
{
    GtkLabel* label = GTK_LABEL(obj->Widget_Ptr);

    // Définir le texte
    const char* texte = get_attribut("texte", obj);
    if (texte != NULL)
    {
        gtk_label_set_text(label, texte);
    }

    // Alignement du texte
    const char* alignement_texte = get_attribut("alignement_texte", obj);
    if (alignement_texte != NULL)
    {
        // Table de correspondance pour l'alignement
        mapping_value align_mapping[] =
        {
            {"gauche",   GTK_JUSTIFY_LEFT},
            {"droite",   GTK_JUSTIFY_RIGHT},
            {"centre",   GTK_JUSTIFY_CENTER},
            {"justifie", GTK_JUSTIFY_FILL},
            {NULL, GTK_JUSTIFY_LEFT}  // Sentinel avec valeur par défaut
        };

        // Recherche dans la table
        for (int i = 0; align_mapping[i].nom != NULL; i++)
        {
            if (strcmp(alignement_texte, align_mapping[i].nom) == 0)
            {
                gtk_label_set_justify(label, align_mapping[i].position);
                 goto suivant;
            }
        }
        print_error_mapping_value("alignement_texte",align_mapping);
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

    const char* box_shadow = get_attribut("box_shadow", obj);
    if (bordure != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-box-shadow",box_shadow);
    }

    const char* font_style = get_attribut("font_style", obj);
    if (font_style != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-font-style",font_style);
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
