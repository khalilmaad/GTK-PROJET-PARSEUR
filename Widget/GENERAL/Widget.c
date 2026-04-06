#include "Widget.h"
#include "../INIT_FUNC/INIT_FUNC.h"


/*
 * Structure associant :
 * - un nom de widget (sous forme de chaîne)
 * - une fonction d'initialisation correspondante
 *
 * Cela permet d'appeler dynamiquement la bonne fonction
 * d'initialisation selon le nom lu (ex: depuis un parseur XML).
 */
static struct {
    char* nom_widget;           // Nom textuel du widget (ex: "button")
    void (*init_func)(Widget*); // Pointeur vers fonction d'initialisation
} List_Obj[] =
{
    // ── Conteneurs principaux ──────────────────────────────────────────
    {"fenetre",            init_fenetre          },  // GtkWindow
    {"box",                init_box              },  // GtkBox (lineaire)
    {"grid",               init_grid             },  // GtkGrid (tableau)
    {"paned",              init_paned            },  // GtkPaned (2 panneaux)
    {"notebook",           init_notebook         },  // GtkNotebook (onglets)
    {"stack",              init_stack            },  // GtkStack (pages animees)
    {"stackswitcher",      init_stackswitcher    },  // GtkStackSwitcher
    {"overlay",            init_overlay          },  // GtkOverlay (superposition)
    {"fixed",              init_fixed            },  // GtkFixed (pos absolue)
    {"layout",             init_layout           },  // GtkLayout (canvas defilable)
    {"flowbox",            init_flowbox          },  // GtkFlowBox (grille fluide)
    {"listbox",            init_listbox          },  // GtkListBox (liste selectable)
    {"buttonbox",          init_buttonbox        },  // GtkButtonBox
    {"frame",              init_frame            },  // GtkFrame (cadre)
    {"expander",           init_expander         },  // GtkExpander (pliable)
    {"revealer",           init_revealer         },  // GtkRevealer (anime)
    {"scrollbar",          init_scrollbar        },  // GtkScrolledWindow
    {"actionbar",          init_action_bar       },  // GtkActionBar

    // ── Boutons ───────────────────────────────────────────────────────
    {"button",             init_button           },  // GtkButton
    {"buttonradio",        init_buttonradio      },  // GtkRadioButton
    {"checkbutton",        init_check_button     },  // GtkCheckButton
    {"togglebutton",       init_togglebutton     },  // GtkToggleButton
    {"linkbutton",         init_linkbutton       },  // GtkLinkButton
    {"menubutton",         init_menubutton       },  // GtkMenuButton
    {"scalebutton",        init_scalebutton      },  // GtkScaleButton
    {"colorbutton",        init_colorbutton      },  // GtkColorButton
    {"fontbutton",         init_fontbutton       },  // GtkFontButton
    {"filechoosebutton",   init_filechoosebutton },  // GtkFileChooserButton

    // ── Saisie ────────────────────────────────────────────────────────
    {"entry",              init_entry            },  // GtkEntry
    {"searchentry",        init_searchentry      },  // GtkSearchEntry
    {"spinbutton",         init_spinbutton       },  // GtkSpinButton
    {"switch",             init_switch           },  // GtkSwitch
    {"scale",              init_scale            },  // GtkScale (curseur)
    {"comboboxtext",       init_comboboxtext     },  // GtkComboBoxText
    {"comboboxtextentry",  init_comboboxtextentry},  // GtkComboBoxText+Entry

    // ── Affichage ─────────────────────────────────────────────────────
    {"label",              init_label            },  // GtkLabel
    {"image",              init_image            },  // GtkImage
    {"progressbar",        init_progressbar      },  // GtkProgressBar
    {"levelbar",           init_levelbar         },  // GtkLevelBar
    {"spinner",            init_spinner          },  // GtkSpinner
    {"separator",          init_separator        },  // GtkSeparator
    {"statusbar",          init_statusbar        },  // GtkStatusbar
    {"calendrier",         init_calendrier       },  // GtkCalendar

    // ── Menus ─────────────────────────────────────────────────────────
    {"menubar",            init_menubar          },  // GtkMenuBar
    {"menu",               init_menu             },  // GtkMenu
    {"menuitem",           init_menuitem         },  // GtkMenuItem
    {"checkmenuitem",      init_checkmenuitem    },  // GtkCheckMenuItem
    {"radiomenuitem",      init_radiomenuitem    },  // GtkRadioMenuItem
    {"separatormenuitem",  init_separatormenuitem},  // GtkSeparatorMenuItem

    // ── Barre d'outils ────────────────────────────────────────────────
    {"toolbar",            init_toolbar          },  // GtkToolbar
    {"toolitem",           init_toolitem         },  // GtkToolButton
    {"separatortoolitem",  init_separatortoolitem},  // GtkSeparatorToolItem

    // ── Barres speciales ──────────────────────────────────────────────
    {"headerbar",          init_header_bar       },  // GtkHeaderBar
    {"infobar",            init_infobar          },  // GtkInfoBar
    {"searchbar",          init_searchbar        },  // GtkSearchBar
    // ── Autre  ──────────────────────────────────────────────
    {"drawingarea",          init_drawingarea        },
    // ── Dialog  ──────────────────────────────────────────────
    {"filechooserdialog",          init_filechooserdialog        },
    // ── Elements spéciaux (non-GTK) ───────────────────────────────────
    {"option",             init_option           },  // Option combobox (interne)
    {"signal",             init_signal           },  // Balise signal (interne)
    {"simulation",         init_simulation          },
    {"poisson",            init_poisson          },
};

/*
 * Initialise les champs généraux d'un objet Widget :
 * - pointeurs
 * - relations arbre (fils / frère)
 * - attributs spéciaux par défaut
 */
void init_general(Widget* obj)
{
    obj->Id = NULL;            // Identifiant logique
    obj->Widget_Ptr = NULL;    // Pointeur vers widget GTK réel
    obj->fils = obj->frere = NULL; // Structure arbre (child / sibling)

    /*
     * Attributs spéciaux génériques applicables à plusieurs widgets
     * Ex: position dans certains containers, marge, comportement notebook, etc.
     */
    Attributs tableau_attribut_special[] =
    {
        {"insert_cote", strdup("")},   // droite / gauche
        {"marge", strdup("")},         // marge externe
        {"remplir", strdup("")},       // TRUE / FALSE
        {"etendre", strdup("")},       // expansion TRUE / FALSE
        {"pos_colonne", strdup("")},   // Grid column
        {"pos_ligne", strdup("")},     // Grid row
        {"pos_x", strdup("")},         // Fixed X
        {"pos_y", strdup("")},         // Fixed Y
        {"nombre_colonne", strdup("")},
        {"nombre_ligne", strdup("")},
        {"page_titre", strdup("")},
        {"page_detachable", strdup("")},
        {"page_reorderable", strdup("")},
    };

    //Allocation dynamique
    obj->Nbre_Attribut_special = sizeof(tableau_attribut_special)/sizeof(tableau_attribut_special[0]);
    obj->List_Attribut_special = (Attributs*)malloc(obj->Nbre_Attribut_special * sizeof(Attributs));

    memcpy(obj->List_Attribut_special, tableau_attribut_special, obj->Nbre_Attribut_special * sizeof(Attributs));
}

/*
 * Crée dynamiquement un Widget selon son nom.
 * Cherche la fonction correspondante dans List_Obj.
 */
Widget*  init_func_widget(char* nom)
{
    Widget* obj = (Widget*)malloc(sizeof(Widget));
    if(!obj)
    {
        printf("\n\033[34mMessage : \033[31minit_func_widget | erreur d'allocation memoire\n\033[0m");
        exit(1);
    }
    obj->Nom = strdup(nom);  // Sauvegarde du nom du widget

    init_general(obj);       // Initialisation commune


    for(int i=0; i < sizeof(List_Obj)/sizeof(List_Obj[0]); i++)
    {
        if(!compare(nom,List_Obj[i].nom_widget))
        {
            List_Obj[i].init_func(obj); // Appel dynamique

            printf("\n\033[1;32m[init]\033[0m Initialisation de \033[1;34m %s \033[0m\n",nom);
            return (Widget*) obj;
        }
    }

    printf("\n\033[1;31m[init]\033[0m Initialisation de \033[1;34m %s \033[0m\n",nom);
    printf("\n\033[1;34mMessage : \033[31minit_func_widget | balise \033[1;34m %s \033[31m non reconnue\n\033[0m",nom);
    exit(1);

    return (Widget*) obj;
}


/*
 * Retourne la valeur d'un attribut si trouvé.
 * Cherche d'abord dans les attributs normaux,
 * puis dans les attributs spéciaux.
 */
const char* get_attribut(const char* nom_attribut, Widget* obj)
{
    // Recherche dans attributs standards
    for(int i=0; i<obj->Nbre_Attribut; i++)
    {
        if(!compare(nom_attribut,obj->List_Attribut[i].Nom)
                && obj->List_Attribut[i].Valeur[0] != '\0')
        {
            return obj->List_Attribut[i].Valeur;
        }
    }

    // Recherche dans attributs spéciaux
    for(int i=0; i<obj->Nbre_Attribut_special; i++)
    {
        if(!compare(nom_attribut,obj->List_Attribut_special[i].Nom)
                && obj->List_Attribut_special[i].Valeur[0] != '\0')
        {
            return obj->List_Attribut_special[i].Valeur;
        }
    }

    return NULL;  // Non trouvé
}

_Bool Attribut_existe(const char* nom_attribut, Widget* obj)
{
    // Recherche dans attributs standards
    for(int i=0; i<obj->Nbre_Attribut; i++)
    {
        if(!compare(nom_attribut,obj->List_Attribut[i].Nom))
        {
            return TRUE;
        }
    }
    return FALSE;
}


/*
 * Convertit une chaîne en booléen.
 * Retourne TRUE si :
 * - "1"
 * - "true"
 */
_Bool to_bool (const char* value)
{
    return !compare(value,"1") || !compare(value,"true");
};


void print_succes_liaison(const char* Nom_parent)
{
    printf("\n\033[1;32m[Liaison]\033[0m Liaison au parent \033[1;34m%s\033[0m",Nom_parent);
}

void print_succes_liaison_signal(const char* Nom_parent)
{
    printf("\n\033[1;32m[Liaison signal]\033[0m source \033[1;34m%s\033[0m",Nom_parent);
}

void print_error_liaison(const char* Nom_parent)
{
    printf("\n\033[1;31m[Liaison]\033[0m Liaison au parent \033[1;34m%s\033[0m",Nom_parent);
}

void print_error_liaison_signal(const char* message,const char* sible,_Bool motif)
{
    if(motif)
        printf("\n\033[1;31m[Liaison Signal]\033[0m %s du type de signal Sible =\033[1;34m%s\033[0m",message,sible);
    else
        printf("\n\033[1;31m[Liaison Signal]\033[0m %s de la fonction à executer par le signal Sible =\033[1;34m%s\033[0m",message,sible);
}

void print_message_error_liaison(const char* message)
{
    printf("\n\033[1;34mMessage : \033[1;31mEchec liaison au parente -> manque attribut indicatif %s\033[0m",message);
    exit(1);
}

long string_to_long(const char* nom_attribut,const char* valeur)
{
    char* endptr;
    errno = 0;  // Réinitialiser errno

    long val = strtol(valeur, &endptr, 10);  // base 10

    if (errno == ERANGE)
    {
        printf("\n\033[1;31m[conversion]\033[0m 033[1;34m%s\033[0m  debordement (trop grand)",nom_attribut);
        printf("\n\033[1;34mMessage : \033[1;31m (\033[1;34m%s\033[1;31m) -> attend une valeur entiere \033[0m (ex: %s=\"10\")n\n",nom_attribut,nom_attribut);
        exit(1);
    }
    else if (endptr == valeur)
    {
        printf("\n\033[1;31m[conversion]\033[0m \033[1;34m%s\033[0m  aucun caractere numerique trouve",nom_attribut);
        printf("\n\033[1;34mMessage : \033[1;31m (\033[1;34m%s\033[1;31m) -> attend une valeur entiere \033[0m (ex: %s=\"10\")n\n",nom_attribut,nom_attribut);
        exit(1);
    }
    else if (*endptr != '\0')
    {
        printf("\n\033[1;31m[conversion]\033[0m \033[1;34m%s\033[0m  contient des caracteres non numeriques",nom_attribut);
        printf("\n\033[1;34mMessage : \033[1;31m (\033[1;34m%s\033[1;31m) -> attend une valeur entiere \033[0m (ex: %s=\"10\")n\n",nom_attribut,nom_attribut);
        exit(1);
    }

    return val;
}

double string_to_double(const char* nom_attribut, const char* valeur)
{
    char* endptr;
    errno = 0;  // Réinitialiser errno

    double val = strtod(valeur, &endptr);

    if (errno == ERANGE)
    {
        printf("\n\033[1;31m[conversion]\033[0m \033[1;34m%s\033[0m  debordement (trop grand ou trop petit)", nom_attribut);
        printf("\n\033[1;34mMessage : \033[1;31m (\033[1;34m%s\033[1;31m) -> attend une valeur reelle \033[0m (ex: %s=\"3,14\")\n\n", nom_attribut, nom_attribut);
        exit(1);
    }
    else if (endptr == valeur)
    {
        printf("\n\033[1;31m[conversion]\033[0m \033[1;34m%s\033[0m=(%s)  aucun caractere numerique trouve", nom_attribut,valeur);
        printf("\n\033[1;34mMessage : \033[1;31m (\033[1;34m%s\033[1;31m) -> attend une valeur reelle \033[0m (ex: %s=\"3,14\")\n\n", nom_attribut, nom_attribut);
        exit(1);
    }
    else if (*endptr != '\0')
    {
        printf("\n\033[1;31m[conversion]\033[0m \033[1;34m%s\033[0m=(%s)  contient des caracteres non numeriques", nom_attribut,valeur);
        printf("\n\033[1;34mMessage : \033[1;31m (\033[1;34m%s\033[1;31m) -> attend une valeur reelle \033[0m (ex: %s=\"3,14\")\n\n", nom_attribut, nom_attribut);
        exit(1);
    }

    return val;
}

void print_error_mapping_value(const char* nom_attribut,mapping_value* tab)
{
    printf("\n\033[1;31m[conversion]\033[0m \033[1;34m%s\033[0m -> valeur incorrect\033[0m",nom_attribut);
    printf("\n\033[1;34mMessage : \033[0m valeur attendu : ");
    for (int i = 0; tab[i].nom != NULL; i++)
    {
        printf("\n->\033[1;34m%s\033[0m,",tab[i].nom);
    }
    printf("\n");
    exit(1);
}

void print_error_mapping_liaison(Widget* pere,Widget* fils)
{
    printf("\n\033[1;34mMessage : \033[1;31mEchec au controle de parente -> (\033[1;34m%s\033[1;31m) ne prend pas (\033[1;34m%s\033[1;31m)"
           "\n\n\033[0mNom widget prise en charge: ",pere->Nom,fils->Nom);

    for(int i=0; i < pere->Nbre_enfant; i++)
    {
        printf("\n->\033[1;34m%s\033[0m,",pere->List_widget_enfant[i]);
    }
    printf("\n");
    exit(1);
}
