#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include <gtk/gtk.h>
#include <cairo.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

typedef struct wd Widget;

/* ================================================================
   CONSTANTES — dimensions et comportement
   ================================================================ */
#define WIDTH  1300
#define HEIGHT 750

#define MAX_SPECIES 50

/* Boids — voisinage */
#define NEIGHBOR_RADIUS  70.0
#define SEPARATION_DIST  20.0

#define MAX_SPEED      2.5
#define MIN_SPEED      0.4 /* vitesse minimale : les poissons nagent toujours */

#define PRED_SPEED     3.2
#define PRED_SPEED_FED 1.0    /* vitesse réduite après une capture (prédateur rassasié) */

/* Forces boids */
#define COHESION   0.002
#define ALIGNMENT  0.05
#define SEPARATION 0.08

/* AVOID_PRED est une force normalisée par la distance.
 * valeur : 80.0 appliqué à (dx/d) / d → force proportionnelle à la proximité.
 */
#define AVOID_PRED 80.0

/* Fuite prédateur */
#define FLEE_RADIUS 120.0

/* Capture : distance prédateur → poisson pour déclencher la mort */
#define CAPTURE_DIST 20.0 //15.0 initial


/* Durées de mort (en secondes) */
#define DEATH_DISPLAY_TIME 2.0
#define DEATH_FADE_TIME    1.0

/* Pas de temps par tick (16ms ≈ 60fps) */
#define TICK_DT 0.016

/* Force de contrôle souris / clavier */
#define MOUSE_FORCE  0.05
#define KEY_FORCE    0.3

/* Pénalité de partage de cible entre prédateurs */
#define SHARING_PENALTY 80.0

/* Fatigue */
#define STAMINA_DRAIN    0.0008  /* consommée par tick quand un prédateur est proche */
#define STAMINA_RECOVER  0.0003  /* récupérée par tick au repos */

/* Satiété prédateur */
#define HUNGER_RECOVER   0.0004  /* la faim revient lentement après une capture */

/* Courant marin — force appliquée à tous les poissons */
#define CURRENT_X  0.015
#define CURRENT_Y  0.005

/* Angle de vision (cos de la demi-ouverture).
 * cos(135°) = -0.707 → le poisson voit 270° devant lui, ignore 90° derrière.
 */
#define VISION_COS -0.707

/* Prédateur sélectionné : force d'attraction vers la souris */
#define PRED_MOUSE_FORCE  0.12

/* Barre de vie des prédateurs */
#define PRED_HP_MAX   1.0
#define PRED_HP_DRAIN 0.00015
#define PRED_HP_EAT   0.35

/* Tolérance de clic pour sélectionner un prédateur (px) */
#define PRED_CLICK_RADIUS 25.0



/* ================================================================
   STRUCTURE FISH
   ================================================================ */
typedef struct {
    double x, y;
    double vx, vy;
    int    species;
    GdkPixbuf *sprite;

    gboolean selected;

    /* Mort */
    gboolean dead;
    double   death_timer;
    double   opacity;

    /* Fatigue : 1.0 = pleine forme, 0.0 = épuisé */
    double stamina;
    Widget* obj_ptr;
} Fish;


/* ================================================================
   STRUCTURE PREDATOR
   ================================================================ */
typedef struct {
    double x, y;
    double vx, vy;
    int    species;
    GdkPixbuf *sprite;

    int    target_fish_idx;

    /* Satiété : 0.0 = rassasié (lent), 1.0 = affamé (rapide) */
    double hunger;

    /* Barre de vie : 1.0 = plein, 0.0 = mort */
    double hp;

    /* TRUE = mort de faim (en cours d'animation de mort) */
    gboolean dead;

    /* Durée depuis la mort (s) — pilote squelette + fondu */
    double death_timer;

    /* Opacité pour le fondu : 1.0 → 0.0 */
    double opacity;

    /* TRUE = sélectionné par le joueur, suit la souris */
    gboolean selected;

    Widget* obj_ptr;
} Predator;


/* ================================================================
   VARIABLES GLOBALES
   ================================================================ */


extern char* fish_species[MAX_SPECIES];
extern int nbr_fish_species;

extern char* predator_img[MAX_SPECIES];
extern int nbr_predator_species;

extern GdkPixbuf *skeleton_img;

extern GtkWidget *area;

extern Widget* old_sim;
extern Widget* new_sim;

// Mutex unique protégeant fishes, predators, old_sim, new_sim
extern pthread_mutex_t sim_mutex;

extern Fish    *selected_fish    ;
extern int      selected_species ;
extern gboolean select_banc      ;
extern gboolean mouse_control    ;
extern double   target_x         ;
extern double   target_y         ;

/* [CORRIGÉ] Tableau de touches enfoncées pour éviter le conflit haut/bas */
extern gboolean key_up    ;
extern gboolean key_down  ;
extern gboolean key_left  ;
extern gboolean key_right ;
extern double   key_vx    ;
extern double   key_vy    ;

/* Contrôle prédateur sélectionné — symétrique à selected_fish */
extern Predator *selected_pred ;
extern gboolean  pred_control  ;
extern double    pred_target_x ;
extern double    pred_target_y ;


/* ================================================================
   UTILITAIRES
   ================================================================ */
double randf(double a, double b);

void limit_speed(double *vx, double *vy, double max);

/* Impose une vitesse minimale dans la direction actuelle */
void enforce_min_speed(double *vx, double *vy, double min);

/* [CORRIGÉ] Recalcule key_vx / key_vy depuis l'état des 4 touches */
void update_key_vector();



/* ================================================================
   STRUCTURES
   ================================================================ */

typedef struct
{
    char* filename;
    GtkWidget* emetteur_signal_sauvegarde;
    Widget* racine_arbre;
} type_sauvegarde;

typedef struct fish
{
    Fish* elem;
    struct fish* svt;
}List_fishes;

typedef struct pred
{
    Predator* elem;
    struct pred* svt;
}List_predators;

extern List_fishes* fishes;
extern List_predators* predators;






_Bool file_name_equals(const char* file1,const char* file2);

void set_fish_specie(Fish* obj,char* img);

void set_predator_specie(Predator* obj,char* img);

void init_fish(Widget* obj_ptr,_Bool pos_auto,int x, int y,char* img_path);

void init_predator(Widget* obj_ptr,_Bool pos_auto,int x, int y,char* img_path);

void update_fish();

void update_pred();


gboolean tick(gpointer data);

gboolean on_key_release(GtkWidget *widget, GdkEventKey *event, gpointer data);
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data);
gboolean on_button_release(GtkWidget *widget, GdkEventButton *event, gpointer data);
gboolean on_motion_notify(GtkWidget *widget, GdkEventMotion *event, gpointer data);
gboolean on_button_press(GtkWidget *widget, GdkEventButton *event, gpointer data);
gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data);
void draw_rotated(cairo_t   *cr,
                  GdkPixbuf *img,
                  double     x,
                  double     y,
                  double     vx,
                  double     vy,
                  double     opacity);



void save_file(GtkWidget *widget, gpointer data);

void chargement_simulation(GtkWidget *widget, gpointer data);

void reset_state(GtkWidget *widget, gpointer data);


void liberer_liste_frere(Widget* tete) ;

void liberer_arbre(Widget* racine);

#endif // SIMULATION_H_INCLUDED
