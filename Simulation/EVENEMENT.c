#include "SIMULATION.h"

/* ================================================================
   ÉVÉNEMENTS — SOURIS
   ================================================================ */
gboolean on_button_press(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    double mx = event->x;
    double my = event->y;

    if (event->button == 1) {
        /* ── Clic gauche : sélectionner un poisson ── */

        /* Désélectionner tout */
        for (List_fishes* crt = fishes; crt; crt = crt->svt) crt->elem->selected = FALSE;
        selected_fish    = NULL;
        selected_species = -1;
        select_banc      = FALSE;
        mouse_control    = FALSE;
        target_x = target_y = -1;

        /* Désélectionner le requin éventuellement sélectionné */
        if (selected_pred) { selected_pred->selected = FALSE; }
        selected_pred = NULL;
        pred_control  = FALSE;
        pred_target_x = pred_target_y = -1;

        /* Chercher le poisson vivant le plus proche (tolérance 20px) */
        double best = 20.0;
        for (List_fishes* crt = fishes; crt; crt = crt->svt) {
            if (crt->elem->dead) continue;
            double dx = crt->elem->x - mx;
            double dy = crt->elem->y - my;
            double d  = sqrt(dx*dx + dy*dy);
            if (d < best) { best = d; selected_fish = crt->elem; }
        }

        if (selected_fish) {
            selected_fish->selected = TRUE;
            mouse_control = TRUE;
            target_x = mx;
            target_y = my;

            if (event->state & GDK_SHIFT_MASK) {
                selected_species = selected_fish->species;
                select_banc      = TRUE;
                for (List_fishes* crt = fishes; crt; crt = crt->svt) {
                    if (!crt->elem->dead && crt->elem->species == selected_species)
                        crt->elem->selected = TRUE;
                }
            }
        }

    } else if (event->button == 3) {
        /* ── Clic droit : sélectionner un requin ── */

        /* Désélectionner poissons */
        for (List_fishes* crt = fishes; crt; crt = crt->svt) crt->elem->selected = FALSE;
        selected_fish    = NULL;
        selected_species = -1;
        select_banc      = FALSE;
        mouse_control    = FALSE;
        target_x = target_y = -1;

        /* Désélectionner le requin précédent */
        if (selected_pred) { selected_pred->selected = FALSE; }
        selected_pred = NULL;
        pred_control  = FALSE;
        pred_target_x = pred_target_y = -1;

        /* Chercher le requin vivant le plus proche (tolérance PRED_CLICK_RADIUS) */
        double best = PRED_CLICK_RADIUS;
        for (List_predators* pred_crt = predators; pred_crt; pred_crt = pred_crt->svt) {
            if (pred_crt->elem->dead) continue;
            double dx = pred_crt->elem->x - mx;
            double dy = pred_crt->elem->y - my;
            double d  = sqrt(dx*dx + dy*dy);
            if (d < best) { best = d; selected_pred = pred_crt->elem; }
        }

        if (selected_pred) {
            selected_pred->selected = TRUE;
            pred_control  = TRUE;
            pred_target_x = mx;
            pred_target_y = my;
        }
    }

    return TRUE;
}

gboolean on_motion_notify(GtkWidget *widget, GdkEventMotion *event, gpointer data)
{
    if (mouse_control)
        target_x = event->x, target_y = event->y;

    if (pred_control && selected_pred && !selected_pred->dead)
        pred_target_x = event->x, pred_target_y = event->y;

    return TRUE;
}

gboolean on_button_release(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    if (event->button == 3 && selected_pred) {
        /*
         * Relâcher le clic droit : désélectionner le requin.
         * Il reprend immédiatement son comportement IA autonome
         * (la passe 1 de update_pred() recalculera sa cible au prochain tick).
         */
        selected_pred->selected = FALSE;
        selected_pred = NULL;
        pred_control  = FALSE;
        pred_target_x = pred_target_y = -1;
    }
    return TRUE;
}


/* ================================================================
   ÉVÉNEMENTS — CLAVIER
   ================================================================ */
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    switch (event->keyval)
    {
        case GDK_KEY_Up:    case GDK_KEY_z: case GDK_KEY_Z:
            key_up    = TRUE;  break;
        case GDK_KEY_Down:  case GDK_KEY_s: case GDK_KEY_S:
            key_down  = TRUE;  break;
        case GDK_KEY_Left:  case GDK_KEY_q: case GDK_KEY_Q:
            key_left  = TRUE;  break;
        case GDK_KEY_Right: case GDK_KEY_d: case GDK_KEY_D:
            key_right = TRUE;  break;

        case GDK_KEY_Escape:
            for (List_fishes* crt = fishes; crt; crt = crt->svt) crt->elem->selected = FALSE;
            selected_fish    = NULL;
            selected_species = -1;
            select_banc      = FALSE;
            mouse_control    = FALSE;
            key_up = key_down = key_left = key_right = FALSE;
            target_x = target_y = -1;
            if (selected_pred) { selected_pred->selected = FALSE; }
            selected_pred = NULL;
            pred_control  = FALSE;
            pred_target_x = pred_target_y = -1;
            break;

        default: break;
    }
    update_key_vector(); /* [CORRIGÉ] recalcul immédiat */
    return TRUE;
}

gboolean on_key_release(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    switch (event->keyval)
    {
        case GDK_KEY_Up:    case GDK_KEY_z: case GDK_KEY_Z:
            key_up    = FALSE; break;
        case GDK_KEY_Down:  case GDK_KEY_s: case GDK_KEY_S:
            key_down  = FALSE; break;
        case GDK_KEY_Left:  case GDK_KEY_q: case GDK_KEY_Q:
            key_left  = FALSE; break;
        case GDK_KEY_Right: case GDK_KEY_d: case GDK_KEY_D:
            key_right = FALSE; break;

        default: break;
    }
    update_key_vector(); /* [CORRIGÉ] recalcul immédiat */
    return TRUE;
}

