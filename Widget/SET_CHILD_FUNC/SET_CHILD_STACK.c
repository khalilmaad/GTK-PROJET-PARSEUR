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

        int n = (int)string_to_long("nombre_page",nombre_page);

        snprintf(buffer, sizeof(buffer), "%d", ++n);

        free(pere->List_Attribut[0].Valeur);
        pere->List_Attribut[0].Valeur = strdup(buffer);
    }
    else
    {
        print_error_liaison(pere->Nom);
        print_message_error_liaison("(page_titre=\"valeur\")");
    }
    print_succes_liaison(pere->Nom);
}
