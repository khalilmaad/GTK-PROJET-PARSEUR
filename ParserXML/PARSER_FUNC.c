
#include "ParseXML.h"
#include "../Widget/GENERAL/Widget.h"



// =============================================
// Fonctions du parser
// =============================================
ParserXML* parser_create(const char* nomFichier) {
    ParserXML* parser = malloc(sizeof(ParserXML));
    if (!parser) return NULL;

    parser->Fichier = fopen(nomFichier,"r");
    if(!parser->Fichier){
        fprintf(stderr, "\033[31mErreur détectée : Impossible d'ouvrir le fichier (%s)\033[0m\n",nomFichier);
        exit(EXIT_FAILURE);
    }
    parser->racine = NULL;
    parser->pile_widget = NULL;
    parser->Signaux = NULL;
    parser->Widget_with_ID = NULL;

    parser->parse = parser_parse;

    return parser;
}

/*
void parser_destroy(ParserXML* parser) {
    if (!parser) return;

    free(parser->nomFichier);
    pile_clear(parser);
    free(parser);
}*/

// Fonction pour afficher les erreurs avec couleur
void print_error(const char* message, int ligne) {
    fprintf(stderr, "\n\033[34mMessage :  \033[31m%s,\033[33m[Ligne = %d]\033[0m\n",
            message, ligne);
}

void print_fatal_error(const char* message) {
    fprintf(stderr, "\n\033[31mErreur détectée : %s\033[0m\n", message);
}

// Fonction pour convertir en minuscules
void to_lowercase(char* str) {
    if (!str) return;
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Fonction principale de parsing
void parser_parse(ParserXML* parser) {
    if (!parser || !parser->Fichier) {
        fprintf(stderr, "Erreur : parser ou fichier invalide\n");
        return;
    }

    char ligne[BUFFER_SIZE];
    int numLigne = 0;

     // Lire ligne par ligne avec fgets
    while (fgets(ligne, sizeof(ligne), parser->Fichier) != NULL) {
        numLigne++;

        size_t longueur = strlen(ligne);

        // Supprimer les caractères de fin de ligne
        if (longueur > 0) {
            // Supprimer \r\n (Windows) ou \n (Unix)
            if (ligne[longueur - 1] == '\n') {
                ligne[longueur - 1] = '\0';
                longueur--;

                // Vérifier si c'était \r\n
                if (longueur > 0 && ligne[longueur - 1] == '\r') {
                    ligne[longueur - 1] = '\0';
                    longueur--;
                }
            }
            // Cas où \r seul (anciens Mac)
            else if (ligne[longueur - 1] == '\r') {
                ligne[longueur - 1] = '\0';
                longueur--;
            }
        }

        traiterLigne(parser, ligne, numLigne);
    }

    fclose(parser->Fichier);
    Liaison_signaux(parser);

    // Vérifier les balises non fermées
    if (!pile_empty(parser)) {
        print_fatal_error("Balises non fermées")    ;
        exit(1);
    }

}
// =============================================
// Traitement des lignes
// =============================================
void traiterLigne(ParserXML* parser, const char* ligne, int numLigne) {
    if (!parser || !ligne) return;

    size_t len = strlen(ligne);
    size_t pos = 0;

    // Parcourir caractère par caractère
    while (pos < len) {
        // Chercher le prochain '<'
        const char* prochain_ouvrant = strchr(ligne + pos, '<');
        if (!prochain_ouvrant) break;  // Plus de balises

        // Mettre à jour la position
        pos = prochain_ouvrant - ligne;

        // Vérifier que ce n'est pas la fin de la ligne
        if (pos + 1 >= len) break;

        // Déterminer le type de balise
        if (ligne[pos + 1] == '/') {
            // Balise fermante
            traiterBaliseFermante(parser, ligne, &pos, numLigne);
        } else {
            // Balise ouvrante
            traiterBaliseOuvrante(parser, ligne, &pos, numLigne);
        }

        // Avancer pour éviter boucle infinie
        // Chercher la fin de la balise courante '>'
        const char* fin_balise = strchr(ligne + pos, '>');
        if (fin_balise) {
            pos = (fin_balise - ligne) + 1;  // Position après '>'
        } else {
            pos++;  // Avancer au moins d'un caractère
        }
    }
}
// =============================================
// Traitement balise ouvrante
// =============================================

void traiterBaliseOuvrante(ParserXML* parser, const char* ligne, size_t* pos, int numLigne) {
    if (!parser || !ligne || !pos) return;

    // Faire une copie de la partie de la ligne à partir de la balise
    const char* debut_balise = ligne + *pos + 1;  // Sauter '<'
    //size_t longueur_restante = strlen(debut_balise);

    // Trouver la fin de la balise '>'
    const char* fin_balise = strchr(debut_balise, '>');
    if (!fin_balise) {
        print_error("Balise mal formée (manque '>')", numLigne);
        exit(1);
    }

    // Extraire tout le contenu entre < et >
    size_t contenu_len = fin_balise - debut_balise;
    char* contenu = malloc(contenu_len + 1);
    if (!contenu) return;

    strncpy(contenu, debut_balise, contenu_len);
    contenu[contenu_len] = '\0';

    // Vérifier si c'est une balise auto-fermante
    _Bool fermante = FALSE;
    if (contenu_len > 0 && contenu[contenu_len - 1] == '/') {
        fermante = TRUE;
        contenu[contenu_len - 1] = '\0';  // Retirer le '/'
    }

    // Utiliser strtok pour extraire le nom du widget
    char* nomWidget = strtok(contenu, " \t\n\r");
    if (!nomWidget) {
        free(contenu);
        print_error("Nom de balise manquant", numLigne);
        exit(1);
    }

    if(!compare(nomWidget,"!--")) goto suivant;

    // Transformer en minuscules
    to_lowercase(nomWidget);

    printf("\033[1;35m====================<\033[0m\033[1;34m%s\033[0m\033[1;35m>====================\033[0m\n",nomWidget);
    printf("\033[0mLigne = \033[1;33m%d\033[0m\n", numLigne);

    // Créer le widget
    Widget* widget = init_func_widget(nomWidget);
    if (!widget) {
        free(contenu);
        print_error("Impossible de créer le widget", numLigne);
        exit(1);
    }

    // Parser les attributs avec strtok
    // Le reste après le nom est les attributs
    char* attributs_str = strtok(NULL, "");
    if (attributs_str) {
        parserAttributs(attributs_str, widget,numLigne);
    }





    // Appliquer les attributs
    if (widget->apply_attribut_func) {
        widget->apply_attribut_func(widget);
    }
    printf("\n\033[1;32m[Succes]\033[0m widget \033[1;34m%s\033[0m pret a l'emploi!\n",nomWidget);

    // Gérer la hiérarchie
    if (!pile_empty(parser)) {
        Widget* parent = pile_top(parser);
        if(parent->set_child) parent->set_child(parent,widget);

        widget->frere = parent->fils;
        parent->fils = widget;

    } else {
        if (!parser->racine) {
            parser->racine = widget;
        } else {
            widget->frere = parser->racine->frere;
            parser->racine->frere = widget;
        }
    }

    printf("\n\n\033[1;35m====================<\\\033[0m\033[1;34m%s\033[0m\033[1;35m>====================\033[0m\n\n",nomWidget);

    // Balise auto-fermante
    //Si ce n'est pas une balise auto fermente Empiler le widget
    if (!fermante) {
        pile_push(parser, widget);
    }

    gerer_widget_with_id(parser,widget,numLigne);

    suivant:

    // Mettre à jour la position
    *pos = (fin_balise - ligne);

    // Nettoyage
    free(contenu);
}

// =============================================
// Traitement balise fermante
// =============================================

void traiterBaliseFermante(ParserXML* parser, const char* ligne, size_t* pos, int numLigne) {
    if (!parser || !ligne || !pos) return;

    // Extraire le nom de la balise fermante
    const char* debut_nom = ligne + *pos + 2;  // Sauter "</"
    const char* fin_balise = strchr(debut_nom, '>');

    if (!fin_balise) {
        print_error("Balise fermante mal formée", numLigne);
        exit(1);
    }

    // Extraire le nom
    size_t nom_len = fin_balise - debut_nom;
    char* nomWidget = malloc(nom_len + 1);
    if (!nomWidget) return;

    strncpy(nomWidget, debut_nom, nom_len);
    nomWidget[nom_len] = '\0';

    // Transformer en minuscules
    to_lowercase(nomWidget);

    if (pile_empty(parser)) {
        char erreur[256];
        snprintf(erreur, sizeof(erreur),
                 "Balise fermante (%s) -> manque balise ouvrante", nomWidget);
        free(nomWidget);
        print_error(erreur, numLigne);
        exit(1);
    }

    // Comparer avec le widget au sommet de la pile
    Widget* top_widget = pile_top(parser);

    if (top_widget && top_widget->Nom && strcmp(top_widget->Nom, nomWidget) == 0) {
        pile_pop(parser);
    } else {
        char erreur[256];
        snprintf(erreur, sizeof(erreur),
                 "Nom Balise fermante (%s) -> Incorrect (attendue: %s)",
                 nomWidget, top_widget ? top_widget->Nom : "NULL");
        free(nomWidget);
        print_error(erreur, numLigne);
        exit(1);
    }

    free(nomWidget);
    *pos = (fin_balise - ligne);  // Mettre à jour la position
}


// =============================================
// Parser les attributs
// =============================================

void attributs_add(Widget* obj, const char* nom, const char* valeur) {
    if (!obj || !nom || !valeur) return;

    if(!compare(nom,"id"))
    {
        obj->Id = strdup(valeur);
        printf("\n\033[1;36m[Affectation]\033[0m ID widget \033[1;34m%s\033[0m = \033[1;33m%s\033[0m\n",nom,valeur);
        return;
    }

    for(int i=0; i < obj->Nbre_Attribut; i++)
    {
        if(!compare(obj->List_Attribut[i].Nom,nom))
        {
            free(obj->List_Attribut[i].Valeur);
            obj->List_Attribut[i].Valeur = strdup(valeur);
            printf("\n\033[1;36m[Affectation]\033[0m Attribut \033[1;34m%s\033[0m = \033[1;33m%s\033[0m\n",nom,valeur);
            return;
        }
    }

    for(int i=0; i < obj->Nbre_Attribut_special; i++)
    {
        if(!compare(obj->List_Attribut_special[i].Nom,nom))
        {
            free(obj->List_Attribut_special[i].Valeur);
            obj->List_Attribut_special[i].Valeur = strdup(valeur);
            printf("\n\033[1;36m[Affectation]\033[0m Attribut special \033[1;34m%s\033[0m = \033[1;33m%s\033[0m\n",nom,valeur);
            return;
        }
    }
    printf("\n\033[1;31m[Affectation]\033[0m Attribut \033[1;34m%s\033[0m = \033[1;33m%s\033[0m\n",nom,valeur);
    printf("\n\033[1;34mMessage : \033[1;31mNom attribut (\033[1;34m%s\033[1;31m) -> Incorrect\n\n\033[0mNom attribut attendu: ",nom);

    for(int i=0; i < obj->Nbre_Attribut; i++)
    {
        printf("\n->\033[1;34m%s\033[0m,",obj->List_Attribut[i].Nom);
    }
    printf("\n\nAutre attribut: (special pour la liaison avec un conteneur<widget parent>)");
    for(int i=0; i < obj->Nbre_Attribut_special; i++)
    {
        printf("\n->\033[1;34m%s\033[0m,",obj->List_Attribut_special[i].Nom);
    }
    printf("\n");

    exit(1);

}


void parserAttributs(const char* attributs_str, Widget* obj,int numLigne) {
    if (!attributs_str || !obj) return;

    // Faire une copie modifiable pour strtok
    char* str = strdup(attributs_str);
    if (!str) return;

    // Nettoyer les espaces au début et à la fin
    char* debut = str;
    while (*debut && isspace((unsigned char)*debut)) debut++;

    char* fin = debut + strlen(debut) - 1;
    while (fin > debut && isspace((unsigned char)*fin)) {
        *fin = '\0';
        fin--;
    }

    // Si la chaîne est vide après nettoyage
    if (strlen(debut) == 0) {
        free(str);
        return;
    }

    // Utiliser strtok pour parser les attributs
    // Format attendu: nom="valeur" nom2="valeur2"
    char* token = strtok(debut, "\"");

    while (token != NULL) {
        // token devrait contenir "nom=" ou " nom="
        char* nom_attribut = token;

        // Nettoyer les espaces avant le nom
        while (*nom_attribut && isspace((unsigned char)*nom_attribut)) nom_attribut++;

        // Trouver le '=' pour séparer nom et valeur
        size_t nom_len = strlen(nom_attribut);
        if (nom_attribut[nom_len-1] != '=') {
            // Pas de '=', peut-être fin de la chaîne
            print_error("Lecture Attribut -> manque de \" ou = | Format attendu: nom=\"valeur\" nom2=\"valeur2\"  ", numLigne);
            exit(1);
        }
        else
        {
            nom_attribut[nom_len-1] = '\0';
        }

        // Le prochain token après strtok sera la valeur
        char* valeur = strtok(NULL, "\"");
        if (!valeur) {
            // Valeur manquante
            print_error("Lecture Attribut -> manque de la valeur | Format attendu: nom=\"valeur\" nom2=\"valeur2\"  ", numLigne);
            exit(1);
        }

        // Ajouter à la map
        attributs_add(obj, nom_attribut, valeur);

        // Continuer avec le prochain attribut
        token = strtok(NULL, "\"");
    }

    free(str);
}
