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
        {"icone",           strdup("")},
        {"type_icone",      strdup("false")},
        {"x",               strdup("")},
        {"y",               strdup("")},
        {"position_auto",   strdup("")},
        {"redimensionnable",strdup("")},
        {"type_fenetre",    strdup("normal")},
        {"modale",          strdup("false")},
        {"couleur_fond",    strdup("#FFFFFF")},

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
    obj->List_widget_enfant =(char**) malloc(obj->Nbre_enfant * sizeof(char*));

    obj->apply_attribut_func = apply_attribut_fenetre;
    obj->set_child = set_child_fenetre;

    memcpy(obj->List_Attribut, tableau_attribut, obj->Nbre_Attribut * sizeof(Attributs));
    memcpy(obj->List_widget_enfant, tableau_enfant, obj->Nbre_enfant * sizeof(char*));
}
