#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"

static void afficher_menu(GtkWidget* widget,gpointer data)
{
    Widget* obj = (Widget*)data;
    gtk_widget_show_all(obj->Widget_Ptr);
    gtk_menu_button_set_popup(GTK_MENU_BUTTON(widget),obj->Widget_Ptr);

}

static void afficher_menu2(GtkWidget* widget,gpointer data)
{
    GtkWidget *popover = gtk_popover_new(widget);
    Widget* obj = (Widget*)data;
    gtk_container_add(GTK_CONTAINER(popover), obj->Widget_Ptr);
    gtk_widget_show_all(obj->Widget_Ptr);

    gtk_menu_button_set_popover(GTK_MENU_BUTTON(widget), popover);

}
void set_child_menubutton( Widget* pere,Widget* fils)
{
    if(!Controle_parente(pere,fils)) return;

    if(!strcmp("menu",fils->Nom))
        g_signal_connect(pere->Widget_Ptr, "show",
                         G_CALLBACK(afficher_menu), fils);
    else
        g_signal_connect(pere->Widget_Ptr, "show",
                         G_CALLBACK(afficher_menu2), fils);

    print_succes_liaison(pere->Nom);
}
