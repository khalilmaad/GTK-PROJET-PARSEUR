#include "SIMULATION.h"
char* fish_species[MAX_SPECIES];
char* predator_img[MAX_SPECIES];

Widget* old_sim = NULL;
Widget* new_sim = NULL;

pthread_mutex_t sim_mutex = PTHREAD_MUTEX_INITIALIZER;

Fish    *selected_fish    = NULL;
int      selected_species = -1;
gboolean select_banc      = FALSE;
gboolean mouse_control    = FALSE;
double   target_x         = -1;
double   target_y         = -1;

/* [CORRIGÉ] Tableau de touches enfoncées pour éviter le conflit haut/bas */
gboolean key_up    = FALSE;
gboolean key_down  = FALSE;
gboolean key_left  = FALSE;
gboolean key_right = FALSE;
double   key_vx    = 0.0;
double   key_vy    = 0.0;

/* Contrôle prédateur sélectionné — symétrique à selected_fish */
Predator *selected_pred  = NULL;
gboolean  pred_control   = FALSE;
double    pred_target_x  = -1;
double    pred_target_y  = -1;

int nbr_fish_species = 0;
int nbr_predator_species = 0;
GdkPixbuf *skeleton_img;
List_fishes* fishes = NULL;
List_predators* predators = NULL;




_Bool file_name_equals(const char* file1,const char* file2)
{
    char* filename1 = strrchr(file1, '\\') + 1;
    char* filename2 = strrchr(file2, '\\') + 1;

    if(!strcmp(filename1,filename2)) return TRUE;

    return FALSE;
}






/* ================================================================
   UTILITAIRES
   ================================================================ */
double randf(double a, double b)
{
    return a + (b - a) * (rand() / (double)RAND_MAX);
}

void limit_speed(double *vx, double *vy, double max)
{
    double s = sqrt((*vx) * (*vx) + (*vy) * (*vy));
    if (s < 0.0001) return;
    if (s > max) {
        *vx = (*vx / s) * max;
        *vy = (*vy / s) * max;
    }
}

/* Impose une vitesse minimale dans la direction actuelle */
void enforce_min_speed(double *vx, double *vy, double min)
{
    double s = sqrt((*vx) * (*vx) + (*vy) * (*vy));
    if (s < 0.0001) {
        /* Pas de direction : donner une impulsion aléatoire */
        *vx = randf(-1, 1);
        *vy = randf(-1, 1);
        s   = sqrt((*vx)*(*vx) + (*vy)*(*vy));
    }
    if (s < min) {
        *vx = (*vx / s) * min;
        *vy = (*vy / s) * min;
    }
}

/* Recalcule key_vx / key_vy depuis l'état des 4 touches */

void update_key_vector()
{
    key_vx = (key_right ? 1.0 : 0.0) - (key_left ? 1.0 : 0.0);
    key_vy = (key_down  ? 1.0 : 0.0) - (key_up   ? 1.0 : 0.0);
}


/* ================================================================
   BOUCLE PRINCIPALE — tick ~60fps
   ================================================================ */
gboolean tick(gpointer data)
{
    pthread_mutex_lock(&sim_mutex);

    update_fish();
    update_pred();

    /* Gestion des morts — squelette → fondu → disparition définitive */
    for (List_fishes* crt = fishes; crt; crt = crt->svt) {

        Fish *f = crt->elem;
        if (!f->dead) continue;

        f->death_timer += TICK_DT;

        if (f->death_timer < DEATH_DISPLAY_TIME) {
            f->opacity = 1.0;
        }
        else if (f->death_timer < DEATH_DISPLAY_TIME + DEATH_FADE_TIME) {
            double t = f->death_timer - DEATH_DISPLAY_TIME;
            f->opacity = 1.0 - (t / DEATH_FADE_TIME);
        }
        else {
            f->opacity = 0.0;
        }
    }

    /* Gestion de la mort des prédateurs : squelette → fondu → disparition définitive */
    for (List_predators* pred_crt = predators; pred_crt; pred_crt = pred_crt->svt) {

        Predator *p = pred_crt->elem;
        if (!p->dead) continue;

        p->death_timer += TICK_DT;

        if (p->death_timer < DEATH_DISPLAY_TIME) {
            p->opacity = 1.0;
        }
        else if (p->death_timer < DEATH_DISPLAY_TIME + DEATH_FADE_TIME) {
            double t = p->death_timer - DEATH_DISPLAY_TIME;
            p->opacity = 1.0 - (t / DEATH_FADE_TIME);
        }
        else {
            /*
             * Animation terminée : le prédateur est retiré définitivement.
             * On marque opacity = 0 et on ne le réinitialise pas —
             * il reste absent pour le reste de la simulation.
             */
            p->opacity = 0.0;
        }
    }
    pthread_mutex_unlock(&sim_mutex);

    gtk_widget_queue_draw(area);
    return TRUE;
}
