#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"


void set_child_stack( Widget* pere, Widget* fils)
{
    if(!Controle_parente(pere,fils)) return;

    const char* page_titre = get_attribut("page_titre",fils);
    if (page_titre)
    {
        const char* nombre_page = get_attribut("nombre_page",pere);
        gtk_stack_add_titled(GTK_STACK(pere->Widget_Ptr),fils->Widget_Ptr,strdup(nombre_page),page_titre);

        char buffer[20];

        int n = atoi(nombre_page);

        snprintf(buffer, sizeof(buffer), "%d", ++n);

        free(pere->List_Attribut[0].Valeur);
        pere->List_Attribut[0].Valeur = strdup(buffer);
    }
    else
    {
        printf("\n\033[1;31m[Liaison]\033[0m Liaison au parent \033[1;34m%s\033[0m",pere->Nom);
        printf("\n\033[1;34mMessage : \033[1;31mEchec liaison au parente -> manque attribut indiquant le titre de la page (page_titre=\"valeur\")");
        exit(1);
    }
    printf("\n\033[1;32m[Liaison]\033[0m Liaison au parent \033[1;34m%s\033[0m",pere->Nom);
}
