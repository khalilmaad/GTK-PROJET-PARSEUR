#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_levelbar(Widget* obj)
{
    GtkLevelBar* levelbar = GTK_LEVEL_BAR(obj->Widget_Ptr);



    const char* min = get_attribut("min", obj);
    if (min)
    {
        gtk_level_bar_set_min_value(levelbar, atof(min));  // nouveau min
    }

    const char* max = get_attribut("max", obj);
    if (max)
    {
        gtk_level_bar_set_max_value(levelbar, atof(max)); // nouveau max
    }

    const char* value = get_attribut("value", obj);
    if (value != NULL)
    {
        gtk_level_bar_set_value(levelbar, atof(value));
    }

    // Orientation
    const char* orientation = get_attribut("orientation", obj);
    if (orientation != NULL)
    {
        if (strcmp(orientation, "vertical") == 0 || strcmp(orientation, "verticale") == 0)
        {
            gtk_orientable_set_orientation(GTK_ORIENTABLE(levelbar), GTK_ORIENTATION_VERTICAL);
        }
    }

    const char* mode = get_attribut("mode", obj);
    if (mode != NULL)
    {
        // Table de correspondance
        static const struct
        {
            const char* nom;
            GtkLevelBarMode position;
        } mode_rendu[] =
        {
            {"continu", GTK_LEVEL_BAR_MODE_CONTINUOUS},
            {"discret",   GTK_LEVEL_BAR_MODE_CONTINUOUS},
            {NULL, 0}  // Sentinel
        };

        // Recherche dans la table
        for (int i = 0; mode_rendu[i].nom != NULL; i++)
        {
            if (strcmp(mode, mode_rendu[i].nom) == 0)
            {
                gtk_level_bar_set_mode(levelbar, mode_rendu[i].position);
                break;
            }
        }
    }

    const char* level_low = get_attribut("level_low", obj);
    if (level_low)
    {
        gtk_level_bar_add_offset_value(levelbar,"low",atof(level_low));
    }

    const char* level_high = get_attribut("level_high", obj);
    if (level_high != NULL)
    {
        gtk_level_bar_add_offset_value(levelbar,"high", atof(level_high));
    }

}
