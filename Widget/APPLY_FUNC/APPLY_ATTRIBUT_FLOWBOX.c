#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_flowbox(Widget* obj)
{
    GtkFlowBox* flowbox = GTK_FLOW_BOX(obj->Widget_Ptr);


    const char* selection = get_attribut("selection",obj);
    if (selection)
    {
        static const struct
        {
            const char* nom;
            GtkSelectionMode type;
        } typeselection_mapping[] =
        {
            {"aucun", GTK_SELECTION_NONE},
            {"seule",  GTK_SELECTION_SINGLE},
            {"obligatoire",  GTK_SELECTION_BROWSE},
            {"plsieurs",    GTK_SELECTION_MULTIPLE},
            {NULL, 0}  // Sentinel
        };

        // Recherche dans la table
        for (int i = 0; typeselection_mapping[i].nom != NULL; i++)
        {
            if (strcmp(selection, typeselection_mapping[i].nom) == 0)
            {
                gtk_flow_box_set_selection_mode(flowbox, typeselection_mapping[i].type);
                break;
            }
        }
    }

    const char* nombre_max = get_attribut("nombre_max", obj);
    if (nombre_max != NULL)
    {
        gtk_flow_box_set_max_children_per_line(flowbox,atoi(nombre_max));
    }

    const char* nombre_min = get_attribut("nombre_min", obj);
    if (nombre_min != NULL)
    {
        gtk_flow_box_set_min_children_per_line(flowbox,atoi(nombre_min));
    }

    const char* espacement_colonne = get_attribut("espacement_colonne", obj);
    if (espacement_colonne != NULL)
    {
        gtk_flow_box_set_column_spacing(flowbox,atoi(espacement_colonne));
    }

    const char* espacement_ligne = get_attribut("espacement_ligne", obj);
    if (espacement_ligne != NULL)
    {
        gtk_flow_box_set_row_spacing(flowbox,atoi(espacement_ligne));
    }
}
