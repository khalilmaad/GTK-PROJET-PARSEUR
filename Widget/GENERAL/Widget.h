#ifndef WIDGET_H_INCLUDED
#define WIDGET_H_INCLUDED

#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>


/*
 * Macro de comparaison de chaînes.
 * compare(x,y) retourne 0 si les chaînes sont identiques.
 */
#define compare(x,y) strcmp(x,y)


/*
 * Structure représentant un attribut générique.
 * Exemple : largeur="200"
 * Nom    -> "largeur"
 * Valeur -> "200"
 */
typedef struct
{
    char* Nom;        // Nom de l'attribut
    char* Valeur;     // Valeur de l'attribut (chaîne)
}Attributs;


/*
 * Structure principale représentant un widget abstrait
 * utilisé par ton moteur / parseur.
 *
 * Cette structure ne représente PAS directement un GtkWidget,
 * mais une couche intermédiaire logique.
 */
typedef struct wd
{
    char* Nom;                      // Nom du widget (ex: "button", "grid")
    char* Id;                       // Identifiant unique qui servira pour
                                    //la connexion des signaux

    GtkWidget* Widget_Ptr;          // Pointeur vers le vrai widget GTK

    Attributs* List_Attribut;       // Liste des attributs standards
    Attributs* List_Attribut_special; // Liste des attributs spéciaux génériques

    char Nbre_Attribut;             // Nombre d'attributs standards (<128)
    char Nbre_enfant;               // Nombre d'enfants directs
    char Nbre_Attribut_special;     // Nombre d'attributs spéciaux

    char** List_widget_enfant;      // Tableau des noms des widgets enfants

    /*
     * Structure en arbre :
     * fils  -> premier enfant
     * frere -> widget suivant au même niveau
     */
    struct wd* fils;                // Premier enfant
    struct wd* frere;               // Frère suivant

    /*
     * Pointeurs de fonctions pour comportement dynamique :
     */

    void (*apply_attribut_func)(struct wd*);
    // Fonction appliquant les attributs au widget GTK réel

    void (*set_child)( struct wd* pere, struct wd* fils);
    // Fonction définissant la relation parent -> enfant

} Widget;

typedef struct
{
    const char* nom;
    float position;
}mapping_value;


/*
 * Crée dynamiquement un widget selon son nom.
 * Recherche dans la table de dispatch et appelle la bonne fonction init.
 */
Widget*  init_func_widget(char* nom);


/*
 * Recherche la valeur d’un attribut (standard ou spécial)
 * dans un objet Widget.
 * Retourne NULL si non trouvé.
 */
const char* get_attribut(const char*,Widget*);

_Bool Attribut_existe(const char*, Widget* );


/*
 * Convertit une chaîne en booléen.
 * Retourne vrai si la valeur est "1" ou "true".
 */
_Bool to_bool (const char*);

void print_succes_liaison(const char* Nom_parent);

void print_succes_liaison_signal(const char* Nom_parent);

void print_error_liaison_signal(const char* message,const char* sible,_Bool motif);

void print_error_liaison(const char* Nom_parent);

long string_to_long(const char* nom_attribut,const char* valeur);

double string_to_double(const char* nom_attribut,const char* valeur);

void print_error_mapping_value(const char* nom_attribut,mapping_value* tab);

void print_message_error_liaison(const char* message);

void print_error_mapping_liaison(Widget* pere,Widget* fils);

#endif // WIDGET_H_INCLUDED
