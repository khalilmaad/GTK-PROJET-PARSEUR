#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../SET_CHILD_FUNC/SET_CHILD_FUNC.h"
#include "../GENERAL/Widget.h"


/*
 * Fonction d'initialisation spécifique au widget ActionBar.
 * Elle configure la structure interne "Widget" ainsi que
 * le widget GTK réel correspondant.
 */
void init_action_bar(Widget* obj)
{
    // Création du widget GTK réel (GtkActionBar)
    obj->Widget_Ptr = gtk_action_bar_new();

    // ActionBar ne possède pas d'attributs personnalisés
    obj->List_Attribut = NULL;

    // Nombre d'attributs spécifiques = 0
    obj->Nbre_Attribut = 0;

    /*
     * Liste des types de widgets autorisés comme enfants
     * dans un ActionBar.
     * (Selon ton moteur, tu limites volontairement les types possibles)
     */
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

    // Calcul automatique du nombre d'enfants autorisés
    obj->Nbre_enfant = sizeof(tableau_enfant) / sizeof(tableau_enfant[0]);

    // Allocation dynamique du tableau qui contiendra les noms des enfants autorisés
    obj->List_widget_enfant = (char**)malloc(obj->Nbre_enfant * sizeof(char*));

    /*
     * Pointeur vers la fonction d'application des attributs.
     * Ici NULL car aucun attribut spécifique à appliquer.
     */
    obj->apply_attribut_func = NULL;

    /*
     * Pointeur vers la fonction qui gère l'ajout d'un enfant
     * dans l'ActionBar (ex: gtk_action_bar_pack_start / pack_end).
     */
    obj->set_child = set_child_actionbar;

    // Copie des noms des widgets enfants autorisés
    memcpy(obj->List_widget_enfant,
           tableau_enfant,
           obj->Nbre_enfant * sizeof(char*));
}
