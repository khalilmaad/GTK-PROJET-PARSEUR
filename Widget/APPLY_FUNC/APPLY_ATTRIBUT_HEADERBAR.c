#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_headerbar(Widget* obj)
{
    GtkHeaderBar* headerbar = GTK_HEADER_BAR(obj->Widget_Ptr);

    // Définir le décoration de la fenêtre
    const char* disposition = get_attribut("disposition", obj);
    if (disposition != NULL)
    {
        gtk_header_bar_set_decoration_layout(headerbar, disposition);
    }

    // Titre
    const char* titre = get_attribut("titre", obj);
    if (titre != NULL)
    {
        gtk_header_bar_set_title(headerbar, titre);
    }

    // Sous-titre
    const char* soustitre = get_attribut("sous_titre", obj);
    if (soustitre != NULL)
    {
        gtk_header_bar_set_subtitle(headerbar, soustitre);
    }

    // Afficher/masquer les boutons de fermeture
    const char* afficher_button_fermeture = get_attribut("afficher_boutton_fermeture", obj);
    if (afficher_button_fermeture != NULL)
    {
        gtk_header_bar_set_show_close_button(headerbar, to_bool(afficher_button_fermeture));
    }


    const char* couleur_label = get_attribut("couleur_label", obj);
    if (couleur_label != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-color",couleur_label);
    }

    const char* font_style = get_attribut("font_style", obj);
    if (font_style != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-font-style",font_style);
    }

    const char* font_size = get_attribut("font_size", obj);
    if (font_size != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-font-size",font_size);
    }

    const char* font_family = get_attribut("font_family", obj);
    if (font_family != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-font-family",font_family);
    }
}
