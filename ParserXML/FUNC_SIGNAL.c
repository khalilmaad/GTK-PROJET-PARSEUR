#include "ParseXML.h"
#include "../Widget/GENERAL/Widget.h"



gboolean afficher_avec_event(GtkWidget* widget,GdkEvent *event,gpointer data)
{
    Widget* obj = (Widget*)data;
    gtk_widget_show_all(obj->fils->Widget_Ptr);
    printf("\nafficher_avec_event\n");

    return TRUE;
}

gboolean afficher_avec_event_animation(GtkWidget* widget,GdkEvent *event,gpointer data)
{
    Widget* obj = (Widget*)data;
    gtk_revealer_set_reveal_child(GTK_REVEALER(obj->fils->Widget_Ptr), TRUE);
    printf("\nafficher_avec_event_animation\n");

    return TRUE;
}

gboolean cacher_avec_event_animation(GtkWidget* widget,GdkEvent *event,gpointer data)
{
    Widget* obj = (Widget*)data;
    gtk_revealer_set_reveal_child(GTK_REVEALER(obj->fils->Widget_Ptr), FALSE);
    printf("\ncacher_avec_event_animation\n");

    return TRUE;
}

gboolean afficher_cacher_avec_event_animation(GtkWidget* widget,GdkEvent *event,gpointer data)
{
    Widget* obj = (Widget*)data;
    gboolean state = gtk_revealer_get_reveal_child(GTK_REVEALER(obj->fils->Widget_Ptr));
    gtk_revealer_set_reveal_child(GTK_REVEALER(obj->fils->Widget_Ptr), !state);
    printf("\nafficher_cacher_avec_event_animation\n");

    return TRUE;
}

gboolean cacher_avec_event(GtkWidget* widget,GdkEvent *event,gpointer data)
{
    Widget* obj = (Widget*)data;

    gtk_widget_hide(obj->fils->Widget_Ptr);
    printf("\ncacher_avec_event\n");

    return TRUE;
}


gboolean detruire_avec_event(GtkWidget* widget,GdkEvent *event,gpointer data)
{
    Widget* obj = (Widget*)data;
    GtkWidget *parent = gtk_widget_get_parent(obj->fils->Widget_Ptr);
    gtk_widget_destroy(obj->fils->Widget_Ptr);

    if(parent) gtk_widget_show_all(parent);

    return TRUE;
}


gboolean modifier_avec_event(GtkWidget* widget,GdkEvent *event,gpointer data)
{
    Widget* obj = (Widget*)data;
    const char* nom_attribut = get_attribut("nom_attribut",obj);
    if(nom_attribut)
    {
        const char* valeur_attribut = get_attribut("valeur_attribut",obj);
        if(valeur_attribut && Attribut_existe(nom_attribut,obj->fils))
        {
            attributs_add(obj->fils,nom_attribut,valeur_attribut);
            obj->fils->apply_attribut_func(obj->fils);
            gtk_widget_show_all(obj->fils->Widget_Ptr);
        }
    }

    return TRUE;
}


void afficher(GtkWidget* widget,gpointer data)
{
    Widget* obj = (Widget*)data;
    gtk_widget_show_all(obj->fils->Widget_Ptr);
    printf("\nafficher\n");
}

void cacher_avec_animation(GtkWidget* widget,gpointer data)
{
    Widget* obj = (Widget*)data;
    gtk_revealer_set_reveal_child(GTK_REVEALER(obj->fils->Widget_Ptr), FALSE);
    printf("\ncacher_avec_animation\n");
}

void afficher_avec_animation(GtkWidget* widget,gpointer data)
{
    Widget* obj = (Widget*)data;
    gtk_revealer_set_reveal_child(GTK_REVEALER(obj->fils->Widget_Ptr), TRUE);
    printf("\nafficher_avec_animation\n");
}

void afficher_cacher_avec_animation(GtkWidget* widget,gpointer data)
{
    Widget* obj = (Widget*)data;
    gboolean state = gtk_revealer_get_reveal_child(GTK_REVEALER(obj->fils->Widget_Ptr));
    gtk_revealer_set_reveal_child(GTK_REVEALER(obj->fils->Widget_Ptr), !state);
    printf("\nafficher_cacher_avec_animation\n");
}

void connecte_stack_with_stackswitcher(GtkWidget* widget,gpointer data)
{
    Widget* obj = (Widget*)data;

    gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(widget),
                                  GTK_STACK(obj->fils->Widget_Ptr));
    printf("\nconnexion reussi\n");
}

void cacher(GtkWidget* widget,gpointer data)
{
    Widget* obj = (Widget*)data;

    gtk_widget_hide(obj->fils->Widget_Ptr);
    printf("\ncacher\n");
}

void afficher_cacher(GtkWidget* widget,gpointer data)
{
    Widget* obj = (Widget*)data;

    gboolean visible = gtk_widget_is_visible(obj->fils->Widget_Ptr);

    (visible) ?
    gtk_widget_show_all(obj->fils->Widget_Ptr) :
    gtk_widget_hide(obj->fils->Widget_Ptr);
    printf("\nafficher cacher\n");
}


void detruire(GtkWidget* widget,gpointer data)
{
    Widget* obj = (Widget*)data;
    GtkWidget *parent = gtk_widget_get_parent(obj->fils->Widget_Ptr);
    gtk_widget_destroy(obj->fils->Widget_Ptr);

    if(parent) gtk_widget_show_all(parent);
}

// Callback pour GtkColorButton (color-set)
// Récupère la couleur choisie et l'applique sur le widget cible
void modifier_couleur_avec_colorbutton(GtkWidget* widget, gpointer data)
{
    Widget* obj = (Widget*)data;

    const char* nom_attribut = get_attribut("nom_attribut", obj);
    if (!nom_attribut) return;
    if (!Attribut_existe(nom_attribut, obj->fils)) return;

    // Récupérer la couleur choisie par l'utilisateur
    GdkRGBA couleur;
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(widget), &couleur);

    // Convertir GdkRGBA en string CSS  ex: "rgba(255,0,0,1)"
    gchar* couleur_str = gdk_rgba_to_string(&couleur);

    // Appliquer sur le widget cible
    attributs_add(obj->fils, nom_attribut, couleur_str);
    obj->fils->apply_attribut_func(obj->fils);
    gtk_widget_show_all(obj->fils->Widget_Ptr);

    g_free(couleur_str);
}

void modifier_police(GtkWidget* widget, gpointer data)
{
    Widget* obj = (Widget*)data;

    const gchar* police = gtk_font_button_get_font_name(GTK_FONT_BUTTON(widget));
    if (!police) return;

    PangoFontDescription* desc = pango_font_description_from_string(police);

    // ── Famille ──────────────────────────────────────────────

    if (Attribut_existe("font_family", obj->fils))
    {
        const char* famille = pango_font_description_get_family(desc);
        if (famille)
            attributs_add(obj->fils, "font_family", famille);
    }

    // ── Taille ───────────────────────────────────────────────

    if (Attribut_existe("font_size", obj->fils))
    {
        gint taille = pango_font_description_get_size(desc) / PANGO_SCALE;
        char taille_str[16];
        snprintf(taille_str, sizeof(taille_str), "%dpx", taille);
        attributs_add(obj->fils, "font_size", taille_str);
    }

    // ── Graisse (bold) ────────────────────────────────────────
    // Pango retourne une valeur numérique :
    // PANGO_WEIGHT_NORMAL = 400, PANGO_WEIGHT_BOLD = 700

    if (Attribut_existe("font_weight", obj->fils))
    {
        PangoWeight weight = pango_font_description_get_weight(desc);
        const char* weight_str = (weight >= PANGO_WEIGHT_BOLD) ? "bold" : "normal";
        attributs_add(obj->fils, "font_weight", weight_str);
    }

    // ── Style (italic) ────────────────────────────────────────
    // Pango : PANGO_STYLE_NORMAL, PANGO_STYLE_ITALIC, PANGO_STYLE_OBLIQUE
    // Récupéré via un 4ème attribut dans le signal — on utilise "attribut_sible2"
    // Mais comme on n'a que 4 attributs dans le signal, on peut l'ajouter dans
    // INIT_FUNC_SIGNAL.c si nécessaire. Pour l'instant on le gère ainsi :
    PangoStyle style = pango_font_description_get_style(desc);
    const char* style_str;
    if      (style == PANGO_STYLE_ITALIC)  style_str = "italic";
    else if (style == PANGO_STYLE_OBLIQUE) style_str = "oblique";
    else                                   style_str = "normal";

    // Appliquer le style directement si l'attribut "font_style" existe sur la cible
    if (Attribut_existe("font_style", obj->fils))
        attributs_add(obj->fils, "font_style", style_str);

    // Appliquer tous les changements
    obj->fils->apply_attribut_func(obj->fils);
    gtk_widget_show_all(obj->fils->Widget_Ptr);

    pango_font_description_free(desc);
}

// Callback pour GtkFileChooserButton (file-set)
// Récupère le chemin du fichier choisi
void recuper_modifier_avec_filechooser(GtkWidget* widget, gpointer data)
{
    Widget* obj = (Widget*)data;

    // Récupérer le chemin complet du fichier choisi
    // ex: "C:/Users/khalil/images/photo.png"
    gchar* chemin = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widget));
    if (!chemin) return;

    const char* nom_attribut = get_attribut("nom_attribut", obj);
    if (nom_attribut && Attribut_existe(nom_attribut, obj->fils))
    {
        // Appliquer le chemin sur l'attribut cible du widget cible
        attributs_add(obj->fils, nom_attribut, chemin);
        obj->fils->apply_attribut_func(obj->fils);
        gtk_widget_show_all(obj->fils->Widget_Ptr);
    }

    g_free(chemin);
}

void modifier(GtkWidget* widget,gpointer data)
{
    Widget* obj = (Widget*)data;
    const char* nom_attribut = get_attribut("nom_attribut",obj);
    if(nom_attribut)
    {
        const char* valeur_attribut = get_attribut("valeur_attribut",obj);
        if(valeur_attribut && Attribut_existe(nom_attribut,obj->fils))
        {
            attributs_add(obj->fils,nom_attribut,valeur_attribut);
            obj->fils->apply_attribut_func(obj->fils);
            gtk_widget_show_all(obj->fils->Widget_Ptr);
        }
    }
}


void recuper_modifier(GtkWidget* widget,gpointer data)
{
    Widget* obj = (Widget*)data;
    const char* nom_attribut = get_attribut("nom_attribut",obj);
    if(nom_attribut)
    {
        const char* valeur_attribut = gtk_entry_get_text(GTK_ENTRY(widget));
        if(valeur_attribut && Attribut_existe(nom_attribut,obj->fils))
        {
            attributs_add(obj->fils,nom_attribut,valeur_attribut);
            obj->fils->apply_attribut_func(obj->fils);
            gtk_widget_show_all(obj->fils->Widget_Ptr);
            // Effacer après traitement
            gtk_entry_set_text(GTK_ENTRY(widget), "");
        }
    }
}


// Callback pour la touche Entrée
void afficher_text_entry_terminal(GtkWidget* widget,gpointer data)
{
    Widget* obj = (Widget*)data;
    const gchar* text = gtk_entry_get_text(GTK_ENTRY(obj->Widget_Ptr));

    printf("\nTexte saisi: %s\n", text);

    // Effacer après traitement
    gtk_entry_set_text(GTK_ENTRY(obj->Widget_Ptr), "");
}
