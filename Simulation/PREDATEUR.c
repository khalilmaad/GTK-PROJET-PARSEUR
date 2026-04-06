#include "SIMULATION.h"
#include "../ParserXML/ParseXML.h"


void set_predator_specie(Predator* obj,char* img)
{
    for(int i = 0; i < nbr_predator_species; i++)
    {
        if(file_name_equals(predator_img[i],img))
        {
            obj->species = i;
            obj->sprite = gdk_pixbuf_new_from_file(predator_img[i],   NULL);
            return;
        }
    }

    obj->sprite = gdk_pixbuf_new_from_file(img,   NULL);
    predator_img[nbr_fish_species] = img;
    nbr_fish_species++;
}

void init_predator(Widget* obj_ptr,_Bool pos_auto,int x, int y,char* img_path)
{
    Predator* obj_pred = malloc(sizeof(Predator));
    if(!obj_pred) return;

    obj_pred->obj_ptr = obj_ptr;

    obj_pred->dead = FALSE;
    obj_pred->death_timer = 0.0;
    obj_pred->hp = PRED_HP_MAX;
    obj_pred->hunger = 1.0;
    obj_pred->opacity = 1.0;
    obj_pred->selected = FALSE;
    set_predator_specie(obj_pred,img_path);
    obj_pred->target_fish_idx = -1;
    obj_pred->vx = randf(-1, 1);
    obj_pred->vy = randf(-1, 1);

    if(pos_auto)
    {
        obj_pred->x = rand() % WIDTH;
        obj_pred->y = rand() % HEIGHT;
    }
    else{
        obj_pred->x = x;
        obj_pred->y = y;
    }

    List_predators* obj_list_pred = malloc(sizeof(List_predators));
    if(!obj_list_pred) return;

    obj_list_pred->elem = obj_pred;

    pthread_mutex_lock(&sim_mutex);

    obj_list_pred->svt = predators;
    predators = obj_list_pred;

    pthread_mutex_unlock(&sim_mutex);

}

static void* libere_memoire_predateur(void* data)
{
    List_predators* obj = (List_predators*)data;

    pthread_mutex_lock(&sim_mutex);

    attributs_add(obj->elem->obj_ptr,"dead","true");
    free(obj->elem);
    free(obj);

    pthread_mutex_unlock(&sim_mutex);

    return NULL;
}



/* ================================================================
   MISE À JOUR — PRÉDATEURS
   ================================================================ */
void update_pred()
{
    /* ── Passe 1 : sélection des cibles IA (skip les prédateurs sélectionnés) ── */
    for (List_predators* pred_crt = predators; pred_crt; pred_crt = pred_crt->svt) {

        pthread_t parsing_thread;

        while(pred_crt && pred_crt->elem->dead)
        {
            List_predators* supp = pred_crt;
            pred_crt = pred_crt->svt;
            // Créer et lancer le thread
            if (pthread_create(&parsing_thread, NULL, libere_memoire_predateur, (void*)supp) != 0)
            {
                return;
            }
            // Détacher le thread pour qu'il tourne en arrière-plan
            pthread_detach(parsing_thread);

            predators = pred_crt;

        }

        while(pred_crt && pred_crt->svt && pred_crt->svt->elem->dead)
        {
            List_predators* supp = pred_crt->svt;
            pred_crt->svt = pred_crt->svt->svt;
            // Créer et lancer le thread
            if (pthread_create(&parsing_thread, NULL, libere_memoire_predateur, (void*)supp) != 0)
            {
                return;
            }
            // Détacher le thread pour qu'il tourne en arrière-plan
            pthread_detach(parsing_thread);

        }

        if(!pred_crt) break;

        Predator *p = pred_crt->elem;
        if (p->dead)     continue;
        if (p->selected) continue;

        int    best_idx   = -1;
        double best_score = 999999.0;
        int nbr = 0;
        for (List_fishes* fish_crt = fishes; fish_crt; fish_crt = fish_crt->svt,nbr++) {
            Fish* f = fish_crt->elem;

            if (f->dead) continue;

            double dx = f->x - p->x;
            double dy = f->y - p->y;
            double d  = sqrt(dx*dx + dy*dy);

            double score = d;
            for (List_predators* autre_pred = predators; autre_pred; autre_pred = autre_pred->svt) {
                if (autre_pred != pred_crt && autre_pred->elem->target_fish_idx == nbr)
                    score += SHARING_PENALTY;
            }

            if (score < best_score) {
                best_score = score;
                best_idx   = nbr;
            }
        }

        p->target_fish_idx = best_idx;
    }

    /* ── Passe 2 : déplacement, capture, vie ── */
    for (List_predators* pred_crt = predators; pred_crt; pred_crt = pred_crt->svt) {

        Predator *p = pred_crt->elem;
        if (p->dead) continue;

        /* Drain de vie constant */
        p->hp -= PRED_HP_DRAIN;
        if (p->hp < 0.0) p->hp = 0.0;
        if (p->hp <= 0.0) {
            /* Déclencher l'animation de mort : passer en squelette */
            p->dead        = TRUE;
            p->death_timer = 0.0;
            p->opacity     = 1.0;
            p->sprite      = skeleton_img;
            p->vx          = 0.0;
            p->vy          = 0.0;
            p->selected    = FALSE;
            if (selected_pred == p) {
                selected_pred = NULL;
                pred_control  = FALSE;
                pred_target_x = pred_target_y = -1;
            }
            continue;
        }

        /* Récupération de la faim */
        p->hunger += HUNGER_RECOVER;
        if (p->hunger > 1.0) p->hunger = 1.0;

        /* ── Déplacement ── */
        if (p->selected && pred_control && pred_target_x >= 0) {
            /*
             * Contrôle joueur : identique à la logique poisson —
             * force d'attraction vers la position de la souris.
             */
            double dx = pred_target_x - p->x;
            double dy = pred_target_y - p->y;
            p->vx += dx * PRED_MOUSE_FORCE;
            p->vy += dy * PRED_MOUSE_FORCE;
        } else {
            /* IA autonome : fonce vers sa cible */
            int idx = p->target_fish_idx;
            Fish* fish_sible = fishes->elem;
            int nbr = 0;
            for(List_fishes* fish_crt = fishes ; fish_crt; fish_crt = fish_crt->svt)
            {
                if(nbr == idx)
                {
                    fish_sible = fish_crt->elem;
                    break;
                }
                nbr++;
            }
            if (idx >= 0 && !fish_sible->dead) {
                p->vx += (fish_sible->x - p->x) * 0.002;
                p->vy += (fish_sible->y - p->y) * 0.002;
            }
        }

        /* Vitesse proportionnelle à la faim */
        double spd = PRED_SPEED_FED + (PRED_SPEED - PRED_SPEED_FED) * p->hunger;
        limit_speed(&p->vx, &p->vy, spd);

        p->x += p->vx;
        p->y += p->vy;

        if (p->x < 0)      p->x = WIDTH;
        if (p->x > WIDTH)  p->x = 0;
        if (p->y < 0)      p->y = HEIGHT;
        if (p->y > HEIGHT) p->y = 0;

        /* ── Capture ── */
        for (List_fishes* fish_crt = fishes; fish_crt; fish_crt = fish_crt->svt) {
            Fish* fish_cap = fish_crt->elem;
            if (fish_cap->dead) continue;

            double dx = fish_cap->x - p->x;
            double dy = fish_cap->y - p->y;
            if (sqrt(dx*dx + dy*dy) < CAPTURE_DIST) {

                fish_cap->dead        = TRUE;
                fish_cap->death_timer = 0.0;
                fish_cap->opacity     = 1.0;
                fish_cap->sprite      = skeleton_img;
                fish_cap->vx         = 0.0;
                fish_cap->vy         = 0.0;
                fish_cap->selected   = FALSE;

                if (selected_fish == fish_cap) {
                    selected_fish  = NULL;
                    mouse_control  = FALSE;
                    target_x = target_y = -1;
                }

                p->hp    += PRED_HP_EAT;
                if (p->hp > PRED_HP_MAX) p->hp = PRED_HP_MAX;
                p->hunger  = 0.0;
                p->target_fish_idx = -1;

                break;
            }
        }
    }
}
