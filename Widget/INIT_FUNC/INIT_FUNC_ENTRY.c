#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../GENERAL/Widget.h"
void init_entry_or_searchentry(Widget*, _Bool);

void init_entry(Widget* obj)
{
    init_entry_or_searchentry(obj,FALSE);
}

void init_searchentry(Widget* obj)
{
    init_entry_or_searchentry(obj,TRUE);
}

void init_entry_or_searchentry(Widget* obj, _Bool Search)
{
    // Créer soit un SearchEntry soit un Entry normal
    if (Search)
    {
        obj->Widget_Ptr = gtk_search_entry_new();
    }
    else
    {
        obj->Widget_Ptr = gtk_entry_new();
    }

    Attributs tableau_attribut[] =
    {
        {"texte_initial",      strdup("")},
        {"placeholder",        strdup("Tapez ici...")},
        {"longueur_max",       strdup("50")},
        {"icone",              strdup("")},
        {"position_icone",     strdup("gauche")},
        {"sensibilite_icone",  strdup("true")},
        {"visibilite",         strdup("true")},
        {"invisible_char",     strdup("*")},
        {"editable",           strdup("true")},
        {"alignement_texte",   strdup("droite")}
    };

    obj->Nbre_Attribut = sizeof(tableau_attribut) / sizeof(tableau_attribut[0]);
    obj->Nbre_enfant = 0;

    obj->List_Attribut = (Attributs*)malloc(obj->Nbre_Attribut * sizeof(Attributs));
    obj->List_widget_enfant = NULL;  // Pas d'enfants

    obj->apply_attribut_func = apply_attribut_entry;
    obj->set_child = NULL;

    // Copier les attributs
    memcpy(obj->List_Attribut, tableau_attribut, obj->Nbre_Attribut * sizeof(Attributs));
}
