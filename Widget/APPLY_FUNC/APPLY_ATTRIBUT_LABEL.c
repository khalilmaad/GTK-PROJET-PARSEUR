#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_label(Widget* obj)
{
    GtkLabel* label = GTK_LABEL(obj->Widget_Ptr);

    // Définir le texte
    const char* texte = get_attribut("texte", obj);
    if (texte != NULL)
    {
        gtk_label_set_text(label, texte);
    }

    // Alignement du texte
    const char* alignement_texte = get_attribut("alignement_texte", obj);
    if (alignement_texte != NULL)
    {
        // Table de correspondance pour l'alignement
        static const struct
        {
            const char* nom;
            GtkJustification alignement;
        } align_mapping[] =
        {
            {"gauche",   GTK_JUSTIFY_LEFT},
            {"droite",   GTK_JUSTIFY_RIGHT},
            {"centre",   GTK_JUSTIFY_CENTER},
            {"justifie", GTK_JUSTIFY_FILL},
            {NULL, GTK_JUSTIFY_LEFT}  // Sentinel avec valeur par défaut
        };

        // Recherche dans la table
        for (int i = 0; align_mapping[i].nom != NULL; i++)
        {
            if (strcmp(alignement_texte, align_mapping[i].nom) == 0)
            {
                gtk_label_set_justify(label, align_mapping[i].alignement);
                break;
            }
        }
    }
}
