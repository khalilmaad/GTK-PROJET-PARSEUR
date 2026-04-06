#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../GENERAL/Widget.h"
#include "../SET_CHILD_FUNC/SET_CHILD_FUNC.h"


void init_filechooserdialog(Widget* obj)
{
    obj->Widget_Ptr = gtk_file_chooser_dialog_new(
                          "Ouvrir un fichier",
                          NULL,
                          GTK_FILE_CHOOSER_ACTION_OPEN,
                          "Annuler", GTK_RESPONSE_CANCEL,
                          "Ouvrir",  GTK_RESPONSE_ACCEPT,
                          NULL);

    Attributs tableau_attribut[] =
    {
        {"type",               strdup("")},
        {"titre",              strdup("")},
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

    obj->apply_attribut_func = apply_attribut_filechooserdialog;
    obj->set_child = set_child_default;

    // Copier les attributs
    memcpy(obj->List_Attribut, tableau_attribut, obj->Nbre_Attribut * sizeof(Attributs));

    // Copier les enfants
    memcpy(obj->List_widget_enfant, tableau_enfant, obj->Nbre_enfant * sizeof(char*));
}
