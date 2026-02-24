#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_menubutton(Widget* obj)
{
    GtkButton* menu_button = GTK_BUTTON(obj->Widget_Ptr);

    // Label
    const char* label = get_attribut("label", obj);
    if (label != NULL)
    {
        gtk_button_set_label(menu_button, label);
    }

    // Icône
    const char* icone = get_attribut("icone", obj);
    if (icone != NULL)
    {
        GtkWidget *image =
        gtk_image_new_from_icon_name(icone,
                                 GTK_ICON_SIZE_BUTTON);

        gtk_button_set_image(GTK_BUTTON(menu_button), image);
        gtk_button_set_always_show_image(GTK_BUTTON(menu_button), TRUE);
    }

    // Position de l'image par rapport au texte
    const char* direction = get_attribut("direction", obj);
    if (direction != NULL)
    {
        // Table de correspondance
        static const struct
        {
            const char* nom;
            GtkArrowType position;
        } direction_mapping[] =
        {
            {"gauche",  GTK_ARROW_LEFT},
            {"droite",  GTK_ARROW_RIGHT},
            {"haut",  GTK_ARROW_UP},
            {"bas", GTK_ARROW_DOWN},
            {NULL, 0}  // Sentinel
        };

        // Recherche dans la table
        for (int i = 0; direction_mapping[i].nom != NULL; i++)
        {
            if (strcmp(direction, direction_mapping[i].nom) == 0)
            {
                gtk_menu_button_set_direction(GTK_MENU_BUTTON(menu_button), direction_mapping[i].position);
                break;
            }
        }
    }
}
