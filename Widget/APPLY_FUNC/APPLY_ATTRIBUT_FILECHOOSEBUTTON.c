#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_filechoosebutton(Widget* obj)
{
    const char* type = get_attribut("type", obj);
    if (type != NULL)
    {
        // Table de correspondance
        mapping_value type_mapping[] =
        {
            {"file",  GTK_FILE_CHOOSER_ACTION_OPEN},
            {"save",  GTK_FILE_CHOOSER_ACTION_SAVE},
            {"select_folder",  GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER},
            {"create_folder", GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER    },
            {NULL, 0}  // Sentinel
        };

        // Recherche dans la table
        for (int i = 0; type_mapping[i].nom != NULL; i++)
        {
            if (strcmp(type, type_mapping[i].nom) == 0)
            {
                const char* titre = get_attribut("titre", obj);

                const char* titre_init = (titre != NULL) ? titre : "Choisir un fichier";
                GtkWidget* nouveau = gtk_file_chooser_button_new(titre_init, type_mapping[i].position);

                // Remplacer l'ancien widget dans le parent GTK
                /*GtkWidget* parent = gtk_widget_get_parent(obj->Widget_Ptr);
                if (parent)
                {
                    gtk_container_remove(GTK_CONTAINER(parent), obj->Widget_Ptr);
                    gtk_container_add(GTK_CONTAINER(parent), nouveau);
                }*/

                obj->Widget_Ptr = nouveau;

                goto suivant;
            }
        }
        print_error_mapping_value("type",type_mapping);
suivant:
    }
    else return;



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
