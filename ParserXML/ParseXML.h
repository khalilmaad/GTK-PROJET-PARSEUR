#ifndef PARSEXML_H_INCLUDED
#define PARSEXML_H_INCLUDED


#include <gtk/gtk.h>

#define BUFFER_SIZE 4096

typedef gboolean (*Gtk_Callback_with_event)(GtkWidget*,GdkEvent*, gpointer);
typedef void (*Gtk_Callback)(GtkWidget*, gpointer);

//forward declaration
typedef struct wd Widget;

// Structure pour la pile de widgets
typedef struct StackNode {
    Widget* widget;
    struct StackNode* next;
} StackNode;

typedef struct sgl
{
    char* ID;
    int numligne;
    Widget* obj;
    struct sgl* svt;
}Gestion_Signaux;

// Structure principale du parser
typedef struct pxml
{
    FILE* Fichier;
    Widget* racine;
    StackNode* pile_widget;  // Pile pour suivre la hiérarchie
    Gestion_Signaux* Signaux;
    Gestion_Signaux* Widget_with_ID;

    void (*parse)(struct pxml*);
}ParserXML;


// Prototypes des fonctions
ParserXML* parser_create(const char* nomFichier);
void parser_destroy(ParserXML* parser);
void parser_parse(ParserXML* parser);

void traiterLigne(ParserXML* parser, const char* ligne, int numLigne);
void traiterBaliseOuvrante(ParserXML* parser, const char* ligne, size_t* pos, int numLigne);
void traiterBaliseFermante(ParserXML* parser, const char* ligne, size_t* pos, int numLigne);
void parserAttributs(
    const char* attributs_str,
    Widget* obj,
    int numLigne
);


// Fonctions utilitaires pour la pile
void pile_push(ParserXML* parser, Widget* widget);
Widget* pile_top(ParserXML* parser);
void pile_pop(ParserXML* parser);
_Bool pile_empty(ParserXML* parser);
void pile_clear(ParserXML* parser);


// Fonctions pour Attributs

void attributs_add(Widget* obj, const char* nom, const char* valeur);


// Fonctions pour la gestions des signaux

void gerer_widget_with_id(ParserXML* Parser, Widget* obj,int numligne);

void Liaison_signaux(ParserXML* Parser);


void afficher(GtkWidget*, gpointer);

void cacher(GtkWidget*, gpointer);

void detruire(GtkWidget*, gpointer);

void modifier(GtkWidget*, gpointer);

void cacher_avec_animation(GtkWidget* widget,gpointer data);

void afficher_avec_animation(GtkWidget* widget,gpointer data);

void afficher_cacher_avec_animation(GtkWidget* widget,gpointer data);

void connecte_stack_with_stackswitcher(GtkWidget*,gpointer);


gboolean afficher_avec_event(GtkWidget*,GdkEvent*, gpointer);

gboolean cacher_avec_event(GtkWidget*,GdkEvent*, gpointer);

gboolean detruire_avec_event(GtkWidget*,GdkEvent*, gpointer);

gboolean modifier_avec_event(GtkWidget*,GdkEvent*, gpointer);

gboolean afficher_avec_event_animation(GtkWidget* widget,GdkEvent *event,gpointer data);

gboolean cacher_avec_event_animation(GtkWidget* widget,GdkEvent *event,gpointer data);

gboolean afficher_cacher_avec_event_animation(GtkWidget* widget,GdkEvent *event,gpointer data);

#endif // PARSEXML_H_INCLUDED
