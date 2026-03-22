#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"



void apply_attribut_entry(Widget* obj)
{
    GtkEntry* entry = GTK_ENTRY(obj->Widget_Ptr);

    // texte initial
    const char* texte_initial = get_attribut("texte_initial", obj);
    if (texte_initial != NULL)
    {
        gtk_entry_set_text(entry, texte_initial);
    }

    // texte placeholder
    const char* placeholder = get_attribut("placeholder", obj);
    if (placeholder != NULL)
    {
        gtk_entry_set_placeholder_text(entry, placeholder);
    }

    // longueur maximale
    const char* longueur_max_str = get_attribut("longueur_max", obj);
    if (longueur_max_str != NULL)
    {
        long longueur_max = string_to_long("longueur_max",longueur_max_str);

        if (longueur_max > 0)
        {
            gtk_entry_set_max_length(entry, longueur_max);
        }
        else
        {
            gtk_entry_set_max_length(entry, 50);
        }
    }

    // visibilité
    const char* visibilite = get_attribut("visibilite", obj);
    if (visibilite != NULL)
    {
        gtk_entry_set_visibility(entry, to_bool(visibilite));
    }

    // Afficher le caractère de masquage personnalisé
    const char* invisible_char = get_attribut("invisible_char", obj);
    if (invisible_char != NULL && strlen(invisible_char) > 0)
    {
        gtk_entry_set_invisible_char(entry, invisible_char[0]);
    }

    // editable
    const char* editable = get_attribut("editable", obj);
    if (editable != NULL)
    {
        gtk_editable_set_editable(GTK_EDITABLE(entry), to_bool(editable));
    }

    // Alignement du texte
    const char* alignement_texte = get_attribut("alignement_texte", obj);
    if (alignement_texte != NULL)
    {
        // Table de correspondance
        mapping_value alignement_mapping[] =
        {
            {"droite", 1.0},
            {"centre", 0.5},
            {"gauche", 0.0},
            {NULL, 0.0}  // Sentinel
        };

        // Recherche dans la table
        for (int i = 0; alignement_mapping[i].nom != NULL; i++)
        {
            if (strcmp(alignement_texte, alignement_mapping[i].nom) == 0)
            {
                gtk_entry_set_alignment(entry, alignement_mapping[i].position);
                goto suivant;
            }
        }
        print_error_mapping_value("alignement_texte",alignement_mapping);
        suivant:
    }

    // SearchEntry (avec icône de recherche)
    const char* sensibilite_icone = get_attribut("sensibilite_icone", obj);
    const char* position_icone = get_attribut("position_icone", obj);
    const char* icone = get_attribut("icone", obj);

    if (sensibilite_icone != NULL && position_icone != NULL && icone != NULL)
    {
        // Table de correspondance pour la position de l'icône
        mapping_value icon_mapping[] =
        {
            {"droite", GTK_ENTRY_ICON_SECONDARY},
            {"gauche", GTK_ENTRY_ICON_PRIMARY},
            {NULL, 0}  // Sentinel
        };

        // Recherche dans la table
        for (int i = 0; icon_mapping[i].nom != NULL; i++)
        {
            if (strcmp(position_icone, icon_mapping[i].nom) == 0)
            {
                // Position de l'icône
                gtk_entry_set_icon_from_icon_name(entry,
                                                  icon_mapping[i].position,
                                                  icone);

                // Sensibilité de l'icône
                gtk_entry_set_icon_sensitive(entry,
                                             icon_mapping[i].position,
                                             to_bool(sensibilite_icone));
                 goto suivant2;
            }
        }
        print_error_mapping_value("position_icone",icon_mapping);
        suivant2:
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
    const char* font_style = get_attribut("font_style", obj);
    if (font_style != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-font-style",font_style);
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

    // Quand on presse Entrée
    /*g_signal_connect(entry, "activate",
                     G_CALLBACK(on_entry_activate), NULL);*/
}
