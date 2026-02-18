#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


// Callback pour la touche Entrée
static void on_entry_activate(GtkEntry* entry, gpointer user_data)
{
    const gchar* text = gtk_entry_get_text(entry);

    printf("\nTexte saisi: %s\n", text);

    // Effacer après traitement
    gtk_entry_set_text(entry, "");
}

void apply_attribut_entry(Widget* obj)
{
    GtkEntry* entry = GTK_ENTRY(obj->Widget_Ptr);

    // texte initial
    const char* texte_initial = get_attribut("texte_initial", obj);
    if (texte_initial != NULL)
    {
        gtk_entry_set_text(entry, texte_initial);
    }

    // texte placeholder
    const char* placeholder = get_attribut("placeholder", obj);
    if (placeholder != NULL)
    {
        gtk_entry_set_placeholder_text(entry, placeholder);
    }

    // longueur maximale
    const char* longueur_max_str = get_attribut("longueur_max", obj);
    if (longueur_max_str != NULL)
    {
        int longueur_max = atoi(longueur_max_str);

        if (longueur_max > 0)
        {
            gtk_entry_set_max_length(entry, longueur_max);
        }
        else
        {
            gtk_entry_set_max_length(entry, 50);
        }
    }

    // visibilité
    const char* visibilite = get_attribut("visibilite", obj);
    if (visibilite != NULL)
    {
        gtk_entry_set_visibility(entry, to_bool(visibilite));
    }

    // Afficher le caractère de masquage personnalisé
    const char* invisible_char = get_attribut("invisible_char", obj);
    if (invisible_char != NULL && strlen(invisible_char) > 0)
    {
        gtk_entry_set_invisible_char(entry, invisible_char[0]);
    }

    // editable
    const char* editable = get_attribut("editable", obj);
    if (editable != NULL)
    {
        gtk_editable_set_editable(GTK_EDITABLE(entry), to_bool(editable));
    }

    // Alignement du texte
    const char* alignement_texte = get_attribut("alignement_texte", obj);
    if (alignement_texte != NULL)
    {
        // Table de correspondance
        static const struct
        {
            const char* nom;
            float alignement;
        } alignement_mapping[] =
        {
            {"droite", 1.0},
            {"centre", 0.5},
            {"gauche", 0.0},
            {NULL, 0.0}  // Sentinel
        };

        // Recherche dans la table
        for (int i = 0; alignement_mapping[i].nom != NULL; i++)
        {
            if (strcmp(alignement_texte, alignement_mapping[i].nom) == 0)
            {
                gtk_entry_set_alignment(entry, alignement_mapping[i].alignement);
                break;
            }
        }
    }

    // SearchEntry (avec icône de recherche)
    const char* sensibilite_icone = get_attribut("sensibilite_icone", obj);
    const char* position_icone = get_attribut("position_icone", obj);
    const char* icone = get_attribut("icone", obj);

    if (sensibilite_icone != NULL && position_icone != NULL && icone != NULL)
    {
        // Table de correspondance pour la position de l'icône
        static const struct
        {
            const char* nom;
            GtkEntryIconPosition position;
        } icon_mapping[] =
        {
            {"droite", GTK_ENTRY_ICON_SECONDARY},
            {"gauche", GTK_ENTRY_ICON_PRIMARY},
            {NULL, 0}  // Sentinel
        };

        // Recherche dans la table
        for (int i = 0; icon_mapping[i].nom != NULL; i++)
        {
            if (strcmp(position_icone, icon_mapping[i].nom) == 0)
            {
                // Position de l'icône
                gtk_entry_set_icon_from_icon_name(entry,
                                                  icon_mapping[i].position,
                                                  icone);

                // Sensibilité de l'icône
                gtk_entry_set_icon_sensitive(entry,
                                             icon_mapping[i].position,
                                             to_bool(sensibilite_icone));
                break;
            }
        }
    }

    // Quand on presse Entrée
    g_signal_connect(entry, "activate",
                     G_CALLBACK(on_entry_activate), NULL);
}
