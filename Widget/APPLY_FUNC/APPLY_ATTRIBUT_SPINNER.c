#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"





// Fonction appelée pour ARRÊTER l'animation
static gboolean stop_animation_callback(gpointer data)
{
    GtkSpinner *spinner = GTK_SPINNER(data);

    gtk_spinner_stop(spinner);

    // Arrêter ce timeout (ne pas rappeler)
    return FALSE;
}


void apply_attribut_spinner(Widget* obj)
{
    GtkSpinner *spinner = GTK_SPINNER(obj->Widget_Ptr);

    const char* duree_ms = get_attribut("duree_ms", obj);
    if (duree_ms != NULL)
    {
        gtk_spinner_start(spinner);
        g_timeout_add(atoi(duree_ms), stop_animation_callback, spinner);
    }
}
