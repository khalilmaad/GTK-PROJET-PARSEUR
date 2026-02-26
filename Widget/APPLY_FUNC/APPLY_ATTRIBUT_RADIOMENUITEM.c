#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"

static GHashTable *radio_group_first_buttons = NULL;

// Affecter un groupe à un bouton radio existant
static void set_radio_group(GtkWidget *radio, const char *group_name)
{
    if (!GTK_IS_RADIO_MENU_ITEM(radio))
    {
        printf("\nERREUR: Widget %p n'est pas un GtkRadioMenuItem\n", radio);
        return;
    }

    // Initialiser la table si nécessaire
    if (radio_group_first_buttons == NULL)
    {
        radio_group_first_buttons = g_hash_table_new(g_str_hash, g_str_equal);
        printf("\nInitialisation de la table des groupes radio\n");
    }

    printf("\n\nset_radio_group: radio=%p, groupe='%s'\n", radio, group_name);

    // Chercher le premier bouton de ce groupe
    GtkWidget *first_button = g_hash_table_lookup(radio_group_first_buttons, group_name);

    if (first_button == NULL)
    {
        // Premier bouton de ce groupe
        printf("\n-> Premier bouton du groupe '%s'\n", group_name);

        // Stocker CE bouton comme référence
        g_hash_table_insert(radio_group_first_buttons, g_strdup(group_name), radio);

        // Ajouter une marque pour identifier le groupe
        g_object_set_data(G_OBJECT(radio), "radio-group-name", (gpointer)group_name);

        // Ce bouton reste avec son groupe singleton (créé avec NULL)
        // Rien de plus à faire
    }
    else
    {
        // Ajouter ce bouton au groupe du premier bouton
        printf("\n-> Ajout au groupe existant (premier: %p)", first_button);

        // Récupérer le groupe du premier bouton
        GSList *group = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(first_button));

        // Définir ce bouton dans le même groupe
        gtk_radio_menu_item_set_group(GTK_RADIO_MENU_ITEM(radio), group);
    }
}


void apply_attribut_radiomenuitem(Widget* obj)
{
    GtkWidget* item = obj->Widget_Ptr;

    // Label
    const char* label = get_attribut("label", obj);
    if (label != NULL)
    {
        radiomenuitem(GTK_MENU_ITEM(item), label);
    }

    // Utiliser mnémonique (raccourci clavier)
    const char* groupe = get_attribut("groupe", obj);
    if (groupe != NULL)
    {
        set_radio_group(item, groupe);
    }
    else
    {
        printf("\n\033[34mMessage :  \033[31mVeuiller indiquer le groupe du button radio attribut attendu : 33[34mgroupe=\"valeur_indicative\" \033[0m\n");
        exit(1);
    }
}
