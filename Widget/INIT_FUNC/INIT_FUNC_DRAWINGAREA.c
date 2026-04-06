#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../GENERAL/Widget.h"
#include "../SET_CHILD_FUNC/SET_CHILD_FUNC.h"
#include "../../Simulation/SIMULATION.h"
GtkWidget *area = NULL;

void init_drawingarea(Widget* obj)
{
    obj->Widget_Ptr = gtk_drawing_area_new();
    gtk_widget_add_events(obj->Widget_Ptr,
        GDK_BUTTON_PRESS_MASK   |
        GDK_BUTTON_RELEASE_MASK |
        GDK_POINTER_MOTION_MASK
    );

    pthread_mutex_lock(&sim_mutex);

    if(!area) area = obj->Widget_Ptr;

    pthread_mutex_unlock(&sim_mutex);

    g_signal_connect(obj->Widget_Ptr, "draw",                 G_CALLBACK(draw_cb),           NULL);
    g_signal_connect(obj->Widget_Ptr, "button-press-event",   G_CALLBACK(on_button_press),   NULL);
    g_signal_connect(obj->Widget_Ptr, "button-release-event", G_CALLBACK(on_button_release), NULL);
    g_signal_connect(obj->Widget_Ptr, "motion-notify-event",  G_CALLBACK(on_motion_notify),  NULL);

    char* tableau_enfant[] =
    {
        "signal","simulation"
    };

    obj->Nbre_Attribut = 0;
    obj->Nbre_enfant = sizeof(tableau_enfant) / sizeof(tableau_enfant[0]);

    obj->List_Attribut = NULL;
    obj->List_widget_enfant = (char**)malloc(obj->Nbre_enfant * sizeof(char*));

    obj->apply_attribut_func = NULL;
    obj->set_child = set_child_drawingarea;



    // Copier les enfants
    memcpy(obj->List_widget_enfant, tableau_enfant, obj->Nbre_enfant * sizeof(char*));
}
