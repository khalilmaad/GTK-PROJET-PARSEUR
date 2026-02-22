#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"

void apply_attribut_searchbar(Widget* obj)
{
    GtkSearchBar* searchbar = GTK_SEARCH_BAR(obj->Widget_Ptr);

    const char* afficher = get_attribut("afficher", obj);
    if (afficher != NULL)
    {
        gtk_search_bar_set_search_mode(searchbar, to_bool(afficher));
    }
}
