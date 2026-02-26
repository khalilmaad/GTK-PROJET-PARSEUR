#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_filechoosebutton(Widget* obj)
{
    GtkFileChooserButton* filechoosebutton = GTK_FILE_CHOOSER_BUTTON(obj->Widget_Ptr);

    // Label
    const char* label = get_attribut("label", obj);
    if (label != NULL)
    {
        gtk_file_chooser_button_set_title(filechoosebutton, label);
    }

    const char* type = get_attribut("type", obj);
    if (type != NULL)
    {
        // Table de correspondance
        static const struct
        {
            const char* nom;
            GtkFileChooserAction action;
        } type_mapping[] =
        {
            {"file",  GTK_FILE_CHOOSER_ACTION_OPEN},
            {"save",  GTK_FILE_CHOOSER_ACTION_SAVE},
            {"select_folder",  GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER},
            {"create_folder", GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER    },
            {NULL, 0}  // Sentinel
        };

        // Recherche dans la table
        for (int i = 0; type_mapping[i].nom != NULL; i++)
        {
            if (strcmp(type, type_mapping[i].nom) == 0)
            {
                gtk_file_chooser_set_action(GTK_FILE_CHOOSER(filechoosebutton), position_mapping[i].action);
                break;
            }
        }
    }
}
