#include "SIMULATION.h"
#include "../ParserXML/ParseXML.h"

void set_fish_specie(Fish* obj,char* img)
{
    for(int i = 0; i < nbr_fish_species; i++)
    {

        if(file_name_equals(fish_species[i],img))
        {

            obj->species = i;
            obj->sprite = gdk_pixbuf_new_from_file(fish_species[i],   NULL);
            return;
        }
    }

    obj->species = nbr_fish_species;
    obj->sprite = gdk_pixbuf_new_from_file(img,   NULL);
    fish_species[nbr_fish_species] = img;
    nbr_fish_species++;
}


void init_fish(Widget* obj_ptr,_Bool pos_auto,int x, int y,char* img_path)
{
    Fish* obj_fish = malloc(sizeof(Fish));
    if(!obj_fish) return;

    obj_fish->obj_ptr = obj_ptr;

    obj_fish->dead = FALSE;
    obj_fish->death_timer = 0.0;
    obj_fish->opacity = 1.0;
    obj_fish->selected = FALSE;

    set_fish_specie(obj_fish,img_path);

    obj_fish->stamina = 1.0;
    obj_fish->vx = randf(-1, 1);
    obj_fish->vy = randf(-1, 1);
    if(pos_auto)
    {
        obj_fish->x = rand() % WIDTH;
        obj_fish->y = rand() % HEIGHT;
    }
    else
    {
        obj_fish->x = x;
        obj_fish->y = y;
    }

    List_fishes* obj_list_fishes = malloc(sizeof(List_fishes));
    if(!obj_list_fishes) return;

    obj_list_fishes->elem = obj_fish;

    pthread_mutex_lock(&sim_mutex);

    obj_list_fishes->svt = fishes;
    fishes = obj_list_fishes;

    pthread_mutex_unlock(&sim_mutex);

}

static void* libere_memoire_poisson(void* data)
{
    List_fishes* obj = (List_fishes*)data;

    pthread_mutex_lock(&sim_mutex);

    attributs_add(obj->elem->obj_ptr,"dead","true");
    free(obj->elem);
    free(obj);

    pthread_mutex_unlock(&sim_mutex);

    return NULL;
}

/* ================================================================
   MISE À JOUR — POISSONS
   ================================================================ */
void update_fish()
{
    for (List_fishes* crt = fishes; crt; crt = crt->svt)
    {

        pthread_t parsing_thread;

        while(crt && crt->elem->dead)
        {
            List_fishes* supp = crt;
            crt = crt->svt;
            // Créer et lancer le thread
            if (pthread_create(&parsing_thread, NULL, libere_memoire_poisson, (void*)supp) != 0)
            {
                return;
            }
            // Détacher le thread pour qu'il tourne en arrière-plan
            pthread_detach(parsing_thread);

            fishes = crt;

        }


        while(crt && crt->svt && crt->svt->elem->dead)
        {
            List_fishes* supp = crt->svt;
            crt->svt = crt->svt->svt;
            // Créer et lancer le thread
            if (pthread_create(&parsing_thread, NULL, libere_memoire_poisson, (void*)supp) != 0)
            {
                return;
            }
            // Détacher le thread pour qu'il tourne en arrière-plan
            pthread_detach(parsing_thread);

        }

        if(!crt) break;

        Fish *f = crt->elem;
        if (f->dead) continue;

        /* ── Boids ──────────────────────────────────────────────── */
        double cx = 0, cy = 0;
        double avx = 0, avy = 0;
        double sx = 0, sy = 0;
        int count = 0;

        for (List_fishes* autre = fishes; autre; autre = autre->svt)
        {
            Fish* autre_f = autre->elem;
            if (crt == autre)                          continue;
            if (autre_f->dead)                  continue;
            if (autre_f->species != f->species) continue;

            double dx = autre_f->x - f->x;
            double dy = autre_f->y - f->y;
            double d  = sqrt(dx*dx + dy*dy);
            if (d < 0.0001) continue;

            /* [NOUVEAU] Angle de vision : ignorer les voisins dans le dos */
            double speed = sqrt(f->vx*f->vx + f->vy*f->vy);
            if (speed > 0.0001)
            {
                double dot = (f->vx * dx + f->vy * dy) / (speed * d);
                if (dot < VISION_COS) continue;
            }

            if (d < NEIGHBOR_RADIUS)
            {
                cx  += autre_f->x;
                cy  += autre_f->y;
                avx += autre_f->vx;
                avy += autre_f->vy;
                count++;

                if (d < SEPARATION_DIST)
                {
                    sx -= dx / d;
                    sy -= dy / d;
                }
            }
        }

        if (count > 0)
        {
            cx /= count;
            cy /= count;
            f->vx += (cx - f->x) * COHESION;
            f->vy += (cy - f->y) * COHESION;

            avx /= count;
            avy /= count;
            f->vx += (avx - f->vx) * ALIGNMENT;
            f->vy += (avy - f->vy) * ALIGNMENT;

            f->vx += sx * SEPARATION;
            f->vy += sy * SEPARATION;
        }

        /* ── Fuite des prédateurs ───────────────────────────────── */
        gboolean fleeing = FALSE;

        for (List_predators* p = predators; p ; p = p->svt)
        {
            Predator* pred_crt = p->elem;
            if (pred_crt->dead) continue;
            double dx = pred_crt->x - f->x;
            double dy = pred_crt->y - f->y;
            double d  = sqrt(dx*dx + dy*dy);
            if (d < 0.0001) continue;

            if (d < FLEE_RADIUS)
            {
                /*
                 * [CORRIGÉ] Force normalisée : on divise par d deux fois.
                 * Premier d  → normalise le vecteur (direction pure)
                 * Deuxième d → pondère par la proximité (plus c'est proche,
                 *              plus c'est fort)
                 * Résultat  : force = AVOID_PRED / d²
                 */
                f->vx -= (dx / d) * (AVOID_PRED / d);
                f->vy -= (dy / d) * (AVOID_PRED / d);
                fleeing = TRUE;
            }
        }

        /* [NOUVEAU] Fatigue */
        if (fleeing)
        {
            f->stamina -= STAMINA_DRAIN;
            if (f->stamina < 0.0) f->stamina = 0.0;
        }
        else
        {
            f->stamina += STAMINA_RECOVER;
            if (f->stamina > 1.0) f->stamina = 1.0;
        }

        /* [NOUVEAU] Courant marin global */
        f->vx += CURRENT_X;
        f->vy += CURRENT_Y;

        /* ── Contrôle utilisateur ───────────────────────────────── */
        if (f->selected && mouse_control && target_x >= 0)
        {
            double dx = target_x - f->x;
            double dy = target_y - f->y;
            f->vx += dx * MOUSE_FORCE;
            f->vy += dy * MOUSE_FORCE;
        }

        if (f->selected && (key_vx != 0.0 || key_vy != 0.0))
        {
            f->vx += key_vx * KEY_FORCE;
            f->vy += key_vy * KEY_FORCE;
        }

        /* ── Limites de vitesse ─────────────────────────────────── */
        /* [NOUVEAU] Vitesse max réduite si fatigué */
        double speed_cap = MAX_SPEED * (0.5 + 0.5 * f->stamina);
        limit_speed(&f->vx, &f->vy, speed_cap);

        /* [NOUVEAU] Vitesse minimale */
        enforce_min_speed(&f->vx, &f->vy, MIN_SPEED);

        /* ── Déplacement ────────────────────────────────────────── */
        f->x += f->vx;
        f->y += f->vy;

        /* Wrap-around */
        if (f->x < 0)      f->x = WIDTH;
        if (f->x > WIDTH)  f->x = 0;
        if (f->y < 0)      f->y = HEIGHT;
        if (f->y > HEIGHT) f->y = 0;
    }
}

