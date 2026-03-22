#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../GENERAL/Widget.h"
#include "../SET_CHILD_FUNC/SET_CHILD_FUNC.h"

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
        {"alignement_texte",   strdup("droite")},
        {"couleur_fond",       strdup("")},
        {"coin_arrondi",       strdup("")},
        {"margin",             strdup("")},
        {"margin_top",         strdup("")},
        {"margin_bottom",      strdup("")},
        {"margin_left",        strdup("")},
        {"margin_right",       strdup("")},
        {"bordure",            strdup("")},
        {"box_shadow",         strdup("")},
        {"couleur_label",      strdup("")},
        {"font_weight",        strdup("")},
        {"font_size",          strdup("")},
        {"font_family",          strdup("")},
        {"font_style",        strdup("")},
    };

    char* tableau_enfant[] =
    {
        "signal"
    };

    obj->Nbre_Attribut = sizeof(tableau_attribut) / sizeof(tableau_attribut[0]);
    obj->Nbre_enfant = sizeof(tableau_enfant) / sizeof(tableau_enfant[0]);

    obj->List_Attribut = (Attributs*)malloc(obj->Nbre_Attribut * sizeof(Attributs));
    obj->List_widget_enfant = (char**)malloc(obj->Nbre_enfant * sizeof(char*));

    obj->apply_attribut_func = apply_attribut_entry;
    obj->set_child = set_child_default;

    // Copier les attributsk
    memcpy(obj->List_Attribut, tableau_attribut, obj->Nbre_Attribut * sizeof(Attributs));
    // Copier les enfants
    memcpy(obj->List_widget_enfant, tableau_enfant, obj->Nbre_enfant * sizeof(char*));
}
