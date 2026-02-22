#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"

void apply_attribut_toolbar(Widget* obj)
{
    GtkToolbar* toolbar = GTK_TOOLBAR(obj->Widget_Ptr);

    // Orientation
    const char* orientation = get_attribut("orientation", obj);
    if (orientation != NULL)
    {
        if (strcmp(orientation, "vertical") == 0 || strcmp(orientation, "verticale") == 0)
        {
            gtk_orientable_set_orientation(GTK_ORIENTABLE(toolbar), GTK_ORIENTATION_VERTICAL);
        }
    }

    const char* style_affichage = get_attribut("style_affichage", obj);
    if (style_affichage != NULL)
    {
        // Table de correspondance
        static const struct
        {
            const char* nom;
            GtkToolbarStyle style;
        } alignement[] =
        {
            {"icone_seulement", GTK_TOOLBAR_ICONS},
            {"texte_seulement",   GTK_TOOLBAR_TEXT},
            {"icone_texte",    GTK_TOOLBAR_BOTH },
            {"icone_gauche_texte",    GTK_TOOLBAR_BOTH_HORIZ },
            {NULL, 0}  // Sentinel
        };

        // Recherche dans la table
        for (int i = 0; alignement[i].nom != NULL; i++)
        {
            if (strcmp(style_affichage, alignement[i].nom) == 0)
            {
                gtk_toolbar_set_style(toolbar, alignement[i].style);
                break;
            }
        }
    }
}
