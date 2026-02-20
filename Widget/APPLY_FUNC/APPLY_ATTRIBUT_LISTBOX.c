#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_listbox(Widget* obj)
{
    GtkListBox* listbox = GTK_LIST_BOX(obj->Widget_Ptr);


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
                gtk_list_box_set_selection_mode(listbox, typeselection_mapping[i].type);
                break;
            }
        }
    }

}
