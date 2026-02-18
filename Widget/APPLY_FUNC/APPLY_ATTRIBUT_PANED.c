#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"

void on_paned_moved(GObject *object, GParamSpec *pspec, gpointer user_data) {

    /*Widget* obj=(Widget*)(user_data);

    GtkPaned *paned = GTK_PANED(obj->Widget_Ptr);
    int position = gtk_paned_get_position(paned);

    int min_limit = Ptr->limit_min; // Minimum en pixels
    int max_limit = Ptr->limit_max; // Maximum en pixels

    if (position < min_limit) {
        gtk_paned_set_position(paned, min_limit);
    } else if (position > max_limit) {
        gtk_paned_set_position(paned, max_limit);
    }*/
}


void apply_attribut_paned(Widget* obj)
{
    GtkWidget* paned = obj->Widget_Ptr;

    // Orientation
    const char* orientation = get_attribut("orientation", obj);
    if (orientation != NULL)
    {
        if (strcmp(orientation, "vertical") == 0 || strcmp(orientation, "verticale") == 0)
        {
            gtk_orientable_set_orientation(GTK_ORIENTABLE(paned), GTK_ORIENTATION_VERTICAL);
        }
    }

    // Espacement entre enfants
    const char* diviseur_pos_str = get_attribut("diviseur_pos", obj);
    if (diviseur_pos_str != NULL)
    {
        int diviseur_pos = atoi(diviseur_pos_str);

        gtk_paned_set_position(GTK_PANED(paned), diviseur_pos);
    }

    const char* couleur_fond = get_attribut("couleur_fond", obj);
    if (couleur_fond != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-background-color",couleur_fond);
    }

    g_signal_connect(obj->Widget_Ptr, "notify::position", G_CALLBACK(on_paned_moved), obj);
}
