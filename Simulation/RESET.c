#include "SIMULATION.h"


void reset_state(GtkWidget *widget, gpointer data)
{
    pthread_mutex_lock(&sim_mutex);
    for (List_fishes* crt = fishes; crt; crt = crt->svt)
    {
        crt->elem->dead = TRUE;
    }

    for (List_predators* pred_crt = predators; pred_crt; pred_crt = pred_crt->svt)
    {
        pred_crt->elem->dead = TRUE;
    }
    pthread_mutex_unlock(&sim_mutex);
}
