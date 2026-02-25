#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"

static guint pulse_timeout_id = 0;


// Fonction de pulse
gboolean pulse_callback(gpointer data)
{
    GtkProgressBar *progress = GTK_PROGRESS_BAR(data);
    gtk_progress_bar_pulse(progress);
    return TRUE; // Continue
}

// Fonction appelée pour ARRÊTER l'animation
gboolean stop_animation_callback(gpointer data)
{
    GtkProgressBar *progress = GTK_PROGRESS_BAR(data);

    // Arrêter le pulse timeout
    if (pulse_timeout_id > 0)
    {
        g_source_remove(pulse_timeout_id);
        pulse_timeout_id = 0;

        // Optionnel : remettre la barre à zéro ou à un etat precis
        gtk_progress_bar_set_fraction(progress, 1.0);
        gtk_progress_bar_set_text(progress, "finished");
    }

    // Arrêter ce timeout (ne pas rappeler)
    return FALSE;
}


void apply_attribut_progressbar(Widget* obj)
{
    GtkProgressBar* progressbar = GTK_PROGRESS_BAR(obj->Widget_Ptr);

    const char* value = get_attribut("value", obj);
    if (value != NULL)
    {
        gtk_progress_bar_set_fraction(progressbar, atoi(value));
    }

    const char* afficher_texte = get_attribut("afficher_texte", obj);
    if (afficher_texte != NULL)
    {
        gtk_progress_bar_set_show_text(progressbar, to_bool(afficher_texte));
    }

    const char* texte = get_attribut("texte", obj);
    if (texte != NULL)
    {
        gtk_progress_bar_set_text(progressbar, texte);
    }

    const char* mode_indetermine = get_attribut("mode_indetermine", obj);
    if (mode_indetermine != NULL && to_bool(mode_indetermine))
    {
        // 1. Démarrer le pulse (toutes les 100ms)
        pulse_timeout_id = g_timeout_add(100, pulse_callback, progressbar);

        const char* duree_ms = get_attribut("duree_ms", obj);
        if (duree_ms != NULL) g_timeout_add(atoi(duree_ms), stop_animation_callback, progressbar);
    }

    // Orientation
    const char* orientation = get_attribut("orientation", obj);
    if (orientation != NULL)
    {
        if (strcmp(orientation, "vertical") == 0 || strcmp(orientation, "verticale") == 0)
        {
            gtk_orientable_set_orientation(GTK_ORIENTABLE(progressbar), GTK_ORIENTATION_VERTICAL);
        }
    }


    const char* mode_inverse = get_attribut("mode_inverse", obj);
    if (mode_inverse != NULL)
    {
        gtk_progress_bar_set_inverted(progressbar, to_bool(mode_inverse));
    }
}
