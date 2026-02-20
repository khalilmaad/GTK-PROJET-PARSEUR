#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"

void apply_attribut_buttonbox(Widget* obj)
{
    GtkButtonBox* buttonbox = GTK_BUTTON_BOX(obj->Widget_Ptr);

    // Orientation
    const char* orientation = get_attribut("orientation", obj);
    if (orientation != NULL)
    {
        if (strcmp(orientation, "vertical") == 0 || strcmp(orientation, "verticale") == 0)
        {
            gtk_orientable_set_orientation(GTK_ORIENTABLE(buttonbox), GTK_ORIENTATION_VERTICAL);
        }
    }



    // Baseline position (pour alignement vertical)
    const char* disposition = get_attribut("disposition", obj);
    if (disposition != NULL)
    {
        // Table de correspondance
        static const struct
        {
            const char* nom;
            GtkButtonBoxStyle position;
        } alignement[] =
        {
            {"repartir", GTK_BUTTONBOX_SPREAD},
            {"extremite",   GTK_BUTTONBOX_EDGE},
            {"gauche",    GTK_BUTTONBOX_START},
            {"droite",    GTK_BUTTONBOX_END},
            {"centre",    GTK_BUTTONBOX_CENTER},
            {NULL, 0}  // Sentinel
        };

        // Recherche dans la table
        for (int i = 0; alignement[i].nom != NULL; i++)
        {
            if (strcmp(disposition, alignement[i].nom) == 0)
            {
                gtk_button_box_set_layout(buttonbox, alignement[i].position);
                break;
            }
        }
    }
}
