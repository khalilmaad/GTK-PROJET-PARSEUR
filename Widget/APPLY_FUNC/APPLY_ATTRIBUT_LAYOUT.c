#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_layout(Widget* obj)
{
    GtkLayout* layout = GTK_LAYOUT(obj->Widget_Ptr);

    // Label
    const char* taille_str = get_attribut("taille", obj);
    if (taille_str != NULL)
    {
        gtk_layout_set_size(layout, atoi(taille_str), atoi(taille_str));
    }
}
