#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_infobar(Widget* obj)
{
    GtkInfoBar* infobar = GTK_INFO_BAR(obj->Widget_Ptr);


    const char* type_message = get_attribut("type_message",obj);
    if (type_message)
    {
        mapping_value type_message_mapping[] =
        {
            {"info", GTK_MESSAGE_INFO},
            {"warning",  GTK_MESSAGE_WARNING},
            {"error",  GTK_MESSAGE_ERROR},
            {"question",    GTK_MESSAGE_QUESTION},
            {"autre",  GTK_MESSAGE_OTHER},
            {NULL, 0}  // Sentinel
        };

        // Recherche dans la table
        for (int i = 0; type_message_mapping[i].nom != NULL; i++)
        {
            if (strcmp(type_message, type_message_mapping[i].nom) == 0)
            {
                gtk_info_bar_set_message_type(infobar, type_message_mapping[i].position);
                goto suivant;
            }
        }
        print_error_mapping_value("type_message",type_message_mapping);
        suivant:
    }

    const char* message = get_attribut("message",obj);
    if (message)
    {
        GtkWidget *content;
        GtkWidget *label;

        content = gtk_info_bar_get_content_area(infobar);

        label = gtk_label_new(message);
        gtk_container_add(GTK_CONTAINER(content), label);
    }

    const char* label_ok = get_attribut("label_ok",obj);
    if (label_ok)
    {
        gtk_info_bar_add_button(infobar,
                        label_ok,
                        GTK_RESPONSE_OK);
    }

    const char* label_cancel = get_attribut("label_cancel",obj);
    if (label_cancel)
    {
        gtk_info_bar_add_button(infobar,
                        label_cancel,
                        GTK_RESPONSE_CANCEL);
    }

    const char* couleur_fond = get_attribut("couleur_fond", obj);
    if (couleur_fond != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-background-color",couleur_fond);
    }

    const char* couleur_label = get_attribut("couleur_label", obj);
    if (couleur_label != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-color",couleur_label);
    }

    const char* font_weight = get_attribut("font_weight", obj);
    if (font_weight != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-font-weight",font_weight);
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
