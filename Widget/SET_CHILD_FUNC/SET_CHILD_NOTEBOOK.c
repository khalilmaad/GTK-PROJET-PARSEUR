#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"


void set_child_notebook( Widget* pere, Widget* fils)
{
    if(!Controle_parente(pere,fils)) return;

    const char* page_titre = get_attribut("page_titre",fils);
    if (page_titre)
    {
        GtkWidget* page = gtk_label_new(page_titre);
        gtk_notebook_append_page_menu(GTK_NOTEBOOK(pere->Widget_Ptr), fils->Widget_Ptr, page, NULL);

        const char* page_detachable = get_attribut("page_detachable",fils);
        if(page_detachable)
        {
            gtk_notebook_set_tab_detachable(GTK_NOTEBOOK(pere->Widget_Ptr), fils->Widget_Ptr,to_bool(page_detachable));
        }

        const char* page_reorderable = get_attribut("page_reorderable",fils);
        if(page_reorderable)
        {
            gtk_notebook_set_tab_reorderable(GTK_NOTEBOOK(pere->Widget_Ptr), fils->Widget_Ptr, to_bool(page_reorderable));
        }
    }
    else
    {
        printf("\n\033[1;31m[Liaison]\033[0m Liaison au parent \033[1;34m%s\033[0m",pere->Nom);
        printf("\n\033[1;34mMessage : \033[1;31mEchec liaison au parente -> manque attribut indiquant le titre de la page (page_titre=\"valeur\")");
        exit(1);
    }
    printf("\n\033[1;32m[Liaison]\033[0m Liaison au parent \033[1;34m%s\033[0m",pere->Nom);
}
