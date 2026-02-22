#include "INIT_FUNC.h"
#include "../APPLY_FUNC/APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void init_statusbar(Widget* obj)
{
    obj->Widget_Ptr = gtk_statusbar_new();
    obj->Nbre_Attribut = 0;  // Pas d'attributs spécifiques pour Calendrier
    obj->Nbre_enfant = 0;    // Pas d'enfants spécifiques pour Calendrier

    // Pas d'attributs ni d'enfants pour Calendrier
    obj->List_Attribut = NULL;
    obj->List_widget_enfant = NULL;

    // Fonction d'application des attributs
    obj->apply_attribut_func = NULL;  // Pas de fonction spécifique pour Calendrier
    obj->set_child = NULL;
}
