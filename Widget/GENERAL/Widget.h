#ifndef WIDGET_H_INCLUDED
#define WIDGET_H_INCLUDED

#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <errno.h>

#define compare(x,y) strcmp(x,y)


typedef struct
{
    char* Nom;
    char* Valeur;
}Attributs;


typedef struct wd
{
    char* Nom;
    char* Id;
    GtkWidget* Widget_Ptr;
    Attributs* List_Attribut;
    Attributs* List_Attribut_special;
    char Nbre_Attribut;     //Nombre attribut < 128
    char Nbre_enfant;
    char Nbre_Attribut_special;

    char** List_widget_enfant;

    struct wd* fils;
    struct wd* frere;

    void (*apply_attribut_func)(struct wd*);
    void (*set_child)( struct wd* pere, struct wd* fils);
} Widget;

Widget*  init_func_widget(char* nom);
const char* get_attribut(const char*,Widget*);
_Bool to_bool (const char*);



#endif // WIDGET_H_INCLUDED
