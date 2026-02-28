#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../GENERAL/Widget.h"
void init_comboboxtext_or_comboboxtextentry(Widget* obj, _Bool Search);

void init_comboboxtext(Widget* obj)
{
    init_comboboxtext_or_comboboxtextentry(obj,FALSE);
}

void init_comboboxtextentry(Widget* obj)
{
    init_comboboxtext_or_comboboxtextentry(obj,TRUE);
}

void init_comboboxtext_or_comboboxtextentry(Widget* obj, _Bool Search)
{
    // Créer soit un SearchEntry soit un Entry normal
    if (Search)
    {
        obj->Widget_Ptr = gtk_combo_box_text_new_with_entry();
    }
    else
    {
        obj->Widget_Ptr = gtk_combo_box_text_new();
    }

    Attributs tableau_attribut[] =
    {
        {"selection",      strdup("0")},
    };

    char* tableau_enfant[] =
    {
        "signal","option"
    };

    obj->Nbre_Attribut = sizeof(tableau_attribut) / sizeof(tableau_attribut[0]);
    obj->Nbre_enfant = sizeof(tableau_enfant) / sizeof(tableau_enfant[0]);

    obj->List_Attribut = (Attributs*)malloc(obj->Nbre_Attribut * sizeof(Attributs));
    obj->List_widget_enfant = (char**)malloc(obj->Nbre_enfant * sizeof(char*));

    obj->apply_attribut_func = apply_attribut_comboboxtext;
    obj->set_child = set_child_comboboxtext;

    // Copier les attributs
    memcpy(obj->List_Attribut, tableau_attribut, obj->Nbre_Attribut * sizeof(Attributs));

    // Copier les enfants
    memcpy(obj->List_widget_enfant, tableau_enfant, obj->Nbre_enfant * sizeof(char*));
}
