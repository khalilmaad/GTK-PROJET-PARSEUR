#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../GENERAL/Widget.h"
#include "../SET_CHILD_FUNC/SET_CHILD_FUNC.h"

void init_toolbar(Widget* obj)
{
    obj->Widget_Ptr = gtk_toolbar_new();

    char* tableau_enfant[] = {"toolitem","separatortoolitem"};

    Attributs tableau_attribut[] =
    {
        {"orientation",        strdup("")},
        {"style_affichage",    strdup("")},
    };

    obj->Nbre_Attribut = sizeof(tableau_attribut) / sizeof(tableau_attribut[0]);
    obj->Nbre_enfant = sizeof(tableau_enfant) / sizeof(tableau_enfant[0]);

    obj->List_Attribut = NULL;
    obj->List_widget_enfant =(char**) malloc(obj->Nbre_enfant * sizeof(char*));

    obj->apply_attribut_func = apply_attribut_toolbar;
    obj->set_child = set_child_toolbar;

    memcpy(obj->List_Attribut, tableau_attribut, obj->Nbre_Attribut * sizeof(Attributs));
    memcpy(obj->List_widget_enfant, tableau_enfant, obj->Nbre_enfant * sizeof(char*));
}
