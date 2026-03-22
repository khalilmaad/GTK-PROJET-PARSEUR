#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../SET_CHILD_FUNC/SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"


void init_paned(Widget* obj)
{
    obj->Widget_Ptr = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);

    Attributs tableau_attribut[] =
    {
        {"orientation",        strdup("")},
        {"diviseur_pos",        strdup("100")},
        {"diviseur_min_limit",  strdup("80")},
        {"diviseur_max_limit",  strdup("700")},
        {"couleur_fond",        strdup("")},
    };

    char* tableau_enfant[] =
    {
        "actionbar","box","button","buttonradio","calendrier",
        "checkbutton","entry","frame","headerbar","image",
        "label","menu","menubar","menuitem","overlay","scrollbar",
        "searchentry","grid","paned","notebook","stack","stackswitcher",
        "expander","fixed","layout","revealer","listbox","flowbox","buttonbox",
        "toolbar","toolitem","separatortoolitem","statusbar","infobar",
        "searchbar","togglebutton","linkbutton","spinbutton","switch",
        "scalebutton","menubutton","progressbar","levelbar","spinner",
        "scale","colorbutton","fontbutton","filechoosebutton","checkmenuitem",
        "radiomenuitem","separatormenuitem","comboboxtext","comboboxtextentry",
        "separator","signal"
    };

    obj->Nbre_Attribut = sizeof(tableau_attribut) / sizeof(tableau_attribut[0]);
    obj->Nbre_enfant = sizeof(tableau_enfant) / sizeof(tableau_enfant[0]);

    obj->List_Attribut = (Attributs*)malloc(obj->Nbre_Attribut * sizeof(Attributs));
    obj->List_widget_enfant = (char**)malloc(obj->Nbre_enfant * sizeof(char*));

    obj->apply_attribut_func = apply_attribut_paned;
    obj->set_child = set_child_paned;

    // Copier les attributs
    memcpy(obj->List_Attribut, tableau_attribut, obj->Nbre_Attribut * sizeof(Attributs));

    // Copier les enfants
    memcpy(obj->List_widget_enfant, tableau_enfant, obj->Nbre_enfant * sizeof(char*));
}
