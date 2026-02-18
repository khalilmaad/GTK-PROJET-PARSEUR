#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../GENERAL/Widget.h"
#include "../SET_CHILD_FUNC/SET_CHILD_FUNC.h"

void init_fenetre(Widget* obj)
{
    obj->Widget_Ptr = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    Attributs tableau_attribut[]=
    {
        {"titre",           strdup("")},
        {"largeur",         strdup("800")},
        {"hauteur",         strdup("600")},
        {"couleur_fond",    strdup("#FFFFFF")},
        {"icone",           strdup("")},
        {"type_icone",      strdup("false")},
        {"x",               strdup("")},
        {"y",               strdup("")},
        {"position_auto",   strdup("")},
        {"redimensionnable",strdup("")},
        {"type_fenetre",    strdup("normal")},
        {"modale",          strdup("false")},
    };

    char* tableau_enfant[] = {"grid","searchentry","entry","scrollbar","overlay","menuitem","menubar","menu","label","image",
                    "headerbar","frame","checkbutton","calendrier","buttonradio","button","box","actionbar","signal"};

    obj->Nbre_Attribut = sizeof(tableau_attribut) / sizeof(tableau_attribut[0]);
    obj->Nbre_enfant = sizeof(tableau_enfant) / sizeof(tableau_enfant[0]);

    obj->List_Attribut = (Attributs*)malloc(obj->Nbre_Attribut * sizeof(Attributs));
    obj->List_widget_enfant =(char**) malloc(obj->Nbre_enfant * sizeof(char*));

    obj->apply_attribut_func = apply_attribut_fenetre;
    obj->set_child = set_child_fenetre;

    memcpy(obj->List_Attribut, tableau_attribut, obj->Nbre_Attribut * sizeof(Attributs));
    memcpy(obj->List_widget_enfant, tableau_enfant, obj->Nbre_enfant * sizeof(char*));
}
