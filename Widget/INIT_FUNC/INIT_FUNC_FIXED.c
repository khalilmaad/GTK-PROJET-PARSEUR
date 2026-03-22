#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../GENERAL/Widget.h"
#include "../SET_CHILD_FUNC/SET_CHILD_FUNC.h"

void init_fixed(Widget* obj)
{
    obj->Widget_Ptr = gtk_fixed_new();

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

    obj->Nbre_Attribut = 0;
    obj->Nbre_enfant = sizeof(tableau_enfant) / sizeof(tableau_enfant[0]);

    obj->List_Attribut = NULL;  // Pas d'attributs
    obj->List_widget_enfant = (char**)malloc(obj->Nbre_enfant * sizeof(char*));

    obj->apply_attribut_func = NULL;  // Pas de fonction spécifique pour Overlay
    obj->set_child = set_child_fixed;

    // Copier les enfants
    memcpy(obj->List_widget_enfant, tableau_enfant, obj->Nbre_enfant * sizeof(char*));
}
