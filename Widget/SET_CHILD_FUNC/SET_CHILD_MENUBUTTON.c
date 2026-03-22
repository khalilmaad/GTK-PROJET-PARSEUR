#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"

static void afficher_menu(GtkWidget* widget,gpointer data)
{
    Widget* obj = (Widget*)data;
    gtk_widget_show_all(obj->Widget_Ptr);
    gtk_menu_button_set_popup(GTK_MENU_BUTTON(widget),obj->Widget_Ptr);
    printf("\nafficher\n");
}

void set_child_menubutton( Widget* pere,Widget* fils)
{
    if(!Controle_parente(pere,fils)) return;

    g_signal_connect(pere->Widget_Ptr, "show",
                     G_CALLBACK(afficher_menu), fils);

    print_succes_liaison(pere->Nom);
}
