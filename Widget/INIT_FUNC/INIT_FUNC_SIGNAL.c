#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../GENERAL/Widget.h"
#include "../SET_CHILD_FUNC/SET_CHILD_FUNC.h"



void init_signal(Widget* obj)
{
    obj->Widget_Ptr = NULL;

    Attributs tableau_attribut[]=
    {
        {"sible",           strdup("")},//ID widgetsible
        {"fonction",         strdup("")},//afficher , cacher, modifier, detruire
        {"attribut_sible",         strdup("")},// nom attribut à siblé
        {"attribut_valeur",    strdup("")},   // la nouvelle valeur de l'attribut siblé
        {"type",    strdup("clicked")},
    };

    char* tableau_enfant[] = {"fenetre"};

    obj->Nbre_Attribut = sizeof(tableau_attribut) / sizeof(tableau_attribut[0]);
    obj->Nbre_enfant = sizeof(tableau_enfant) / sizeof(tableau_enfant[0]);

    obj->List_Attribut = (Attributs*)malloc(obj->Nbre_Attribut * sizeof(Attributs));
    obj->List_widget_enfant =(char**) malloc(obj->Nbre_enfant * sizeof(char*));

    obj->apply_attribut_func = NULL;
    obj->set_child = NULL;

    memcpy(obj->List_Attribut, tableau_attribut, obj->Nbre_Attribut * sizeof(Attributs));
    memcpy(obj->List_widget_enfant, tableau_enfant, obj->Nbre_enfant * sizeof(char*));
}
