#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"

#include <unistd.h>
#include <fcntl.h>

void apply_css(GtkWidget* mon_widget, const char* ma_class, const char* valeur)
{
    // Sauvegarder stderr
    int old_stderr = dup(fileno(stderr));
    // Rediriger stderr vers NUL (Windows) ou /dev/null (Linux)
#ifdef _WIN32
    freopen("NUL", "w", stderr);
#else
    freopen("/dev/null", "w", stderr);
#endif

    // --- Code CSS ---
    GtkStyleContext *context = gtk_widget_get_style_context(mon_widget);
    gtk_style_context_add_class(context, ma_class);

    char *css = g_strconcat(
        ".ma-background-color { background-color: ", valeur,";}",
        ".ma-color { color: ", valeur,";}",
        ".ma-border { border: ", valeur,";}",
        ".ma-border-width { border-width: ", valeur,";}",
        ".ma-border-style { border-style: ", valeur,";}",
        ".ma-border-color { border-color: ", valeur,";}",
        ".ma-border-radius { border-radius: ", valeur,";}",
        ".ma-padding { padding: ", valeur,";}",
        ".ma-margin { margin: ", valeur,";}",
        ".ma-opacity { opacity: ", valeur,";}",
        ".ma-box-shadow { box-shadow: ", valeur,";}",
        ".ma-font { font: ", valeur,";}",
        ".ma-font-size { font-size: ", valeur,";}",
        ".ma-font-weight { font-weight: ", valeur,";}",
        ".ma-font-style { font-style: ", valeur,";}",
        ".ma-text-align { text-align: ", valeur,";}",
        NULL
    );

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, css, -1, NULL);

    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );

    g_free(css);

    // Restaurer stderr
    fflush(stderr);
    dup2(old_stderr, fileno(stderr));
    close(old_stderr);
}


