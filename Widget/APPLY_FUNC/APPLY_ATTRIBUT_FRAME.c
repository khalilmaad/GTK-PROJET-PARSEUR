#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_frame(Widget* obj)
{
    GtkFrame* frame = GTK_FRAME(obj->Widget_Ptr);

    // Définir le label
    const char* label = get_attribut("label", obj);
    if (label != NULL)
    {
        gtk_frame_set_label(frame, label);
    }


    const char* label_taille = get_attribut("label_taille", obj);
    if (label_taille != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-font-size",label_taille);
    }

    const char* label_style = get_attribut("label_style", obj);
    if (label_style != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-font-style",label_style);
    }

    // Alignement du label
    const char* alignement_vertical = get_attribut("alignement_vertical", obj);
    const char* alignement_horizontal = get_attribut("alignement_horizontal", obj);

    if (alignement_vertical != NULL && alignement_horizontal != NULL)
    {

        // Table de correspondance pour l'alignement
        mapping_value align_mapping[] =
        {
            {"bas",    0.0},
            {"milieu",  0.5},
            {"haut",     1.0},
            {"gauche",  0.0},
            {"centre",  0.5},
            {"droite",  1.0},
            {NULL, 0.0}  // Sentinel
        };

        float vert_val = 0.0;
        float horiz_val = 0.0;

        // Recherche de la valeur verticale
        for (int i = 0; align_mapping[i].nom != NULL; i++)
        {
            if (strcmp(alignement_vertical, align_mapping[i].nom) == 0)
            {
                vert_val = align_mapping[i].position;
                  goto suivant;
            }
        }
        print_error_mapping_value("alignement_vertical",align_mapping);
        suivant:


        // Recherche de la valeur horizontale
        for (int i = 0; align_mapping[i].nom != NULL; i++)
        {
            if (strcmp(alignement_horizontal, align_mapping[i].nom) == 0)
            {
                horiz_val = align_mapping[i].position;
                  goto suivant2;
            }
        }
        print_error_mapping_value("alignement_horizontal",align_mapping);
        suivant2:

        // Appliquer l'alignement si les deux valeurs ont été trouvées
        printf("\n%f %f\n",horiz_val,vert_val );
        gtk_frame_set_label_align(frame, horiz_val, vert_val);
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
    const char* font_style = get_attribut("font_style", obj);
    if (font_style != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-font-style",font_style);
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
