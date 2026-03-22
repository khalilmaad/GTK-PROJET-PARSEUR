#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_button(Widget* obj)
{
    GtkButton* button = GTK_BUTTON(obj->Widget_Ptr);

    // Label
    const char* label = get_attribut("label", obj);
    if (label != NULL)
    {
        gtk_button_set_label(button, label);
    }

    // Utiliser mnémonique (raccourci clavier)
    const char* use_underline = get_attribut("use_underline", obj);
    if (use_underline != NULL)
    {
        gtk_button_set_use_underline(button, to_bool(use_underline));
    }

    // Icône
    const char* type_icone = get_attribut("type_icone", obj);
    const char* icone = get_attribut("icone", obj);

    if (type_icone != NULL && icone != NULL)
    {
        if (to_bool(type_icone))
        {
            // Icône nommée (thème)
            GtkWidget* image = gtk_image_new_from_icon_name(icone, GTK_ICON_SIZE_BUTTON);
            gtk_button_set_image(button, image);
        }
        else
        {
            // Icône depuis fichier
            GtkWidget* image = gtk_image_new_from_file(icone);

            // Taille icone
            const char* taille_icone_str = get_attribut("taille_icone", obj);
            if (taille_icone_str != NULL)
            {
                long taille_icone = string_to_long("taille_icone",taille_icone_str);

                // Charger le pixbuf depuis le fichier
                GError* error = NULL;
                GdkPixbuf* pixbuf = gdk_pixbuf_new_from_file(icone, &error);

                if (pixbuf != NULL)
                {
                    // Redimensionner le pixbuf
                    GdkPixbuf* scaled_pixbuf = gdk_pixbuf_scale_simple(
                                                   pixbuf,
                                                   taille_icone,
                                                   taille_icone,
                                                   GDK_INTERP_BILINEAR
                                               );

                    if (scaled_pixbuf != NULL)
                    {
                        // Mettre à jour l'image
                        gtk_image_set_from_pixbuf(GTK_IMAGE(image), scaled_pixbuf);
                        g_object_unref(scaled_pixbuf);
                    }

                    // Libérer la mémoire
                    g_object_unref(pixbuf);
                }
                else if (error != NULL)
                {
                    fprintf(stderr, "\033[33mAvertissement: Erreur chargement image: %s\033[0m\n", error->message);
                    g_error_free(error);
                }
            }

            gtk_button_set_image(button, image);
        }
    }

    // Toujours afficher l'image (même si pas d'espace)
    const char* toujours_afficher_icone = get_attribut("toujours_afficher_icone", obj);
    if (toujours_afficher_icone != NULL)
    {
        gtk_button_set_always_show_image(button, to_bool(toujours_afficher_icone));
    }

    // Position de l'image par rapport au texte
    const char* position_icone = get_attribut("position_icone", obj);
    if (position_icone != NULL)
    {
        // Table de correspondance
        mapping_value position_mapping[] =
        {
            {"gauche",  GTK_POS_LEFT},
            {"droite",  GTK_POS_RIGHT},
            {"dessus",  GTK_POS_TOP},
            {"dessous", GTK_POS_BOTTOM},
            {NULL, 0}  // Sentinel
        };

        // Recherche dans la table
        for (int i = 0; position_mapping[i].nom != NULL; i++)
        {
            if (strcmp(position_icone, position_mapping[i].nom) == 0)
            {
                gtk_button_set_image_position(button, position_mapping[i].position);
                goto suivant;
            }
        }
        print_error_mapping_value("position_icone",position_mapping);
suivant:
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

    const char* font_style = get_attribut("font_style", obj);
    if (font_style != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-font-style",font_style);
    }

    const char* couleur_fond = get_attribut("couleur_fond", obj);
    if (couleur_fond != NULL)
    {
        GdkRGBA Color_;
        gdk_rgba_parse(&Color_, couleur_fond);


        // Apply the background color to all states of the button
        gtk_widget_override_background_color(obj->Widget_Ptr, GTK_STATE_FLAG_NORMAL, &Color_);
        // Normal state
        gtk_button_set_relief(GTK_BUTTON(obj->Widget_Ptr), GTK_RELIEF_NONE);
        //apply_css(obj->Widget_Ptr,"ma-background-color",couleur_fond);
    }
}
