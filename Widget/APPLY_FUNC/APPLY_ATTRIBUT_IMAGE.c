#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"


void apply_attribut_image(Widget* obj)
{
    GtkImage* image = GTK_IMAGE(obj->Widget_Ptr);

    // type image (file / icon_name)
    const char* type = get_attribut("type", obj);
    const char* nom = get_attribut("nom", obj);

    if (type != NULL && nom != NULL)
    {
        if (to_bool(type))
        {
            // Icône nommée (thème)
            gtk_image_set_from_icon_name(image, nom, GTK_ICON_SIZE_LARGE_TOOLBAR);
        }
        else
        {
            // Image depuis fichier
            gtk_image_set_from_file(image, nom);
        }
    }

    // Taille en pixels
    const char* taille_str = get_attribut("taille", obj);
    if (taille_str != NULL)
    {
        int taille = atoi(taille_str);
        gtk_image_set_pixel_size(image, taille);
    }
}
