#include "SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"


void set_child_menu( Widget* pere,Widget* fils)
{
    if(!Controle_parente(pere,fils)) return;


    // orientation du menu
    const char* typeH = get_attribut("horizontal", pere);
    if (typeH != NULL && to_bool(typeH))
    {
        // Position
        const char* x_str = get_attribut("x", pere);
        const char* y_str = get_attribut("y", pere);

        if (x_str != NULL && y_str != NULL)
        {
            int x = atoi(x_str);
            int y = atoi(y_str);
            gtk_menu_attach(GTK_MENU(pere->Widget_Ptr),fils->Widget_Ptr,x,y,0,1);

            x++;
            y++;

            char bufferX[20];           // espace temporaire
            char bufferY[20];           // espace temporaire

            snprintf(bufferX, sizeof(bufferX), "%d", x);
            snprintf(bufferY, sizeof(bufferY), "%d", y);

            free(pere->List_Attribut[1].Valeur);
            free(pere->List_Attribut[2].Valeur);

            pere->List_Attribut[1].Valeur = strdup(bufferX);
            pere->List_Attribut[2].Valeur = strdup(bufferY);

        }
    }
    else
    {
        gtk_menu_shell_append(GTK_MENU_SHELL(pere->Widget_Ptr), fils->Widget_Ptr);
    }
    printf("\n\033[1;32m[Liaison]\033[0m Liaison au parent \033[1;34m%s\033[0m",pere->Nom);
}
