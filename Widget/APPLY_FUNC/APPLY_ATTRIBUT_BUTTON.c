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
                int taille_icone = atoi(taille_icone_str);

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
        static const struct
        {
            const char* nom;
            GtkPositionType position;
        } position_mapping[] =
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
                break;
            }
        }
    }
}
