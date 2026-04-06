#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


typedef struct
{
    GtkImage               *image;
    GdkPixbufAnimation     *anim;
    GdkPixbufAnimationIter *iter;
    int                     largeur;
    int                     hauteur;
} AnimData;

gboolean update_frame(gpointer data)
{
    AnimData *ad = data;

    /* Avancer d'un frame */
    GTimeVal tv;
    g_get_current_time(&tv);
    gdk_pixbuf_animation_iter_advance(ad->iter, &tv);

    /* Récupérer et scaler la frame courante */
    GdkPixbuf *frame       = gdk_pixbuf_animation_iter_get_pixbuf(ad->iter);
    GdkPixbuf *frame_redim = gdk_pixbuf_scale_simple(frame,
                             ad->largeur,
                             ad->hauteur,
                             GDK_INTERP_BILINEAR);

    if (ad->image != NULL && GTK_IS_IMAGE(ad->image))
    {
        gtk_image_set_from_pixbuf(ad->image, frame_redim);
    }


    g_object_unref(frame_redim);

    /* Récupérer le délai de la prochaine frame */
    int delay = gdk_pixbuf_animation_iter_get_delay_time(ad->iter);
    if (delay < 0) delay = 100; /* délai par défaut si non spécifié */

    /* Replanifier avec le bon délai */
    g_timeout_add(delay, update_frame, ad);

    return FALSE; /* FALSE = ne pas répéter, on gère nous-mêmes */
}

void apply_attribut_toolitem(Widget* obj)
{
    GtkToolButton* toolitem = GTK_TOOL_BUTTON(obj->Widget_Ptr);

    // Label
    const char* label = get_attribut("label", obj);
    if (label != NULL)
    {
        gtk_tool_button_set_label(toolitem, label);
    }

    const char* tooltip = get_attribut("tooltip", obj);
    if (tooltip != NULL)
    {
        gtk_widget_set_tooltip_text(GTK_WIDGET(toolitem), tooltip);
    }

    const char* type_icone = get_attribut("type_icone", obj);
    const char* type_icone_anim = get_attribut("type_icone_anim", obj);
    const char* icone = get_attribut("icone", obj);
    if (icone != NULL && type_icone != NULL && type_icone_anim != NULL)
    {
        GtkWidget *image;
        if(to_bool(type_icone))
            image = gtk_image_new_from_icon_name(icone,GTK_ICON_SIZE_LARGE_TOOLBAR);
        else
        {
            if(to_bool(type_icone_anim))
            {
                /* Au démarrage */
                AnimData *ad    = g_new0(AnimData, 1);
                ad->anim        = gdk_pixbuf_animation_new_from_file(icone, NULL);
                ad->iter        = gdk_pixbuf_animation_get_iter(ad->anim, NULL);
                ad->largeur     = 42;
                ad->hauteur     = 42;

                image = gtk_image_new();
                ad->image        = GTK_IMAGE(image);

                /* Lancer la boucle d'animation */





                int delay = gdk_pixbuf_animation_iter_get_delay_time(ad->iter);
                g_timeout_add(delay, update_frame, ad);
            }
            else
            {
                image = gtk_image_new_from_file(icone);
            }
        }


        gtk_tool_button_set_icon_widget(toolitem, image);
        gtk_widget_show(image);  // important
    }

    const char* couleur_fond = get_attribut("couleur_fond", obj);
    if (couleur_fond != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-background-color",couleur_fond);
    }

    const char* coin_arrondi = get_attribut("coin_arrondi", obj);
    if (coin_arrondi != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-border-radius",coin_arrondi);
    }

    const char* margin = get_attribut("margin", obj);
    if (margin != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-margin",margin);
    }

    const char* margin_top = get_attribut("margin_top", obj);
    if (margin_top != NULL)
    {
        gtk_widget_set_margin_top(obj->Widget_Ptr,string_to_long("margin_top",margin_top));
    }

    const char* margin_bottom = get_attribut("margin_bottom", obj);
    if (margin_bottom != NULL)
    {
        gtk_widget_set_margin_bottom(obj->Widget_Ptr,string_to_long("margin_bottom",margin_bottom));
    }

    const char* margin_left = get_attribut("margin_left", obj);
    if (margin_left != NULL)
    {
        gtk_widget_set_margin_start(obj->Widget_Ptr,string_to_long("margin_left",margin_left));
    }

    const char* margin_right = get_attribut("margin_right", obj);
    if (margin_right != NULL)
    {
        gtk_widget_set_margin_end(obj->Widget_Ptr,string_to_long("margin_right",margin_right));
    }

    const char* bordure = get_attribut("bordure", obj);
    if (bordure != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-border",bordure);
    }

    const char* box_shadow = get_attribut("box_shadow", obj);
    if (bordure != NULL)
    {
        apply_css(obj->Widget_Ptr,"ma-box-shadow",box_shadow);
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
