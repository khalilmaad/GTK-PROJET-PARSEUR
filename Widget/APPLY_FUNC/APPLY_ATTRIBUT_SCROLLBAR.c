#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_scrollbar(Widget* obj)
{
    const char* affichage_vertical = get_attribut("affichage_vertical", obj);
    const char* affichage_horizontal = get_attribut("affichage_horizontal", obj);

    if (affichage_vertical != NULL && affichage_horizontal != NULL)
    {
        // Table de correspondance pour le type d'affichage
        static const struct
        {
            const char* nom;
            GtkPolicyType type;
        } type_mapping[] =
        {
            {"jamais",    GTK_POLICY_NEVER},
            {"toujours",  GTK_POLICY_ALWAYS},
            {"auto",      GTK_POLICY_AUTOMATIC},
            {NULL, GTK_POLICY_NEVER}  // Sentinel
        };

        GtkPolicyType vert_type = GTK_POLICY_NEVER;
        GtkPolicyType horiz_type = GTK_POLICY_NEVER;

        // Recherche du type vertical
        for (int i = 0; type_mapping[i].nom != NULL; i++)
        {
            if (strcmp(affichage_vertical, type_mapping[i].nom) == 0)
            {
                vert_type = type_mapping[i].type;
                break;
            }
        }

        // Recherche du type horizontal
        for (int i = 0; type_mapping[i].nom != NULL; i++)
        {
            if (strcmp(affichage_horizontal, type_mapping[i].nom) == 0)
            {
                horiz_type = type_mapping[i].type;
                break;
            }
        }

        // Appliquer la politique de défilement
        // Note: Les paramètres sont (horizontal_policy, vertical_policy)
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(obj->Widget_Ptr),
                                       horiz_type,
                                       vert_type);
    }
}
