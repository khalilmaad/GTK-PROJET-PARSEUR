#include "Widget.h"
#include "../INIT_FUNC/INIT_FUNC.h"


static struct
{
    char* nom_widget;
    void (*init_func)(Widget*);
} List_Obj[] =
{
    {"actionbar", init_action_bar},
    {"box", init_box},
    {"button", init_button},
    {"buttonradio", init_buttonradio},
    {"calendrier", init_calendrier},
    {"checkbutton", init_check_button},
    {"entry", init_entry},
    {"fenetre", init_fenetre},
    {"frame", init_frame},
    {"headerbar", init_header_bar},
    {"image", init_image},
    {"label", init_label},
    {"menu", init_menu},
    {"menubar", init_menubar},
    {"menuitem", init_menuitem},
    {"overlay", init_overlay},
    {"scrollbar", init_scrollbar},
    {"searchentry", init_searchentry},
    {"grid", init_grid},
    {"paned", init_paned},
    {"notebook", init_notebook},
    {"stack", init_stack},
    {"stackswitcher", init_stackswitcher},
    {"expander", init_expander},
    {"fixed", init_fixed},
    {"layout", init_layout},
    {"revealer", init_revealer},
    {"listbox", init_listbox},
    {"flowbox", init_flowbox},
    {"buttonbox", init_buttonbox},
    {"toolbar", init_toolbar},
    {"toolitem", init_toolitem},
    {"separatortoolitem", init_separatortoolitem},
    {"statusbar", init_statusbar},
    {"signal", init_signal},
};


Widget*  init_func_widget(char* nom)
{
    Widget* obj = (Widget*)malloc(sizeof(Widget));
    if(!obj)
    {
        printf("\n\033[34mMessage : \033[31minit_func_widget | erreur d'allocation memoire\n\033[0m");
        return NULL;
    }
    obj->Nom = strdup(nom);
    obj->Id = NULL;
    obj->Widget_Ptr = NULL;
    obj->fils = obj->frere = NULL;

    Attributs tableau_attribut_special[]=
    {
        {"insert_cote",strdup("")},// droite/gauche
        {"marge",strdup("")},      //entier positif
        {"remplir",strdup("")},    //TRUE / FALSE
        {"etendre",strdup("")},    //TRUE /
        {"pos_colonne",strdup("")},
        {"pos_ligne",strdup("")},
        {"pos_x",strdup("")},
        {"pos_y",strdup("")},
        {"nombre_colonne",strdup("")},
        {"nombre_ligne",strdup("")},
        {"page_titre",strdup("Nouvelle page")},
        {"page_detachable",strdup("true")},
        {"page_reorderable",strdup("true")},
    };

    obj->Nbre_Attribut_special = sizeof(tableau_attribut_special)/sizeof(tableau_attribut_special[0]);
    obj->List_Attribut_special = (Attributs*)malloc(obj->Nbre_Attribut_special * sizeof(Attributs));

    memcpy(obj->List_Attribut_special, tableau_attribut_special, obj->Nbre_Attribut_special * sizeof(Attributs));

    for(int i=0; i < sizeof(List_Obj)/sizeof(List_Obj[0]); i++)
    {
        if(!compare(nom,List_Obj[i].nom_widget))
        {
            List_Obj[i].init_func(obj);
            printf("\n\033[1;32m[init]\033[0m Initialisation de \033[1;34m %s \033[0m\n",nom);
            return (Widget*) obj;
        }
    }

    printf("\n\033[1;31m[init]\033[0m Initialisation de \033[1;34m %s \033[0m\n",nom);
    printf("\n\033[1;34mMessage : \033[31minit_func_widget | balise \033[1;34m %s \033[31m non reconnue\n\033[0m",nom);
    exit(1);

    return (Widget*) obj;
}


const char* get_attribut(const char* nom_attribut,Widget* obj)
{
    for(int i=0; i<obj->Nbre_Attribut; i++)
    {
        if(!compare(nom_attribut,obj->List_Attribut[i].Nom) && obj->List_Attribut[i].Valeur[0] != '\0')
        {
            return obj->List_Attribut[i].Valeur;
        }
    }

    for(int i=0; i<obj->Nbre_Attribut_special; i++)
    {
        if(!compare(nom_attribut,obj->List_Attribut_special[i].Nom) && obj->List_Attribut_special[i].Valeur[0] != '\0')
        {
            return obj->List_Attribut_special[i].Valeur;
        }
    }
    return NULL;
}


_Bool to_bool (const char* value)
{
    return !compare(value,"1") || !compare(value,"true");
};
