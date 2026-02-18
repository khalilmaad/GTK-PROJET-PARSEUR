#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../GENERAL/Widget.h"
#include "../SET_CHILD_FUNC/SET_CHILD_FUNC.h"

void init_overlay(Widget* obj)
{
    obj->Widget_Ptr = gtk_overlay_new();

    char* tableau_enfant[] =
    {
        "button", "actionbar", "box", "scrollbar",
        "overlay", "calendrier", "checkbutton", "entry",
        "searchentry", "frame", "image", "label"
    };

    obj->Nbre_Attribut = 0;
    obj->Nbre_enfant = sizeof(tableau_enfant) / sizeof(tableau_enfant[0]);

    obj->List_Attribut = NULL;  // Pas d'attributs
    obj->List_widget_enfant = (char**)malloc(obj->Nbre_enfant * sizeof(char*));

    obj->apply_attribut_func = NULL;  // Pas de fonction spécifique pour Overlay
    obj->set_child = set_child_overlay;

    // Copier les enfants
    memcpy(obj->List_widget_enfant, tableau_enfant, obj->Nbre_enfant * sizeof(char*));
}
