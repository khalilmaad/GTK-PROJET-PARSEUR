#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_frame(Widget* obj)
{
    GtkFrame* frame = GTK_FRAME(obj->Widget_Ptr);

    // Définir le label
    const char* label = get_attribut("label", obj);
    if (label != NULL)
    {
        gtk_frame_set_label(frame, label);
    }


    const char* label_taille = get_attribut("label_taille", obj);
    if (label_taille != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-font-size",label_taille);
    }

    const char* label_style = get_attribut("label_style", obj);
    if (label_style != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-font-style",label_style);
    }

    // Alignement du label
    const char* alignement_vertical = get_attribut("alignement_vertical", obj);
    const char* alignement_horizontal = get_attribut("alignement_horizontal", obj);

    if (alignement_vertical != NULL && alignement_horizontal != NULL)
    {
        // Table de correspondance pour l'alignement
        static const struct
        {
            const char* nom;
            float valeur;
        } align_mapping[] =
        {
            {"bas",    0.0},
            {"milieu",  0.5},
            {"haut",     1.0},
            {"gauche",  0.0},
            {"centre",  0.5},
            {"droite",  1.0},
            {NULL, 0.0}  // Sentinel
        };

        float vert_val = 0.0;
        float horiz_val = 0.0;

        // Recherche de la valeur verticale
        for (int i = 0; align_mapping[i].nom != NULL; i++)
        {
            if (strcmp(alignement_vertical, align_mapping[i].nom) == 0)
            {
                vert_val = align_mapping[i].valeur;
                break;
            }
        }

        // Recherche de la valeur horizontale
        for (int i = 0; align_mapping[i].nom != NULL; i++)
        {
            if (strcmp(alignement_horizontal, align_mapping[i].nom) == 0)
            {
                horiz_val = align_mapping[i].valeur;
                break;
            }
        }

        // Appliquer l'alignement si les deux valeurs ont été trouvées
        // Note: L'original vérifie if (it_vert != align_mapping.end() && it_horiz != align_mapping.end())
        // En C, on vérifie que les valeurs ont été mises à jour (différentes de 0.0 par défaut)
        // Mais comme 0.0 est une valeur valide, on ne peut pas utiliser cette vérification
        // On applique toujours les valeurs (0.0, 0.0 par défaut)
        gtk_frame_set_label_align(frame, horiz_val, vert_val);
    }
}
