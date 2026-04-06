#include "ParseXML.h"
#include "../Widget/GENERAL/Widget.h"
#include "../Simulation/SIMULATION.h"


static struct
{
    const char* Nom_fonction_signal;
    void (*func_callback)(GtkWidget*,gpointer);
    gboolean (*func_callback_event)(GtkWidget*,GdkEvent*,gpointer);
    void (*func_callback_response)(GtkDialog *dialog, gint response_id, gpointer data);
} List_Fonction_Signal[]=
{
    {"Arreter_program",exec_main_quit,exec_main_quit_avec_event,NULL},
    {"sauvergarder_fichier",save_file,NULL,NULL},
    {"charger_simulation",chargement_simulation,NULL,NULL},
    {"reset_simulation",reset_state,NULL,NULL},
    {"afficher",afficher,afficher_avec_event,NULL},
    {"maximizer_fenetre",maximizer_fenetre,NULL,NULL},
    {"afficher_text_entry_terminal",afficher_text_entry_terminal,NULL,NULL},
    {"cacher",cacher,cacher_avec_event,NULL},
    {"afficher_cacher",afficher_cacher,NULL,NULL},
    {"detruire",detruire,detruire_avec_event,NULL},
    {"modifier",modifier,modifier_avec_event,NULL},
    {"modifier_simplement",modifier_simplement,NULL,NULL},
    {"modifier_police",modifier_police,NULL,NULL},
    {"recuperer_modifier_avec_entry",recuper_modifier,NULL,NULL},
    {"recuperer_modifier_avec_colorbutton",modifier_couleur_avec_colorbutton,NULL,NULL},
    {"recuperer_modifier_avec_filechooserbutton",recuper_modifier_avec_filechooser,NULL,NULL},
    {"connexion_stackswitcher",connecte_stack_with_stackswitcher,NULL,NULL},
    {"afficher_avec_animation",afficher_avec_animation,afficher_avec_event_animation,NULL},
    {"cacher_avec_animation",cacher_avec_animation,cacher_avec_event_animation,NULL},
    {"afficher_cacher_avec_animation",afficher_cacher_avec_animation,afficher_cacher_avec_event_animation,NULL},
    {"recuperer_modifier_avec_filechooserdialog",NULL,NULL,recuperer_modifier_avec_filechooserdialog},
};

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

_Bool Controle_attribut_signal(Widget* signal,int* event)
{

    const char* type = get_attribut("type",signal);

    static const struct
    {
        const char* nom_signal;
        int avec_event;  // 1 = 3 param�tres, 0 = 2 param�tres
    } signaux_attendu[] =
    {
        // Signaux � 2 param�tres
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
        {"color-set", 0},
        {"font-set", 0},
        {"file-set", 0},
        //Signaux personnalisé
        {"fin_sauvegarde", 0},
        {"debut_sauvegarde", 0},
        {"debut_recuperation", 0},
        {"fin_recuperation", 0},

        // Signaux � 3 param�tres (avec -event)
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


        {"response", 2},
    };

    int nb_signaux = sizeof(signaux_attendu) / sizeof(signaux_attendu[0]);

    if(!type)
    {
        print_error_liaison_signal("manque",signal->fils->Nom,TRUE);
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
        print_error_liaison_signal("Incorect nom",signal->fils->Nom,TRUE);
        printf("\n\nNom du type de signal attendu:");
        for(int i=0; i < nb_signaux; i++)
        {
            printf("\n->\033[1;34m%s\033[0m,",signaux_attendu[i].nom_signal);
        }
        printf("\n");

fonction_exe:

        const char* fonction_utilise = get_attribut("fonction",signal);

        int nb_fonction = sizeof(List_Fonction_Signal) / sizeof(List_Fonction_Signal[0]);
        if(!fonction_utilise)
        {
            print_error_liaison_signal("manque",signal->fils->Nom,FALSE);
        }
        else
        {
            for(int i=0; i < nb_fonction ; i++ )
            {
                if(!compare(fonction_utilise,List_Fonction_Signal[i].Nom_fonction_signal))
                {
                    return TRUE;
                }
            }
            print_error_liaison_signal("Incorect nom",signal->fils->Nom,FALSE);
        }
        printf("\n\nNom de fonction attendu par le signal:");
        for(int i=0; i < nb_fonction; i++)
        {
            printf("\n->\033[1;34m%s\033[0m,",List_Fonction_Signal[i].Nom_fonction_signal);
        }
        printf("\n");
    }
    return FALSE;
}

void appliquer_signal(Widget* signal)
{
    int avec_event=0;
    if(Controle_attribut_signal(signal,&avec_event))
    {

        const char* type = get_attribut("type",signal);
        const char* fonction_utilisee = get_attribut("fonction",signal);

        int nb_fonction = sizeof(List_Fonction_Signal) / sizeof(List_Fonction_Signal[0]);

        for(int i=0; i < nb_fonction; i++)
        {
            if(!compare(fonction_utilisee,List_Fonction_Signal[i].Nom_fonction_signal))
            {
                switch(avec_event)
                {
                case 0:
                    g_signal_connect(signal->Widget_Ptr, type,
                                     G_CALLBACK(List_Fonction_Signal[i].func_callback),
                                     signal);
                    break;

                case 1:

                    g_signal_connect(signal->Widget_Ptr, type,
                                     G_CALLBACK(List_Fonction_Signal[i].func_callback_event),
                                     signal);
                    break;

                case 2:
                    g_signal_connect(signal->Widget_Ptr, type,
                                     G_CALLBACK(List_Fonction_Signal[i].func_callback_response),
                                     signal);
                    break;
                }
            }
        }
        printf("\n\033[1;32m[Liaison Signal]\033[0mSource = %p Sible = \033[1;34m%s\033[0m ID = \033[1;33m%s\033[0m Fonction = \033[1;34m%s\033[0m",
               signal->Widget_Ptr,signal->fils->Nom,(signal->fils->Id) ? signal->fils->Id : "non specifie",fonction_utilisee);
    }

}

void creation_type_signaux_personnalise()
{
    // À faire UNE seule fois au démarrage, avant gtk_main()
    guint mon_signal_id = g_signal_new(
                              "fin_sauvegarde",              // nom du signal
                              GTK_TYPE_WIDGET,           // type GObject auquel il appartient
                              G_SIGNAL_RUN_FIRST,        // quand les handlers sont appelés
                              0,                         // offset dans la structure (0 si pas de classe)
                              NULL,                      // accumulateur (NULL = aucun)
                              NULL,                      // données accumulateur
                              g_cclosure_marshal_VOID__VOID,  // marshaller (type des args)
                              G_TYPE_NONE,               // type de retour
                              0                          // nombre de paramètres
                          );

    g_signal_new(
        "debut_sauvegarde",              // nom du signal
        GTK_TYPE_WIDGET,           // type GObject auquel il appartient
        G_SIGNAL_RUN_FIRST,        // quand les handlers sont appelés
        0,                         // offset dans la structure (0 si pas de classe)
        NULL,                      // accumulateur (NULL = aucun)
        NULL,                      // données accumulateur
        g_cclosure_marshal_VOID__VOID,  // marshaller (type des args)
        G_TYPE_NONE,               // type de retour
        0                          // nombre de paramètres
    );


    g_signal_new(
        "debut_recuperation",              // nom du signal
        GTK_TYPE_WIDGET,           // type GObject auquel il appartient
        G_SIGNAL_RUN_FIRST,        // quand les handlers sont appelés
        0,                         // offset dans la structure (0 si pas de classe)
        NULL,                      // accumulateur (NULL = aucun)
        NULL,                      // données accumulateur
        g_cclosure_marshal_VOID__VOID,  // marshaller (type des args)
        G_TYPE_NONE,               // type de retour
        0                          // nombre de paramètres
    );



    g_signal_new(
        "fin_recuperation",              // nom du signal
        GTK_TYPE_WIDGET,           // type GObject auquel il appartient
        G_SIGNAL_RUN_FIRST,        // quand les handlers sont appelés
        0,                         // offset dans la structure (0 si pas de classe)
        NULL,                      // accumulateur (NULL = aucun)
        NULL,                      // données accumulateur
        g_cclosure_marshal_VOID__VOID,  // marshaller (type des args)
        G_TYPE_NONE,               // type de retour
        0                          // nombre de paramètres
    );
}

void Liaison_signaux(ParserXML* Parser)
{
    if(Parser->Signaux)
    {
        creation_type_signaux_personnalise();
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

