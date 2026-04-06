#include "SIMULATION.h"

/* ================================================================
   RENDU — sprite orienté avec opacité
   ================================================================ */
void draw_rotated(cairo_t   *cr,
                  GdkPixbuf *img,
                  double     x,
                  double     y,
                  double     vx,
                  double     vy,
                  double     opacity)
{
    if (!img) return;

    double angle = atan2(vy, vx);
    int w = gdk_pixbuf_get_width(img);
    int h = gdk_pixbuf_get_height(img);

    cairo_save(cr);
    cairo_translate(cr, x, y);
    cairo_rotate(cr, angle);
    gdk_cairo_set_source_pixbuf(cr, img, -w / 2, -h / 2);
    cairo_paint_with_alpha(cr, opacity);
    cairo_restore(cr);
}


/* ================================================================
   RENDU — callback draw
   ================================================================ */
gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    /* Fond */
    cairo_set_source_rgb(cr, 0.05, 0.1, 0.2);
    cairo_paint(cr);

    /* ── Poissons ── */
    for (List_fishes* crt = fishes; crt; crt = crt->svt) {

        Fish *f = crt->elem;

        /* Sprite principal */
        draw_rotated(cr, f->sprite, f->x, f->y, f->vx, f->vy, f->opacity);

        /* Cercle de sélection */
        if (f->selected && !f->dead) {
            cairo_set_source_rgba(cr, 1.0, 0.9, 0.2, 0.85);
            cairo_set_line_width(cr, 1.8);
            cairo_arc(cr, f->x, f->y, 18.0, 0, 2 * G_PI);
            cairo_stroke(cr);
        }

        /* Barre de stamina sous le poisson sélectionné */
        if (f->selected && !f->dead) {
            double bw = 30.0;
            double bh = 3.0;
            double bx = f->x - bw / 2;
            double by = f->y + 22.0;

            cairo_set_source_rgba(cr, 0.2, 0.2, 0.2, 0.7);
            cairo_rectangle(cr, bx, by, bw, bh);
            cairo_fill(cr);

            double r = 1.0 - f->stamina;
            double g = f->stamina;
            cairo_set_source_rgba(cr, r, g, 0.1, 0.9);
            cairo_rectangle(cr, bx, by, bw * f->stamina, bh);
            cairo_fill(cr);
        }
    }

    /* Ligne de guidage souris */
    if (mouse_control && target_x >= 0 && selected_fish && !selected_fish->dead) {
        cairo_set_source_rgba(cr, 1.0, 1.0, 0.3, 0.4);
        cairo_set_line_width(cr, 1.0);
        cairo_set_dash(cr, (double[]){6, 4}, 2, 0);
        cairo_move_to(cr, selected_fish->x, selected_fish->y);
        cairo_line_to(cr, target_x, target_y);
        cairo_stroke(cr);
        cairo_set_dash(cr, NULL, 0, 0);
    }

    /* ── Prédateurs ── */
    for (List_predators* pred_crt = predators; pred_crt; pred_crt = pred_crt->svt) {

        Predator *p = pred_crt->elem;
        /* Prédateur en animation de mort : dessiner le squelette en fondu */
        if (p->dead) {
            if (p->opacity > 0.0)
                draw_rotated(cr, p->sprite, p->x, p->y, 1.0, 0.0, p->opacity);
            continue;
        }

        double pred_op = 0.4 + 0.6 * p->hunger;
        draw_rotated(cr, p->sprite, p->x, p->y, p->vx, p->vy, pred_op);

        /* Cercle de sélection orange autour du prédateur contrôlé */
        if (p->selected) {
            cairo_set_source_rgba(cr, 1.0, 0.5, 0.1, 0.9);
            cairo_set_line_width(cr, 2.0);
            cairo_arc(cr, p->x, p->y, 22.0, 0, 2 * G_PI);
            cairo_stroke(cr);

            /* Ligne pointillée vers la cible souris */
            if (pred_control && pred_target_x >= 0) {
                cairo_set_source_rgba(cr, 1.0, 0.5, 0.1, 0.35);
                cairo_set_line_width(cr, 1.0);
                cairo_set_dash(cr, (double[]){5, 4}, 2, 0);
                cairo_move_to(cr, p->x, p->y);
                cairo_line_to(cr, pred_target_x, pred_target_y);
                cairo_stroke(cr);
                cairo_set_dash(cr, NULL, 0, 0);
            }
        }

        /* Barre de vie au-dessus du prédateur */
        double bw = 36.0;
        double bh = 4.0;
        double bx = p->x - bw / 2;
        double by = p->y - 28.0;

        cairo_set_source_rgba(cr, 0.15, 0.05, 0.05, 0.8);
        cairo_rectangle(cr, bx, by, bw, bh);
        cairo_fill(cr);

        double hp = p->hp;
        double r  = (hp > 0.5) ? 2.0 * (1.0 - hp) : 1.0;
        double g  = (hp > 0.5) ? 1.0 : 2.0 * hp;
        cairo_set_source_rgba(cr, r, g, 0.0, 0.95);
        cairo_rectangle(cr, bx, by, bw * hp, bh);
        cairo_fill(cr);

        cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 0.3);
        cairo_set_line_width(cr, 0.5);
        cairo_rectangle(cr, bx, by, bw, bh);
        cairo_stroke(cr);
    }

    /* ── HUD ── */
    cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 0.6);
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 12.0);

    if (selected_pred && !selected_pred->dead) {
        cairo_move_to(cr, 10, 20);
        cairo_show_text(cr, "Requin selectionne | Souris = diriger | ESC = annuler");
    } else if (selected_fish && !selected_fish->dead) {
        cairo_move_to(cr, 10, 20);
        if (select_banc)
            cairo_show_text(cr, "Banc selectionne | Souris = diriger | ESC = annuler");
        else
            cairo_show_text(cr, "Poisson selectionne | Souris = diriger | ESC = annuler");
    } else {
        cairo_move_to(cr, 10, 20);
        cairo_show_text(cr, "Clic gauche = poisson | Clic droit = requin | Shift+Clic = banc");
    }

    return FALSE;
}

