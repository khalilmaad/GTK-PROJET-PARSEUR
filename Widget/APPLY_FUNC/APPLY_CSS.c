#include "APPLY_FUNC.h"
#include "../GENERAL/Widget.h"

#include <unistd.h>
#include <fcntl.h>

void apply_css(GtkWidget* mon_widget, const char* ma_class, const char* valeur)
{
    int old_stderr = dup(fileno(stderr));
#ifdef _WIN32
    freopen("NUL", "w", stderr);
#else
    freopen("/dev/null", "w", stderr);
#endif

    // Générer un nom de classe unique basé sur l'adresse du widget
    // ex: "ma-background-color-0x7f1234abcd"
    char classe_unique[128];
    snprintf(classe_unique, sizeof(classe_unique), "%s-%p", ma_class, (void*)mon_widget);

    GtkStyleContext *context = gtk_widget_get_style_context(mon_widget);
    gtk_style_context_add_class(context, classe_unique);

    // CSS ciblant uniquement cette classe unique
    char *css = g_strdup_printf(".%s { %s: %s; }",
        classe_unique,
        ma_class + 3,   // enlève le préfixe "ma-" pour obtenir la vraie propriété CSS
        valeur
    );

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, css, -1, NULL);

    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );

    g_free(css);

    fflush(stderr);
    dup2(old_stderr, fileno(stderr));
    close(old_stderr);
}

