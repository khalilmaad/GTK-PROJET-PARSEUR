#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../SET_CHILD_FUNC/SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"


void init_separator(Widget* obj)
{
    obj->Widget_Ptr = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

    Attributs tableau_attribut[] =
    {
        {"orientation",        strdup("")},
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
    };

    obj->Nbre_Attribut = sizeof(tableau_attribut) / sizeof(tableau_attribut[0]);
    obj->Nbre_enfant = 0;

    obj->List_Attribut = (Attributs*)malloc(obj->Nbre_Attribut * sizeof(Attributs));
    obj->List_widget_enfant = NULL;

    obj->apply_attribut_func = apply_attribut_separator;
    obj->set_child = NULL;

    // Copier les attributs
    memcpy(obj->List_Attribut, tableau_attribut, obj->Nbre_Attribut * sizeof(Attributs));

}
