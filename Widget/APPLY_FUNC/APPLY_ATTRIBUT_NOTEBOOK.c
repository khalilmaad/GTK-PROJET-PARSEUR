#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_notebook(Widget* obj)
{
    GtkNotebook* notebook = GTK_NOTEBOOK(obj->Widget_Ptr);

    const char* show_border = get_attribut("show_border", obj);
    if (show_border != NULL)
    {
        gtk_notebook_set_show_border(notebook, to_bool(show_border));
    }

    const char* show_tabs = get_attribut("show_tabs", obj);
    if (show_tabs != NULL)
    {
        gtk_notebook_set_show_tabs(notebook, to_bool(show_tabs));
    }

    const char* scrollable = get_attribut("scrollable", obj);
    if (scrollable != NULL)
    {
        gtk_notebook_set_scrollable(notebook, to_bool(scrollable));
    }

    const char* pos_tab = get_attribut("pos_tab",obj);
    if (pos_tab)
    {
        static const struct
        {
            const char* nom;
            GtkPositionType type;
        } pos_tab_mapping[] =
        {
            {"haut", GTK_POS_TOP},
            {"bas",  GTK_POS_BOTTOM},
            {"gauche",  GTK_POS_LEFT},
            {"droite",    GTK_POS_RIGHT},
            {NULL, 0}  // Sentinel
        };

        // Recherche dans la table
        for (int i = 0; pos_tab_mapping[i].nom != NULL; i++)
        {
            if (strcmp(pos_tab, pos_tab_mapping[i].nom) == 0)
            {
                gtk_notebook_set_tab_pos(notebook, pos_tab_mapping[i].type);
                break;
            }
        }
    }

    // Modale
    const char* menu_contextuel = get_attribut("menu_contextuel", obj);
    if (menu_contextuel != NULL)
    {
        if(to_bool(menu_contextuel))
            gtk_notebook_popup_enable(notebook);
        else
            gtk_notebook_popup_disable(notebook);
    }

}
