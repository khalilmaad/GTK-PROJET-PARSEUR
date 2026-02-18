#include "ParseXML.h"
#include "../Widget/GENERAL/Widget.h"



gboolean afficher_avec_event(GtkWidget* widget,GdkEvent *event,gpointer data)
{
    Widget* obj = (Widget*)data;
    gtk_widget_show_all(obj->Widget_Ptr);
    printf("\nafficher_avec_event\n");

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
