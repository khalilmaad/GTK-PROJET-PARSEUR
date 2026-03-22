#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_fenetre(Widget* obj)
{
    GtkWindow* window = GTK_WINDOW(obj->Widget_Ptr);

    gtk_window_set_mnemonics_visible(window, TRUE);

    // Type de fenêtre
    const char* typefenetre = get_attribut("type_fenetre",obj);
    if (typefenetre)
    {
        mapping_value type_mapping[] =
        {
            {"normale", GDK_WINDOW_TYPE_HINT_NORMAL},
            {"normal",  GDK_WINDOW_TYPE_HINT_NORMAL},
            {"dialog",  GDK_WINDOW_TYPE_HINT_DIALOG},
            {"menu",    GDK_WINDOW_TYPE_HINT_MENU},
            {"utilitaire", GDK_WINDOW_TYPE_HINT_UTILITY},
            {NULL, 0}  // Sentinel
        };

        // Recherche dans la table
        for (int i = 0; type_mapping[i].nom != NULL; i++)
        {
            if (strcmp(typefenetre, type_mapping[i].nom) == 0)
            {
                gtk_window_set_type_hint(window, type_mapping[i].position);
                goto suivant;
            }
        }
        print_error_mapping_value("type_fenetre",type_mapping);
        suivant:
    }

    // Titre
    const char* titre = get_attribut("titre",obj);
    if (titre)
    {
        gtk_window_set_title(window, titre);
    }

    // Dimensions
    const char* largeur_str = get_attribut("largeur",obj);
    const char* hauteur_str = get_attribut("hauteur",obj);
    if (largeur_str && hauteur_str)
    {

        long largeur = string_to_long("largeur",largeur_str);
        long hauteur = string_to_long("hauteur",hauteur_str);

        if (largeur > 0 && hauteur > 0)
        {
            gtk_window_set_default_size(window, largeur, hauteur);
        }
        else
        {
            gtk_window_set_default_size(window, 800, 600);
        }
    }

    // Icône
    const char* type_icone = get_attribut("type_icone", obj);
    const char* icone = get_attribut("icone", obj);

    if (type_icone != NULL && icone != NULL)
    {
        // Convertir type_icone en booléen
        // Dépend de votre implémentation de to_bool
        gboolean is_named_icon = to_bool(type_icone);

        if (is_named_icon)
        {
            // Icône nommée (thème)
            gtk_window_set_icon_name(window, icone);
        }
        else
        {
            // Icône depuis fichier
            GError* error = NULL;
            GdkPixbuf* icon = gdk_pixbuf_new_from_file(icone, &error);

            if (icon != NULL)
            {
                gtk_window_set_icon(window, icon);
                g_object_unref(icon);
            }
            else
            {
                fprintf(stderr, "\n\033[31mErreur lors du chargement de l'icone : %s\033[0m\n",
                        error->message);
                g_error_free(error);
            }
        }
    }

    // Position
    const char* x_str = get_attribut("x", obj);
    const char* y_str = get_attribut("y", obj);

    if (x_str != NULL && y_str != NULL)
    {
        long x = string_to_long("x",x_str);
        long y = string_to_long("y",y_str);
        gtk_window_move(window, x, y);
    }

    // Position auto
    const char* position_auto = get_attribut("position_auto", obj);
    if (position_auto != NULL)
    {
        // Table de correspondance
        mapping_value position_mapping[] =
        {
            {"centre", GTK_WIN_POS_CENTER},
            {"souris", GTK_WIN_POS_MOUSE}
        };

        // Recherche
        for (size_t i = 0; i < sizeof(position_mapping)/sizeof(position_mapping[0]); i++)
        {
            if (strcmp(position_mapping[i].nom, position_auto) == 0)
            {
                gtk_window_set_position(window, position_mapping[i].position);

                goto suivant2;
            }
        }
        print_error_mapping_value("position_auto",position_mapping);
        suivant2:
    }

    // Redimensionnable
    const char* redimensionnable = get_attribut("redimensionnable", obj);
    if (redimensionnable != NULL)
    {
        gtk_window_set_resizable(window, to_bool(redimensionnable));
    }

    // Modale
    const char* modale = get_attribut("modale", obj);
    if (modale != NULL)
    {
        gtk_window_set_modal(window, to_bool(modale));
    }

    const char* couleur_fond = get_attribut("couleur_fond", obj);
    if (couleur_fond != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-background-color",couleur_fond);
    }



}
