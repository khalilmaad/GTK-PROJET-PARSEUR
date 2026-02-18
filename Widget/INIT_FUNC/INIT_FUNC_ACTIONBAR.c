#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../SET_CHILD_FUNC/SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"



void init_action_bar(Widget* obj)
{
    obj->Widget_Ptr = gtk_action_bar_new();

    // Pas d'attributs pour ActionBar
    obj->List_Attribut = NULL;
    obj->Nbre_Attribut = 0;  // Pas d'attributs spécifiques pour ActionBar

    // Liste des widgets enfants autorisés
    char* tableau_enfant[] =
    {
        "button",
        "box"
    };

    obj->Nbre_enfant = sizeof(tableau_enfant) / sizeof(tableau_enfant[0]);

    // Allouer mémoire pour la liste d'enfants
    obj->List_widget_enfant = (char**)malloc(obj->Nbre_enfant * sizeof(char*));

    // Fonction d'application des attributs (peut être NULL ou une fonction générique)
    obj->apply_attribut_func = NULL;  // Pas de fonction spécifique pour ActionBar
    obj->set_child = set_child_actionbar;

    // Copier la liste des enfants
    memcpy(obj->List_widget_enfant, tableau_enfant, obj->Nbre_enfant * sizeof(char*));
}
