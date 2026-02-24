#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../GENERAL/Widget.h"
#include "../SET_CHILD_FUNC/SET_CHILD_FUNC.h"


void init_scalebutton(Widget* obj)
{
    /*obj->Widget_Ptr = gtk_scale_button_new(
                 GTK_ORIENTATION_HORIZONTAL, // orientation du curseur
                 0.0,  // valeur min
                 100.0, // valeur max
                 1.0); // step increment

    Attributs tableau_attribut[] =
    {
        {"min",                     strdup("0.0")},
        {"max",                     strdup("100.0")},
        {"step",                    strdup("1.0")},
        {"page_increment",          strdup("10.0")},
        {"value",                   strdup("")},
        {"orientation",            strdup("")},
        {"icone",                  strdup("")},
        {"label",                  strdup("")},
    };

    char* tableau_enfant[] =
    {
        "signal"
    };

    obj->Nbre_Attribut = sizeof(tableau_attribut) / sizeof(tableau_attribut[0]);
    obj->Nbre_enfant = sizeof(tableau_enfant) / sizeof(tableau_enfant[0]);

    obj->List_Attribut = (Attributs*)malloc(obj->Nbre_Attribut * sizeof(Attributs));
    obj->List_widget_enfant = (char**)malloc(obj->Nbre_enfant * sizeof(char*));

    obj->apply_attribut_func = apply_attribut_scalebutton;
    obj->set_child = set_child_default;

    // Copier les attributs
    memcpy(obj->List_Attribut, tableau_attribut, obj->Nbre_Attribut * sizeof(Attributs));

    // Copier les enfants
    memcpy(obj->List_widget_enfant, tableau_enfant, obj->Nbre_enfant * sizeof(char*));

    */
}
