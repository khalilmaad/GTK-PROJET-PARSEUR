#include "ParseXML.h"
#include "../Widget/GENERAL/Widget.h"



gboolean afficher_avec_event(GtkWidget* widget,GdkEvent *event,gpointer data)
{
    Widget* obj = (Widget*)data;
    gtk_widget_show_all(obj->Widget_Ptr);
    printf("\nafficher_avec_event\n");

    return TRUE;
}

gboolean afficher_avec_event_animation(GtkWidget* widget,GdkEvent *event,gpointer data)
{
    Widget* obj = (Widget*)data;
    gtk_revealer_set_reveal_child(GTK_REVEALER(obj->Widget_Ptr), TRUE);
    printf("\nafficher_avec_event_animation\n");

    return TRUE;
}

gboolean cacher_avec_event_animation(GtkWidget* widget,GdkEvent *event,gpointer data)
{
    Widget* obj = (Widget*)data;
    gtk_revealer_set_reveal_child(GTK_REVEALER(obj->Widget_Ptr), FALSE);
    printf("\ncacher_avec_event_animation\n");

    return TRUE;
}

gboolean afficher_cacher_avec_event_animation(GtkWidget* widget,GdkEvent *event,gpointer data)
{
    Widget* obj = (Widget*)data;
    gboolean state = gtk_revealer_get_reveal_child(GTK_REVEALER(obj->Widget_Ptr));
    gtk_revealer_set_reveal_child(GTK_REVEALER(obj->Widget_Ptr), !state);
    printf("\nafficher_cacher_avec_event_animation\n");

    return TRUE;
}

gboolean cacher_avec_event(GtkWidget* widget,GdkEvent *event,gpointer data)
{
    Widget* obj = (Widget*)data;

    gtk_widget_hide(obj->Widget_Ptr);
    printf("\ncacher_avec_event\n");

    return TRUE;
}


gboolean detruire_avec_event(GtkWidget* widget,GdkEvent *event,gpointer data)
{
    Widget* obj = (Widget*)data;
    GtkWidget *parent = gtk_widget_get_parent(obj->Widget_Ptr);
    gtk_widget_destroy(obj->Widget_Ptr);

    if(parent) gtk_widget_show_all(parent);

    return TRUE;
}


gboolean modifier_avec_event(GtkWidget* widget,GdkEvent *event,gpointer data)
{
    Widget* obj = (Widget*)data;
    GtkWidget *parent = gtk_widget_get_parent(obj->Widget_Ptr);
    gtk_widget_destroy(obj->Widget_Ptr);

    if(parent) gtk_widget_show_all(parent);

    return TRUE;
}


void afficher(GtkWidget* widget,gpointer data)
{
    Widget* obj = (Widget*)data;
    gtk_widget_show_all(obj->Widget_Ptr);
    printf("\nafficher\n");
}

void cacher_avec_animation(GtkWidget* widget,gpointer data)
{
    Widget* obj = (Widget*)data;
    gtk_revealer_set_reveal_child(GTK_REVEALER(obj->Widget_Ptr), FALSE);
    printf("\ncacher_avec_animation\n");
}

void afficher_avec_animation(GtkWidget* widget,gpointer data)
{
    Widget* obj = (Widget*)data;
    gtk_revealer_set_reveal_child(GTK_REVEALER(obj->Widget_Ptr), TRUE);
    printf("\nafficher_avec_animation\n");
}

void afficher_cacher_avec_animation(GtkWidget* widget,gpointer data)
{
    Widget* obj = (Widget*)data;
    gboolean state = gtk_revealer_get_reveal_child(GTK_REVEALER(obj->Widget_Ptr));
    gtk_revealer_set_reveal_child(GTK_REVEALER(obj->Widget_Ptr), !state);
    printf("\nafficher_cacher_avec_animation\n");
}

void connecte_stack_with_stackswitcher(GtkWidget* widget,gpointer data)
{
    Widget* obj = (Widget*)data;

    gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(widget),
                                  GTK_STACK(obj->Widget_Ptr));
    printf("\nconnexion reussi\n");
}

void cacher(GtkWidget* widget,gpointer data)
{
    Widget* obj = (Widget*)data;

    gtk_widget_hide(obj->Widget_Ptr);
    printf("\ncacher\n");
}


void detruire(GtkWidget* widget,gpointer data)
{
    Widget* obj = (Widget*)data;
    GtkWidget *parent = gtk_widget_get_parent(obj->Widget_Ptr);
    gtk_widget_destroy(obj->Widget_Ptr);

    if(parent) gtk_widget_show_all(parent);
}


void modifier(GtkWidget* widget,gpointer data)
{
    Widget* obj = (Widget*)data;
    GtkWidget *parent = gtk_widget_get_parent(obj->Widget_Ptr);
    gtk_widget_destroy(obj->Widget_Ptr);

    if(parent) gtk_widget_show_all(parent);
}
