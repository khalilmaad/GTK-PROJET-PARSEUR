#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_scale(Widget* obj)
{
    GtkScale* scale = GTK_SCALE(obj->Widget_Ptr);

    // Orientation
    const char* orientation = get_attribut("orientation", obj);
    if (orientation != NULL)
    {
        if (strcmp(orientation, "vertical") == 0 || strcmp(orientation, "verticale") == 0)
        {
            gtk_orientable_set_orientation(GTK_ORIENTABLE(scale), GTK_ORIENTATION_VERTICAL);
        }
    }

    const char* aff_valeur_cote_curseur = get_attribut("aff_valeur_cote_curseur", obj);
    if (aff_valeur_cote_curseur != NULL)
    {
        gtk_scale_set_draw_value(scale, to_bool(aff_valeur_cote_curseur));
    }

    const char* pos_value = get_attribut("pos_value", obj);
    if (pos_value != NULL)
    {
        // Table de correspondance
        mapping_value alignement[] =
        {
            {"haut", GTK_POS_TOP},
            {"bas",   GTK_POS_BOTTOM},
            {"gauche",    GTK_POS_LEFT},
            {"droite",    GTK_POS_RIGHT},
            {NULL, 0}  // Sentinel
        };

        // Recherche dans la table
        for (int i = 0; alignement[i].nom != NULL; i++)
        {
            if (strcmp(pos_value, alignement[i].nom) == 0)
            {
                gtk_scale_set_value_pos(scale, alignement[i].position);
                 goto suivant;
            }
        }
        print_error_mapping_value("pos_value",alignement);
        suivant:
    }


    const char* min = get_attribut("min", obj);
    if (min)
    {
        GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(scale));
        gtk_adjustment_set_lower(adj, string_to_double("min",min));  // nouveau min
    }

    const char* max = get_attribut("max", obj);
    if (max)
    {
        GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(scale));
        gtk_adjustment_set_upper(adj, string_to_double("max",max)); // nouveau max
    }


    const char* value = get_attribut("value", obj);
    if (value != NULL)
    {
        gtk_range_set_value(GTK_RANGE(scale), string_to_double("value",value));
    }

}
