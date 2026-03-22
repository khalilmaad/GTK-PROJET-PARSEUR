#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_stack(Widget* obj)
{
    GtkStack* Stack = GTK_STACK(obj->Widget_Ptr);


    const char* transition = get_attribut("transition",obj);
    if (transition)
    {
        mapping_value typetransition_mapping[] =
        {
            {"aucun", GTK_STACK_TRANSITION_TYPE_NONE},
            {"fondu",  GTK_STACK_TRANSITION_TYPE_CROSSFADE},
            {"horizontal",  GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT},
            {"vertical",    GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN},
            {NULL, 0}  // Sentinel
        };

        // Recherche dans la table
        for (int i = 0; typetransition_mapping[i].nom != NULL; i++)
        {
            if (strcmp(transition, typetransition_mapping[i].nom) == 0)
            {
                gtk_stack_set_transition_type(Stack, typetransition_mapping[i].position);
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
            gtk_stack_set_transition_duration(Stack,duree_transition);
        }
        else
        {
            gtk_stack_set_transition_duration(Stack,500);
        }
    }
}
