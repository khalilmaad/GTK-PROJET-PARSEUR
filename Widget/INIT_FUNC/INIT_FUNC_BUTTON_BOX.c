#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../SET_CHILD_FUNC/SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"


void init_buttonbox(Widget* obj)
{
    obj->Widget_Ptr = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);

    Attributs tableau_attribut[] =
    {
        {"orientation",        strdup("")},
        {"disposition",        strdup("")},
        {"espacement_enfant",  strdup("")},
    };

    char* tableau_enfant[] = {"flowbox","listbox","revealer","layout","fixed","expander","notebook","stack","stackswitcher","grid",
    "searchentry","entry","scrollbar","overlay","menuitem","menubar","menu","label","image",
    "headerbar","frame","checkbutton","calendrier","buttonradio","button","box","actionbar","signal"};

    obj->Nbre_Attribut = sizeof(tableau_attribut) / sizeof(tableau_attribut[0]);
    obj->Nbre_enfant = sizeof(tableau_enfant) / sizeof(tableau_enfant[0]);

    obj->List_Attribut = (Attributs*)malloc(obj->Nbre_Attribut * sizeof(Attributs));
    obj->List_widget_enfant = (char**)malloc(obj->Nbre_enfant * sizeof(char*));

    obj->apply_attribut_func = apply_attribut_buttonbox;
    obj->set_child = set_child_default;

    // Copier les attributs
    memcpy(obj->List_Attribut, tableau_attribut, obj->Nbre_Attribut * sizeof(Attributs));

    // Copier les enfants
    memcpy(obj->List_widget_enfant, tableau_enfant, obj->Nbre_enfant * sizeof(char*));
}
