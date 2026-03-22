#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../GENERAL/Widget.h"
#include "../SET_CHILD_FUNC/SET_CHILD_FUNC.h"


void init_scale(Widget* obj)
{
    obj->Widget_Ptr = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,
                                 0.0,   // min
                                 100.0, // max
                                 1.0);  // step

    Attributs tableau_attribut[] =
    {
        {"min",                     strdup("0,0")},
        {"max",                     strdup("100,0")},
        {"pos_value",               strdup("gauche")},
        {"value",                   strdup("")},
        {"aff_valeur_cote_curseur", strdup("true")},
        {"orientation",             strdup("")},
    };

    char* tableau_enfant[] =
    {
        "signal"
    };

    obj->Nbre_Attribut = sizeof(tableau_attribut) / sizeof(tableau_attribut[0]);
    obj->Nbre_enfant = sizeof(tableau_enfant) / sizeof(tableau_enfant[0]);

    obj->List_Attribut = (Attributs*)malloc(obj->Nbre_Attribut * sizeof(Attributs));
    obj->List_widget_enfant = (char**)malloc(obj->Nbre_enfant * sizeof(char*));

    obj->apply_attribut_func = apply_attribut_scale;
    obj->set_child = set_child_default;

    // Copier les attributs
    memcpy(obj->List_Attribut, tableau_attribut, obj->Nbre_Attribut * sizeof(Attributs));

    // Copier les enfants
    memcpy(obj->List_widget_enfant, tableau_enfant, obj->Nbre_enfant * sizeof(char*));

}
