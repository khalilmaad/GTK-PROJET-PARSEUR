#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void init_image(Widget* obj)
{
    obj->Widget_Ptr = gtk_image_new();

    Attributs tableau_attribut[] =
    {
        {"type",    strdup("false")},
        {"nom",     strdup("")},
        {"taille",  strdup("")}
    };

    obj->Nbre_Attribut = sizeof(tableau_attribut) / sizeof(tableau_attribut[0]);
    obj->Nbre_enfant = 0;

    obj->List_Attribut = (Attributs*)malloc(obj->Nbre_Attribut * sizeof(Attributs));
    obj->List_widget_enfant = NULL;  // Pas d'enfants

    obj->apply_attribut_func = apply_attribut_image;
    obj->set_child = NULL;

    // Copier les attributs
    memcpy(obj->List_Attribut, tableau_attribut, obj->Nbre_Attribut * sizeof(Attributs));
}
