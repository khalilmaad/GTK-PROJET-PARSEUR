#include "ParseXML.h"
#include "../Widget/GENERAL/Widget.h"

void gerer_widget_with_id(ParserXML* Parser, Widget* obj,int numligne)
{
    if(!compare(obj->Nom,"signal"))
    {
        Gestion_Signaux* signaux = (Gestion_Signaux*)malloc(sizeof(Gestion_Signaux));
        signaux->numligne = numligne;
        signaux->obj = obj;
        signaux->svt = Parser->Signaux;
        Parser->Signaux = signaux;

        return;
    }

    if(obj->Id)
    {
        Gestion_Signaux* signaux = (Gestion_Signaux*)malloc(sizeof(Gestion_Signaux));
        signaux->ID = obj->Id;
        signaux->numligne = numligne;
        signaux->obj = obj;
        signaux->svt = Parser->Widget_with_ID;
        Parser->Widget_with_ID = signaux;

        return;
    }
}

_Bool Controle_attribut_signal(Widget* signal,_Bool* event)
{

    const char* type = get_attribut("type",signal);

    static const struct
    {
        const char* nom_signal;
        int avec_event;  // 1 = 3 paramètres, 0 = 2 paramètres
    } signaux_attendu[29] =
    {
        // Signaux à 2 paramètres
        {"clicked", 0},
        {"activate", 0},
        {"toggled", 0},
        {"changed", 0},
        {"destroy", 0},
        {"realize", 0},
        {"show", 0},
        {"hide", 0},
        {"map", 0},
        {"unmap", 0},
        {"select", 0},
        {"deselect", 0},
        {"value-changed", 0},
        {"popup-menu", 0},
        {"query-tooltip", 0},

        // Signaux à 3 paramètres (avec -event)
        {"delete-event", 1},
        {"key-press-event", 1},
        {"key-release-event", 1},
        {"button-press-event", 1},
        {"button-release-event", 1},
        {"motion-notify-event", 1},
        {"enter-notify-event", 1},
        {"leave-notify-event", 1},
        {"configure-event", 1},
        {"expose-event", 1},
        {"window-state-event", 1},
        {"grab-broken-event", 1},
        {"damage-event", 1},
        {"property-notify-event", 1},
    };

    int nb_signaux = sizeof(signaux_attendu) / sizeof(signaux_attendu[0]);

    if(!type)
    {
        printf("\n\033[1;31m[Liaison Signal]\033[0m manque du type de signal Sible =\033[1;34m%s\033[0m",signal->fils->Nom);
    }
    else
    {
        for(int i=0; i < nb_signaux ; i++ )
        {
            if(!compare(type,signaux_attendu[i].nom_signal))
            {
                *event = signaux_attendu[i].avec_event;
                goto fonction_exe;
            }
        }
        printf("\n\033[1;31m[Liaison Signal]\033[0m Nom(%s) du type de signal est incorrect Sible =\033[1;34m%s\033[0m",type,signal->fils->Nom);
    }
    printf("\n\nNom du type de signal attendu:");
    for(int i=0; i < nb_signaux; i++)
    {
        printf("\n->\033[1;34m%s\033[0m,",signaux_attendu[i].nom_signal);
    }
    printf("\n");

fonction_exe:

    const char* fonction_utilise = get_attribut("fonction",signal);
    char* fonction_attendu[] = {"afficher","cacher","detruire","modifier","connexion_stackswitcher","afficher_avec_animation",
    "cacher_avec_animation","afficher_cacher_avec_animation"};
    int nb_fonction = sizeof(fonction_attendu) / sizeof(fonction_attendu[0]);
    if(!fonction_utilise)
    {
        printf("\n\033[1;31m[Liaison Signal]\033[0m manque du nom de la fonction à executer par le signal Sible =\033[1;34m%s\033[0m",signal->fils->Nom);
    }
    else
    {
        for(int i=0; i < nb_fonction ; i++ )
        {
            if(!compare(fonction_utilise,fonction_attendu[i]))
            {
                return TRUE;
            }
        }
        printf("\n\033[1;31m[Liaison Signal]\033[0m Nom(%s) de la fonction à executer par le signal est incorrect Sible =\033[1;34m%s\033[0m",fonction_utilise,signal->fils->Nom);
    }
    printf("\n\nNom de fonction attendu par le signal:");
    for(int i=0; i < nb_fonction; i++)
    {
        printf("\n->\033[1;34m%s\033[0m,",fonction_attendu[i]);
    }
    printf("\n");

    return FALSE;
}

Gtk_Callback get_fonction(Widget* signal)
{
    const char* fonction = get_attribut("fonction",signal);
    if(!compare(fonction,"afficher")) return afficher;
    else if(!compare(fonction,"connexion_stackswitcher")) return connecte_stack_with_stackswitcher;
    else if(!compare(fonction,"cacher")) return cacher;
    else if(!compare(fonction,"afficher_avec_animation")) return afficher_avec_animation;
    else if(!compare(fonction,"cacher_avec_animation")) return cacher_avec_animation;
    else if(!compare(fonction,"afficher_cacher_avec_animation")) return afficher_cacher_avec_animation;
    else if(!compare(fonction,"detruire")) return afficher_cacher_avec_animation;
    else if(!compare(fonction,"modifier")) return modifier;

    return NULL;
}


Gtk_Callback_with_event get_fonction_avec_event(Widget* signal)
{
    const char* fonction = get_attribut("fonction",signal);
    if(!compare(fonction,"afficher")) return afficher_avec_event;
    else if(!compare(fonction,"cacher")) return cacher_avec_event;
    else if(!compare(fonction,"afficher_avec_animation")) return afficher_avec_event_animation;
    else if(!compare(fonction,"cacher_avec_animation")) return cacher_avec_event_animation;
    else if(!compare(fonction,"afficher_cacher_avec_animation")) return afficher_cacher_avec_event_animation;
    else if(!compare(fonction,"detruire")) return detruire_avec_event;
    else if(!compare(fonction,"modifier")) return modifier_avec_event;

    return NULL;
}

void appliquer_signal(Widget* signal)
{
    _Bool avec_event=0;
    if(Controle_attribut_signal(signal,&avec_event))
    {

        const char* type = get_attribut("type",signal);
        const char* fonction_utilisee = get_attribut("fonction",signal);

        // Connexion d'un signal avec la fonction obtenue
        Gtk_Callback callback = get_fonction(signal);
        Gtk_Callback_with_event callback_event = get_fonction_avec_event(signal);
        if (avec_event && callback_event)
        {
            g_signal_connect(signal->Widget_Ptr, type, G_CALLBACK(callback_event), signal->fils);
        }
        else if(!avec_event && callback)
        {
            g_signal_connect(signal->Widget_Ptr, type, G_CALLBACK(callback), signal->fils);
        }
        else
        {
            g_warning("Impossible de connecter le signal");
        }
        printf("\n\033[1;32m[Liaison Signal]\033[0mSource = %p Sible = \033[1;34m%s\033[0m ID = \033[1;33m%s\033[0m Fonction = \033[1;34m%s\033[0m",signal->Widget_Ptr,signal->fils->Nom,(signal->fils->Id) ? signal->fils->Id : "non specifie",fonction_utilisee);
    }

}

void Liaison_signaux(ParserXML* Parser)
{
    if(Parser->Signaux)
    {
        printf("\033[1;36m====================<\033[0m\033[1;33mCONNEXION SIGNAUX\033[0m\033[1;36m>====================\033[0m\n");
        while(Parser->Signaux)
        {
            if(Parser->Signaux->obj->fils)
            {

                appliquer_signal(Parser->Signaux->obj);
            }
            else
            {
                const char* Sible_signal = get_attribut("sible",Parser->Signaux->obj);
                if(Sible_signal)
                {
                    Gestion_Signaux* crt = Parser->Widget_with_ID;
                    while(crt)
                    {
                        if(!compare(crt->ID,Sible_signal) && crt->obj)
                        {

                            Parser->Signaux->obj->fils = crt->obj;
                            appliquer_signal(Parser->Signaux->obj);
                            goto suite;
                        }
                        crt = crt->svt;
                    }
                    printf("\n\033[1;31m[Liaison Signal]\033[0m sible choisi est introuvable(verifier ID sible designant le widget) pour le signal ligne=\033[1;34m%d\033[0m",Parser->Signaux->numligne);
                }
                else
                {
                    printf("\n\033[1;31m[Liaison Signal]\033[0m absence de sible pour le signal ligne=\033[1;34m%d\033[0m",Parser->Signaux->numligne);
                }
            }
suite:
            Parser->Signaux = Parser->Signaux->svt;
        }
        printf("\n\n\033[1;36m====================<\033[0m\033[1;33mFIN CONNEXION SIGNAUX\033[0m\033[1;36m>====================\033[0m\n");
    }
}

