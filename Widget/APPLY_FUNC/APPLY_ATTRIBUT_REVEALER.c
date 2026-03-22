#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_revealer(Widget* obj)
{
    GtkRevealer* revealer = GTK_REVEALER(obj->Widget_Ptr);


    const char* transition = get_attribut("transition",obj);
    if (transition)
    {
        mapping_value typetransition_mapping[] =
        {
            {"aucun", GTK_REVEALER_TRANSITION_TYPE_NONE},
            {"fondu",  GTK_REVEALER_TRANSITION_TYPE_CROSSFADE},
            {"gauche",  GTK_REVEALER_TRANSITION_TYPE_SLIDE_LEFT},
            {"droite",    GTK_REVEALER_TRANSITION_TYPE_SLIDE_RIGHT},
            {"haut",  GTK_REVEALER_TRANSITION_TYPE_SLIDE_UP},
            {"bas",    GTK_REVEALER_TRANSITION_TYPE_SLIDE_DOWN},
            {NULL, 0}  // Sentinel
        };

        // Recherche dans la table
        for (int i = 0; typetransition_mapping[i].nom != NULL; i++)
        {
            if (strcmp(transition, typetransition_mapping[i].nom) == 0)
            {
                gtk_revealer_set_transition_type(revealer, typetransition_mapping[i].position);
                goto suivant;
            }
        }
        print_error_mapping_value("transition",typetransition_mapping);
        suivant:
    }

    const char* duree_transition_str = get_attribut("duree_transition",obj);
    if (duree_transition_str)
    {

        long duree_transition = string_to_long("duree_transition",duree_transition_str);

        if (duree_transition > 190 && duree_transition < 1010)
        {
            gtk_revealer_set_transition_duration(revealer,duree_transition);
        }
        else
        {
            gtk_revealer_set_transition_duration(revealer,500);
        }
    }
}
