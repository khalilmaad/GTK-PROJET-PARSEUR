#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void init_check_button(Widget* obj)
{
    obj->Widget_Ptr = gtk_check_button_new();

    Attributs tableau_attribut[] =
    {
        {"etat_coche",      strdup("false")},
        {"active",       strdup("true")},
        {"label",           strdup("")},
        {"use_underline",   strdup("true")}
    };

    obj->Nbre_Attribut = sizeof(tableau_attribut) / sizeof(tableau_attribut[0]);
    obj->Nbre_enfant = 0;  // Pas d'enfants spécifiques pour CheckButton

    obj->List_Attribut = (Attributs*)malloc(obj->Nbre_Attribut * sizeof(Attributs));
    obj->List_widget_enfant = NULL;  // Pas d'enfants

    obj->apply_attribut_func = apply_attribut_checkbutton;
    obj->set_child = NULL;

    // Copier les attributs
    memcpy(obj->List_Attribut, tableau_attribut, obj->Nbre_Attribut * sizeof(Attributs));
}
