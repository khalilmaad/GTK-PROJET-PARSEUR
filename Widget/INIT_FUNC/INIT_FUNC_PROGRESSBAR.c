#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../GENERAL/Widget.h"
#include "../SET_CHILD_FUNC/SET_CHILD_FUNC.h"


void init_progressbar(Widget* obj)
{
    obj->Widget_Ptr = gtk_progress_bar_new();

    Attributs tableau_attribut[] =
    {
        {"value",                       strdup("0,0")},
        {"afficher_texte",              strdup("true")}, //true or false
        {"texte",                       strdup("Chargement...")},
        {"mode_indetermine",            strdup("true")},
        {"duree_ms",                    strdup("10000")},
        {"orientation",                 strdup("true")},
        {"mode_inverse",                strdup("false")},
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

    char* tableau_enfant[] =
    {
        "signal"
    };

    obj->Nbre_Attribut = sizeof(tableau_attribut) / sizeof(tableau_attribut[0]);
    obj->Nbre_enfant = sizeof(tableau_enfant) / sizeof(tableau_enfant[0]);

    obj->List_Attribut = (Attributs*)malloc(obj->Nbre_Attribut * sizeof(Attributs));
    obj->List_widget_enfant = (char**)malloc(obj->Nbre_enfant * sizeof(char*));

    obj->apply_attribut_func = apply_attribut_progressbar;
    obj->set_child = set_child_default;

    // Copier les attributs
    memcpy(obj->List_Attribut, tableau_attribut, obj->Nbre_Attribut * sizeof(Attributs));

    // Copier les enfants
    memcpy(obj->List_widget_enfant, tableau_enfant, obj->Nbre_enfant * sizeof(char*));
}
