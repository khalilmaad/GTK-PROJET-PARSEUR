#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../GENERAL/Widget.h"
#include "../SET_CHILD_FUNC/SET_CHILD_FUNC.h"


void init_poisson(Widget* obj)
{
    obj->Widget_Ptr = NULL;

    Attributs tableau_attribut[] =
    {
        {"pos_aleatoire",               strdup("true")},
        {"dead",                        strdup("")},
        {"x",                           strdup("1")},
        {"y",                           strdup("1")},
        {"icone_espece",                strdup("")},  //path de l'image representent le poisson
        {"predator",                    strdup("false")},
    };

    obj->Nbre_Attribut = sizeof(tableau_attribut) / sizeof(tableau_attribut[0]);
    obj->Nbre_enfant = 0;

    obj->List_Attribut = (Attributs*)malloc(obj->Nbre_Attribut * sizeof(Attributs));
    obj->List_widget_enfant = NULL;

    obj->apply_attribut_func = apply_attribut_poisson;
    obj->set_child = NULL;

    // Copier les attributs
    memcpy(obj->List_Attribut, tableau_attribut, obj->Nbre_Attribut * sizeof(Attributs));

}
