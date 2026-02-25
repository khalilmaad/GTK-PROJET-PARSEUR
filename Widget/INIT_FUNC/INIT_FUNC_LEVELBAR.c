#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../GENERAL/Widget.h"
#include "../SET_CHILD_FUNC/SET_CHILD_FUNC.h"


void init_levelbar(Widget* obj)
{
    obj->Widget_Ptr = gtk_level_bar_new();

    Attributs tableau_attribut[] =
    {
        {"min",                     strdup("0.0")},
        {"max",                     strdup("100.0")},
        {"value",                   strdup("")},
        {"orientation",            strdup("")},
        {"mode",                   strdup("continu")},
        {"level_low",                  strdup("30.0")},
        {"level_high",                  strdup("80.0")},
    };

    char* tableau_enfant[] =
    {
        "signal"
    };

    obj->Nbre_Attribut = sizeof(tableau_attribut) / sizeof(tableau_attribut[0]);
    obj->Nbre_enfant = sizeof(tableau_enfant) / sizeof(tableau_enfant[0]);

    obj->List_Attribut = (Attributs*)malloc(obj->Nbre_Attribut * sizeof(Attributs));
    obj->List_widget_enfant = (char**)malloc(obj->Nbre_enfant * sizeof(char*));

    obj->apply_attribut_func = apply_attribut_levelbar;
    obj->set_child = set_child_default;

    // Copier les attributs
    memcpy(obj->List_Attribut, tableau_attribut, obj->Nbre_Attribut * sizeof(Attributs));

    // Copier les enfants
    memcpy(obj->List_widget_enfant, tableau_enfant, obj->Nbre_enfant * sizeof(char*));
}
