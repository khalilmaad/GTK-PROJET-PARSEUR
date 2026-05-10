#include "INTERFACE_MACRO.h"
#include "../Widget/GENERAL/Widget.h" // Pour Widget, init_func_widget, attributs_add ...
#include "../ParserXML/ParseXML.h"    // Pour Liste_Gestion_Signaux, gerer_widget_with_id, Liaison_signaux



/*
 * ============================================================
 *  FILE : creation_interface.c
 *  DESCRIPTION :
 *      Traduction du fichier XML de présentation d'ordinateur
 *      en appels C utilisant le moteur de widgets GTK maison.
 *
 *  ARBRE XML (résumé) :
 *
 *  <fenetre id="fenetre_princile">
 *   ├── <headerbar>
 *   └── <scrollbar>
 *        └── <overlay>
 *             ├── <image>  (fond blanc)
 *             └── <box vertical>
 *                  ├── <box> (barre de menu)
 *                  │    └── <frame>
 *                  │         └── <menubar> ... menus ...
 *                  ├── <box> (qualité + liste déroulante)
 *                  │    ├── <frame "qualité">
 *                  │    │    └── <box> radiobuttons
 *                  │    └── <frame "liste déroulante">
 *                  │         └── <comboboxtext> options
 *                  ├── <box> (ergonomie)
 *                  │    └── <frame "ergonomie">
 *                  │         └── <box> checkbuttons
 *                  ├── <box> (utilisation)
 *                  │    └── <frame "utilisation">
 *                  │         └── <box vertical> radiobuttons
 *                  └── <buttonbox> (Ok / Quitter)
 *                       ├── <button "_Ok">  -> ouvre fenetre_dialog
 *                       └── <button "_Quitte"> -> detruit fenetre_princile
 *
 * ============================================================
 */



/*
 * ============================================================
 *  SCHÉMA DES SIGNAUX
 * ============================================================
 *
 *  signal_ok_affiche_dialog ──────> [clicked] ──> afficher(fenetre_dialog)
 *  signal_dialog_delete     ──────> [delete-event] ──> cacher(fenetre_dialog)
 *
 *  signal_oui_affiche_image ──────> [clicked] ──> afficher(fenetre_image)
 *  signal_non_cache_image   ──────> [clicked] ──> cacher(fenetre_image)
 *  signal_annuler_cache_dlg ──────> [clicked] ──> cacher(fenetre_dialog)
 *  signal_annuler_cache_img ──────> [clicked] ──> cacher(fenetre_image)
 *
 *  signal_image_delete      ──────> [delete-event] ──> cacher(fenetre_image)
 *
 *  signal_quitte            ──────> [clicked] ──> detruire(fenetre_princile)
 *
 * ============================================================
 */

Widget* creation_interface()
{
    /* --------------------------------------------------------
     * Initialisation de la liste de gestion des signaux.
     * Cette liste collecte tous les signaux et widgets avec ID
     * pendant la construction, puis les connecte à la fin.
     * -------------------------------------------------------- */
    Liste_Gestion_Signaux* Liste = init_Liste_Gestion_Signaux();

    Widget* racine = NULL;

    /* ========================================================
     * FENETRE PRINCIPALE
     * <fenetre id="fenetre_princile" icone="preferences-system"
     *          type_icone="true" position_auto="centre" largeur="500">
     * ======================================================== */
    Widget* fenetre_principale = init_func_widget("fenetre");
    racine = fenetre_principale;

    fenetre_principale->add_attribut(fenetre_principale, "id",           "fenetre_princile");
    fenetre_principale->add_attribut(fenetre_principale, "icone",        "preferences-system");
    fenetre_principale->add_attribut(fenetre_principale, "type_icone",   "true");
    fenetre_principale->add_attribut(fenetre_principale, "position_auto","centre");
    fenetre_principale->add_attribut(fenetre_principale, "largeur",      "500");

    fenetre_principale->apply_attribut_func(fenetre_principale);
    /* Enregistrement de l'ID pour la résolution des signaux */
    gerer_widget_with_id(Liste, fenetre_principale, 1);

    /* --------------------------------------------------------
     * HEADERBAR
     * <headerbar disposition="icon:close" titre="Presentation ordinateur" />
     * -------------------------------------------------------- */
    Widget* headerbar = init_func_widget("headerbar");
    headerbar->add_attribut(headerbar, "disposition", "icon:close");
    headerbar->add_attribut(headerbar, "titre",       "Presentation ordinateur");

    fenetre_principale->set_child(fenetre_principale, headerbar);
    headerbar->apply_attribut_func(headerbar);

    /* ========================================================
     * SCROLLBAR  (contient l'overlay)
     * <scrollbar>
     * ======================================================== */
    Widget* scrollbar = init_func_widget("scrollbar");
    fenetre_principale->set_child(fenetre_principale, scrollbar);
    scrollbar->apply_attribut_func(scrollbar);

    /* ========================================================
     * OVERLAY  (fond image + contenu par-dessus)
     * <overlay>
     * ======================================================== */
    Widget* overlay = init_func_widget("overlay");
    scrollbar->set_child(scrollbar, overlay);
    /* overlay n'a pas d'apply_attribut_func (NULL dans INIT_FUNC_OVERLAY) */

    /* --------------------------------------------------------
     * IMAGE DE FOND
     * <image nom=".\image\whiteback.jpg" />
     * -------------------------------------------------------- */
    Widget* image_fond = init_func_widget("image");
    image_fond->add_attribut(image_fond, "nom", ".\\image\\whiteback.jpg");

    overlay->set_child(overlay, image_fond);
    image_fond->apply_attribut_func(image_fond);

    /* ========================================================
     * BOX PRINCIPALE (orientation verticale)
     * <box orientation="vertical">
     * ======================================================== */
    Widget* box_principale = init_func_widget("box");
    box_principale->add_attribut(box_principale, "orientation", "vertical");

    overlay->set_child(overlay, box_principale);
    box_principale->apply_attribut_func(box_principale);

    /* =========================================================
     * --- SECTION 1 : BARRE DE MENU ---
     * <box insert_cote="haut">
     *   <frame insert_cote="gauche">
     *     <menubar>
     *       <menuitem label="Ordinateur"> ...sous-menus... </menuitem>
     *       <separatormenuitem />
     *       <menuitem label="Portable"/>
     *       <separatormenuitem />
     *       <menuitem label="Ecouteur"/>
     *     </menubar>
     *   </frame>
     * </box>
     * ========================================================= */
    Widget* box_menu = init_func_widget("box");
    box_menu->add_attribut(box_menu, "insert_cote", "haut");

    box_principale->set_child(box_principale, box_menu);
    box_menu->apply_attribut_func(box_menu);

    /* Frame autour de la menubar */
    Widget* frame_menu = init_func_widget("frame");
    frame_menu->add_attribut(frame_menu, "insert_cote", "gauche");

    box_menu->set_child(box_menu, frame_menu);
    frame_menu->apply_attribut_func(frame_menu);

    /* MenuBar */
    Widget* menubar = init_func_widget("menubar");
    menubar->add_attribut(menubar, "insert_cote", "gauche");

    frame_menu->set_child(frame_menu, menubar);
    /* menubar n'a pas d'apply_attribut_func (NULL dans INIT_FUNC_MENUBAR) */

    /* --- MenuItem "Ordinateur" avec sous-menus --- */
    Widget* item_ordinateur = init_func_widget("menuitem");
    item_ordinateur->add_attribut(item_ordinateur, "label", "Ordinateur");

    menubar->set_child(menubar, item_ordinateur);
    item_ordinateur->apply_attribut_func(item_ordinateur);

    /* Menu déroulant de "Ordinateur" */
    Widget* menu_ordinateur = init_func_widget("menu");
    item_ordinateur->set_child(item_ordinateur, menu_ordinateur);

    /* Sous-item "Marque" */
    Widget* item_marque = init_func_widget("menuitem");
    item_marque->add_attribut(item_marque, "label", "Marque");
    menu_ordinateur->set_child(menu_ordinateur, item_marque);
    item_marque->apply_attribut_func(item_marque);

    Widget* menu_marque = init_func_widget("menu");
    menu_marque->add_attribut(menu_marque, "horizontal", "true");
    item_marque->set_child(item_marque, menu_marque);

    Widget* item_m111 = init_func_widget("menuitem");
    item_m111->add_attribut(item_m111, "label", "option 111");
    menu_marque->set_child(menu_marque, item_m111);
    item_m111->apply_attribut_func(item_m111);

    Widget* item_m112 = init_func_widget("menuitem");
    item_m112->add_attribut(item_m112, "label", "option 112");
    menu_marque->set_child(menu_marque, item_m112);
    item_m112->apply_attribut_func(item_m112);

    Widget* item_m113 = init_func_widget("menuitem");
    item_m113->add_attribut(item_m113, "label", "option 113");
    menu_marque->set_child(menu_marque, item_m113);
    item_m113->apply_attribut_func(item_m113);

    /* Sous-item "Puissance" */
    Widget* item_puissance = init_func_widget("menuitem");
    item_puissance->add_attribut(item_puissance, "label", "Puissance");
    menu_ordinateur->set_child(menu_ordinateur, item_puissance);
    item_puissance->apply_attribut_func(item_puissance);

    Widget* menu_puissance = init_func_widget("menu");
    menu_puissance->add_attribut(menu_puissance, "horizontal", "true");
    item_puissance->set_child(item_puissance, menu_puissance);

    Widget* item_processor = init_func_widget("menuitem");
    item_processor->add_attribut(item_processor, "label", "Processor");
    menu_puissance->set_child(menu_puissance, item_processor);
    item_processor->apply_attribut_func(item_processor);

    Widget* item_vitesse = init_func_widget("menuitem");
    item_vitesse->add_attribut(item_vitesse, "label", "Vitesse");
    menu_puissance->set_child(menu_puissance, item_vitesse);
    item_vitesse->apply_attribut_func(item_vitesse);

    Widget* item_disque = init_func_widget("menuitem");
    item_disque->add_attribut(item_disque, "label", "Disque Dur");
    menu_puissance->set_child(menu_puissance, item_disque);
    item_disque->apply_attribut_func(item_disque);

    /* Sous-item "Prix" */
    Widget* item_prix = init_func_widget("menuitem");
    item_prix->add_attribut(item_prix, "label", "Prix");
    menu_ordinateur->set_child(menu_ordinateur, item_prix);
    item_prix->apply_attribut_func(item_prix);

    Widget* menu_prix = init_func_widget("menu");
    menu_prix->add_attribut(menu_prix, "horizontal", "true");
    item_prix->set_child(item_prix, menu_prix);

    Widget* item_p131 = init_func_widget("menuitem");
    item_p131->add_attribut(item_p131, "label", "option 131");
    menu_prix->set_child(menu_prix, item_p131);
    item_p131->apply_attribut_func(item_p131);

    Widget* item_p132 = init_func_widget("menuitem");
    item_p132->add_attribut(item_p132, "label", "option 132");
    menu_prix->set_child(menu_prix, item_p132);
    item_p132->apply_attribut_func(item_p132);

    Widget* item_p133 = init_func_widget("menuitem");
    item_p133->add_attribut(item_p133, "label", "option 133");
    menu_prix->set_child(menu_prix, item_p133);
    item_p133->apply_attribut_func(item_p133);

    /* Séparateur */
    Widget* sep1 = init_func_widget("separatormenuitem");
    menubar->set_child(menubar, sep1);

    /* MenuItem "Portable" */
    Widget* item_portable = init_func_widget("menuitem");
    item_portable->add_attribut(item_portable, "label", "Portable");
    menubar->set_child(menubar, item_portable);
    item_portable->apply_attribut_func(item_portable);

    /* Séparateur */
    Widget* sep2 = init_func_widget("separatormenuitem");
    menubar->set_child(menubar, sep2);

    /* MenuItem "Ecouteur" */
    Widget* item_ecouteur = init_func_widget("menuitem");
    item_ecouteur->add_attribut(item_ecouteur, "label", "Ecouteur");
    menubar->set_child(menubar, item_ecouteur);
    item_ecouteur->apply_attribut_func(item_ecouteur);

    /* =========================================================
     * --- SECTION 2 : QUALITÉ + LISTE DÉROULANTE ---
     * <box insert_cote="haut" margin_top="70">
     *   <frame label="La qualite de votre Ordinateur" ...>
     *     <box> radiobuttons </box>
     *   </frame>
     *   <frame label="Liste deroulante" ...>
     *     <comboboxtext> options </comboboxtext>
     *   </frame>
     * </box>
     * ========================================================= */
    Widget* box_qualite = init_func_widget("box");
    box_qualite->add_attribut(box_qualite, "insert_cote",  "haut");
    box_qualite->add_attribut(box_qualite, "margin_top",   "70");

    box_principale->set_child(box_principale, box_qualite);
    box_qualite->apply_attribut_func(box_qualite);

    /* Frame "La qualite de votre Ordinateur" */
    Widget* frame_qualite = init_func_widget("frame");
    frame_qualite->add_attribut(frame_qualite, "label",               "La qualite de votre Ordinateur");
    frame_qualite->add_attribut(frame_qualite, "alignement_vertical", "haut");
    frame_qualite->add_attribut(frame_qualite, "insert_cote",         "gauche");

    box_qualite->set_child(box_qualite, frame_qualite);
    frame_qualite->apply_attribut_func(frame_qualite);

    /* Box des radio buttons de qualité */
    Widget* box_radio1 = init_func_widget("box");
    box_radio1->add_attribut(box_radio1, "espacement_enfant", "0");

    frame_qualite->set_child(frame_qualite, box_radio1);
    box_radio1->apply_attribut_func(box_radio1);

    /* RadioButton "Tres bonne" */
    Widget* radio1_tres_bonne = init_func_widget("buttonradio");
    radio1_tres_bonne->add_attribut(radio1_tres_bonne, "groupe",      "radio1");
    radio1_tres_bonne->add_attribut(radio1_tres_bonne, "label",       "Tres bonne");
    radio1_tres_bonne->add_attribut(radio1_tres_bonne, "insert_cote", "gauche");

    box_radio1->set_child(box_radio1, radio1_tres_bonne);
    radio1_tres_bonne->apply_attribut_func(radio1_tres_bonne);

    /* RadioButton "Moyenne" */
    Widget* radio1_moyenne = init_func_widget("buttonradio");
    radio1_moyenne->add_attribut(radio1_moyenne, "groupe",      "radio1");
    radio1_moyenne->add_attribut(radio1_moyenne, "label",       "Moyenne");
    radio1_moyenne->add_attribut(radio1_moyenne, "insert_cote", "gauche");

    box_radio1->set_child(box_radio1, radio1_moyenne);
    radio1_moyenne->apply_attribut_func(radio1_moyenne);

    /* RadioButton "Faible" */
    Widget* radio1_faible = init_func_widget("buttonradio");
    radio1_faible->add_attribut(radio1_faible, "groupe",      "radio1");
    radio1_faible->add_attribut(radio1_faible, "label",       "Faible");
    radio1_faible->add_attribut(radio1_faible, "insert_cote", "gauche");

    box_radio1->set_child(box_radio1, radio1_faible);
    radio1_faible->apply_attribut_func(radio1_faible);

    /* Frame "Liste deroulante" */
    Widget* frame_liste = init_func_widget("frame");
    frame_liste->add_attribut(frame_liste, "label",               "Liste deroulante");
    frame_liste->add_attribut(frame_liste, "alignement_vertical", "haut");
    frame_liste->add_attribut(frame_liste, "insert_cote",         "droite");

    box_qualite->set_child(box_qualite, frame_liste);
    frame_liste->apply_attribut_func(frame_liste);

    /* ComboBoxText avec options */
    Widget* combobox = init_func_widget("comboboxtext");
    frame_liste->set_child(frame_liste, combobox);
    /* Les options sont ajoutées via set_child de comboboxtext */

    Widget* opt_marque  = init_func_widget("option");
    opt_marque->add_attribut(opt_marque, "texte", "Choix de la marque");
    combobox->set_child(combobox, opt_marque);

    Widget* opt_hp = init_func_widget("option");
    opt_hp->add_attribut(opt_hp, "texte", "HP");
    combobox->set_child(combobox, opt_hp);

    Widget* opt_dell = init_func_widget("option");
    opt_dell->add_attribut(opt_dell, "texte", "DELL");
    combobox->set_child(combobox, opt_dell);

    Widget* opt_asus = init_func_widget("option");
    opt_asus->add_attribut(opt_asus, "texte", "ASUS");
    combobox->set_child(combobox, opt_asus);

    Widget* opt_acer = init_func_widget("option");
    opt_acer->add_attribut(opt_acer, "texte", "ACER");
    combobox->set_child(combobox, opt_acer);

    /* Applique les attributs du combobox APRÈS ajout des options */
    combobox->apply_attribut_func(combobox);

    /* =========================================================
     * --- SECTION 3 : ERGONOMIE ---
     * <box insert_cote="haut" margin_top="70">
     *   <frame label="Son ergonomie" ...>
     *     <box> checkbuttons </box>
     *   </frame>
     * </box>
     * ========================================================= */
    Widget* box_ergo = init_func_widget("box");
    box_ergo->add_attribut(box_ergo, "insert_cote", "haut");
    box_ergo->add_attribut(box_ergo, "margin_top",  "70");

    box_principale->set_child(box_principale, box_ergo);
    box_ergo->apply_attribut_func(box_ergo);

    Widget* frame_ergo = init_func_widget("frame");
    frame_ergo->add_attribut(frame_ergo, "label",               "Son ergonomie");
    frame_ergo->add_attribut(frame_ergo, "alignement_vertical", "haut");
    frame_ergo->add_attribut(frame_ergo, "insert_cote",         "gauche");

    box_ergo->set_child(box_ergo, frame_ergo);
    frame_ergo->apply_attribut_func(frame_ergo);

    Widget* box_check = init_func_widget("box");
    box_check->add_attribut(box_check, "espacement_enfant", "0");

    frame_ergo->set_child(frame_ergo, box_check);
    box_check->apply_attribut_func(box_check);

    /* CheckButton "Conviviale" */
    Widget* cb_conviviale = init_func_widget("checkbutton");
    cb_conviviale->add_attribut(cb_conviviale, "label",       "Conviviale");
    cb_conviviale->add_attribut(cb_conviviale, "insert_cote", "gauche");
    box_check->set_child(box_check, cb_conviviale);
    cb_conviviale->apply_attribut_func(cb_conviviale);

    /* CheckButton "Interessant" */
    Widget* cb_interessant = init_func_widget("checkbutton");
    cb_interessant->add_attribut(cb_interessant, "label",       "Interessant");
    cb_interessant->add_attribut(cb_interessant, "insert_cote", "gauche");
    box_check->set_child(box_check, cb_interessant);
    cb_interessant->apply_attribut_func(cb_interessant);

    /* CheckButton "Facile a utiliser" */
    Widget* cb_facile = init_func_widget("checkbutton");
    cb_facile->add_attribut(cb_facile, "label",       "Facile a utiliser");
    cb_facile->add_attribut(cb_facile, "insert_cote", "gauche");
    box_check->set_child(box_check, cb_facile);
    cb_facile->apply_attribut_func(cb_facile);

    /* CheckButton "Optimiser le travail" */
    Widget* cb_optimiser = init_func_widget("checkbutton");
    cb_optimiser->add_attribut(cb_optimiser, "label",       "Optimiser le travail");
    cb_optimiser->add_attribut(cb_optimiser, "insert_cote", "gauche");
    box_check->set_child(box_check, cb_optimiser);
    cb_optimiser->apply_attribut_func(cb_optimiser);

    /* =========================================================
     * --- SECTION 4 : UTILISATION ---
     * <box insert_cote="haut" margin_top="70">
     *   <frame label="Utilisation de votre Ordinateur" ...>
     *     <box orientation="vertical"> radiobuttons </box>
     *   </frame>
     * </box>
     * ========================================================= */
    Widget* box_utilisation = init_func_widget("box");
    box_utilisation->add_attribut(box_utilisation, "insert_cote", "haut");
    box_utilisation->add_attribut(box_utilisation, "margin_top",  "70");

    box_principale->set_child(box_principale, box_utilisation);
    box_utilisation->apply_attribut_func(box_utilisation);

    Widget* frame_utilisation = init_func_widget("frame");
    frame_utilisation->add_attribut(frame_utilisation, "label",               "Utilisation de votre Ordinateur");
    frame_utilisation->add_attribut(frame_utilisation, "alignement_vertical", "haut");
    frame_utilisation->add_attribut(frame_utilisation, "insert_cote",         "gauche");

    box_utilisation->set_child(box_utilisation, frame_utilisation);
    frame_utilisation->apply_attribut_func(frame_utilisation);

    Widget* box_radio2 = init_func_widget("box");
    box_radio2->add_attribut(box_radio2, "orientation",       "vertical");
    box_radio2->add_attribut(box_radio2, "espacement_enfant", "0");

    frame_utilisation->set_child(frame_utilisation, box_radio2);
    box_radio2->apply_attribut_func(box_radio2);

    /* RadioButton groupe radio2 - Tres bonne */
    Widget* radio2_tres_bonne = init_func_widget("buttonradio");
    radio2_tres_bonne->add_attribut(radio2_tres_bonne, "groupe",      "radio2");
    radio2_tres_bonne->add_attribut(radio2_tres_bonne, "label",       "Tres bonne");
    radio2_tres_bonne->add_attribut(radio2_tres_bonne, "insert_cote", "gauche");
    box_radio2->set_child(box_radio2, radio2_tres_bonne);
    radio2_tres_bonne->apply_attribut_func(radio2_tres_bonne);

    /* RadioButton groupe radio2 - Moyenne */
    Widget* radio2_moyenne = init_func_widget("buttonradio");
    radio2_moyenne->add_attribut(radio2_moyenne, "groupe",      "radio2");
    radio2_moyenne->add_attribut(radio2_moyenne, "label",       "Moyenne");
    radio2_moyenne->add_attribut(radio2_moyenne, "insert_cote", "gauche");
    box_radio2->set_child(box_radio2, radio2_moyenne);
    radio2_moyenne->apply_attribut_func(radio2_moyenne);

    /* RadioButton groupe radio2 - Faible */
    Widget* radio2_faible = init_func_widget("buttonradio");
    radio2_faible->add_attribut(radio2_faible, "groupe",      "radio2");
    radio2_faible->add_attribut(radio2_faible, "label",       "Faible");
    radio2_faible->add_attribut(radio2_faible, "insert_cote", "gauche");
    box_radio2->set_child(box_radio2, radio2_faible);
    radio2_faible->apply_attribut_func(radio2_faible);

    /* =========================================================
     * --- SECTION 5 : BUTTONBOX (Ok / Quitter) ---
     * <buttonbox insert_cote="bas" disposition="centre"
     *            espacement_enfant="20" margin_bottom="10">
     *   <button "_Ok">   -> signal afficher fenetre_dialog
     *   <button "_Quitte"> -> signal detruire fenetre_princile
     * </buttonbox>
     * ========================================================= */
    Widget* buttonbox_actions = init_func_widget("buttonbox");
    buttonbox_actions->add_attribut(buttonbox_actions, "insert_cote",      "bas");
    buttonbox_actions->add_attribut(buttonbox_actions, "disposition",      "centre");
    buttonbox_actions->add_attribut(buttonbox_actions, "espacement_enfant","20");
    buttonbox_actions->add_attribut(buttonbox_actions, "margin_bottom",    "10");

    box_principale->set_child(box_principale, buttonbox_actions);
    buttonbox_actions->apply_attribut_func(buttonbox_actions);

    /* ----------------------------------------------------------
     * BOUTON "_Ok"
     * Quand cliqué -> afficher(fenetre_dialog)
     * <button label="_Ok" icone=".\image\ouvrirfenetre.jpeg">
     *   <signal fonction="afficher">
     *     <fenetre id="fenetre_dialog" ...> ... </fenetre>
     *   </signal>
     * </button>
     * ---------------------------------------------------------- */
    Widget* btn_ok = init_func_widget("button");
    btn_ok->add_attribut(btn_ok, "label", "_Ok");
    btn_ok->add_attribut(btn_ok, "icone", ".\\image\\ouvrirfenetre.jpeg");

    buttonbox_actions->set_child(buttonbox_actions, btn_ok);
    btn_ok->apply_attribut_func(btn_ok);

    /* === FENETRE DIALOG (créée et enregistrée, mais cachée) ===
     *
     * <fenetre id="fenetre_dialog" hauteur="100" largeur="270"
     *          titre=" " icone="dialog-warning" type_icone="true"
     *          position_auto="centre" type_fenetre="dialog">
     *
     * Structure interne :
     *   <signal type="delete-event" fonction="cacher" sible="fenetre_dialog"/>
     *   <box orientation="vertical">
     *     <box insert_cote="haut" etendre="true" margin_left="30">
     *       <image type="true" nom="dialog-warning" taille="30" />
     *       <label texte="Voulez-vous afficher une image ?" />
     *     </box>
     *     <buttonbox insert_cote="bas" ...>
     *       <button "Oui">  -> afficher(fenetre_image)
     *       <button "Non">  -> cacher(fenetre_image)
     *       <button "Annuler"> -> cacher(fenetre_dialog) + cacher(fenetre_image)
     *     </buttonbox>
     *   </box>
     * </fenetre>
     */
    Widget* fenetre_dialog = init_func_widget("fenetre");
    fenetre_dialog->add_attribut(fenetre_dialog, "id",           "fenetre_dialog");
    fenetre_dialog->add_attribut(fenetre_dialog, "hauteur",      "100");
    fenetre_dialog->add_attribut(fenetre_dialog, "largeur",      "270");
    fenetre_dialog->add_attribut(fenetre_dialog, "titre",        " ");
    fenetre_dialog->add_attribut(fenetre_dialog, "icone",        "dialog-warning");
    fenetre_dialog->add_attribut(fenetre_dialog, "type_icone",   "true");
    fenetre_dialog->add_attribut(fenetre_dialog, "position_auto","centre");
    fenetre_dialog->add_attribut(fenetre_dialog, "type_fenetre", "dialog");

    fenetre_dialog->apply_attribut_func(fenetre_dialog);
    gerer_widget_with_id(Liste, fenetre_dialog, 0);

    /* Signal delete-event sur fenetre_dialog -> cacher fenetre_dialog */
    Widget* signal_dialog_delete = init_func_widget("signal");
    signal_dialog_delete->add_attribut(signal_dialog_delete, "sible",    "fenetre_dialog");
    signal_dialog_delete->add_attribut(signal_dialog_delete, "type",     "delete-event");
    signal_dialog_delete->add_attribut(signal_dialog_delete, "fonction", "cacher");
    /* Le widget source du signal est fenetre_dialog elle-même */
    signal_dialog_delete->Widget_Ptr = fenetre_dialog->Widget_Ptr;
    gerer_widget_with_id(Liste, signal_dialog_delete, 0);

    /* Box verticale interne du dialog */
    Widget* box_dialog = init_func_widget("box");
    box_dialog->add_attribut(box_dialog, "orientation", "vertical");

    fenetre_dialog->set_child(fenetre_dialog, box_dialog);
    box_dialog->apply_attribut_func(box_dialog);

    /* Box du haut (icone + label message) */
    Widget* box_dialog_haut = init_func_widget("box");
    box_dialog_haut->add_attribut(box_dialog_haut, "insert_cote",  "haut");
    box_dialog_haut->add_attribut(box_dialog_haut, "etendre",      "true");
    box_dialog_haut->add_attribut(box_dialog_haut, "margin_left",  "30");

    box_dialog->set_child(box_dialog, box_dialog_haut);
    box_dialog_haut->apply_attribut_func(box_dialog_haut);

    /* Icone d'avertissement */
    Widget* img_warning = init_func_widget("image");
    img_warning->add_attribut(img_warning, "type",        "true");
    img_warning->add_attribut(img_warning, "nom",         "dialog-warning");
    img_warning->add_attribut(img_warning, "taille",      "30");
    img_warning->add_attribut(img_warning, "insert_cote", "gauche");

    box_dialog_haut->set_child(box_dialog_haut, img_warning);
    img_warning->apply_attribut_func(img_warning);

    /* Label du message */
    Widget* label_question = init_func_widget("label");
    label_question->add_attribut(label_question, "texte",       "Voulez-vous afficher une image ?");
    label_question->add_attribut(label_question, "insert_cote", "gauche");
    label_question->add_attribut(label_question, "etendre",     "true");

    box_dialog_haut->set_child(box_dialog_haut, label_question);
    label_question->apply_attribut_func(label_question);

    /* ButtonBox bas du dialog (Oui / Non / Annuler) */
    Widget* buttonbox_dialog = init_func_widget("buttonbox");
    buttonbox_dialog->add_attribut(buttonbox_dialog, "insert_cote",      "bas");
    buttonbox_dialog->add_attribut(buttonbox_dialog, "disposition",      "centre");
    buttonbox_dialog->add_attribut(buttonbox_dialog, "espacement_enfant","5");
    buttonbox_dialog->add_attribut(buttonbox_dialog, "margin",           "0 10 5");

    box_dialog->set_child(box_dialog, buttonbox_dialog);
    buttonbox_dialog->apply_attribut_func(buttonbox_dialog);

    /* === FENETRE IMAGE (créée ici, référencée par les signaux) ===
     * <fenetre id="fenetre_image" titre=" " icone=".\image\cat.jpg"
     *          position_auto="centre" type_fenetre="dialog">
     *   <signal type="delete-event" fonction="cacher" sible="fenetre_image"/>
     *   <image nom=".\image\cat.jpg"/>
     * </fenetre>
     */
    Widget* fenetre_image = init_func_widget("fenetre");
    fenetre_image->add_attribut(fenetre_image, "id",           "fenetre_image");
    fenetre_image->add_attribut(fenetre_image, "titre",        " ");
    fenetre_image->add_attribut(fenetre_image, "icone",        ".\\image\\cat.jpg");
    fenetre_image->add_attribut(fenetre_image, "position_auto","centre");
    fenetre_image->add_attribut(fenetre_image, "type_fenetre", "dialog");

    fenetre_image->apply_attribut_func(fenetre_image);
    gerer_widget_with_id(Liste, fenetre_image, 0);

    /* Signal delete-event sur fenetre_image -> cacher fenetre_image */
    Widget* signal_image_delete = init_func_widget("signal");
    signal_image_delete->add_attribut(signal_image_delete, "sible",    "fenetre_image");
    signal_image_delete->add_attribut(signal_image_delete, "type",     "delete-event");
    signal_image_delete->add_attribut(signal_image_delete, "fonction", "cacher");
    signal_image_delete->Widget_Ptr = fenetre_image->Widget_Ptr;
    gerer_widget_with_id(Liste, signal_image_delete, 0);

    /* Image du chat dans fenetre_image */
    Widget* img_chat = init_func_widget("image");
    img_chat->add_attribut(img_chat, "nom", ".\\image\\cat.jpg");

    fenetre_image->set_child(fenetre_image, img_chat);
    img_chat->apply_attribut_func(img_chat);

    /* ----------------------------------------------------------
     * BOUTON "Oui" -> afficher(fenetre_image)
     * ---------------------------------------------------------- */
    Widget* btn_oui = init_func_widget("button");
    btn_oui->add_attribut(btn_oui, "label", "Oui");

    buttonbox_dialog->set_child(buttonbox_dialog, btn_oui);
    btn_oui->apply_attribut_func(btn_oui);

    Widget* signal_oui = init_func_widget("signal");
    signal_oui->add_attribut(signal_oui, "sible",    "fenetre_image");
    signal_oui->add_attribut(signal_oui, "fonction", "afficher");
    signal_oui->add_attribut(signal_oui, "type",     "clicked");

    btn_oui->set_child(btn_oui, signal_oui);
    gerer_widget_with_id(Liste, signal_oui, 0);

    /* ----------------------------------------------------------
     * BOUTON "Non" -> cacher(fenetre_image)
     * ---------------------------------------------------------- */
    Widget* btn_non = init_func_widget("button");
    btn_non->add_attribut(btn_non, "label", "Non");

    buttonbox_dialog->set_child(buttonbox_dialog, btn_non);
    btn_non->apply_attribut_func(btn_non);

    Widget* signal_non = init_func_widget("signal");
    signal_non->add_attribut(signal_non, "sible",    "fenetre_image");
    signal_non->add_attribut(signal_non, "fonction", "cacher");
    signal_non->add_attribut(signal_non, "type",     "clicked");

    btn_non->set_child(btn_non, signal_non);
    gerer_widget_with_id(Liste, signal_non, 0);

    /* ----------------------------------------------------------
     * BOUTON "Annuler" -> cacher(fenetre_dialog) + cacher(fenetre_image)
     * (deux signaux sur le même bouton)
     * ---------------------------------------------------------- */
    Widget* btn_annuler = init_func_widget("button");
    btn_annuler->add_attribut(btn_annuler, "label", "Annuler");

    buttonbox_dialog->set_child(buttonbox_dialog, btn_annuler);
    btn_annuler->apply_attribut_func(btn_annuler);

    /* Signal 1 : cacher fenetre_dialog */
    Widget* signal_annuler_dlg = init_func_widget("signal");
    signal_annuler_dlg->add_attribut(signal_annuler_dlg, "sible",    "fenetre_dialog");
    signal_annuler_dlg->add_attribut(signal_annuler_dlg, "fonction", "cacher");
    signal_annuler_dlg->add_attribut(signal_annuler_dlg, "type",     "clicked");

    btn_annuler->set_child(btn_annuler, signal_annuler_dlg);
    gerer_widget_with_id(Liste, signal_annuler_dlg, 0);

    /* Signal 2 : cacher fenetre_image */
    Widget* signal_annuler_img = init_func_widget("signal");
    signal_annuler_img->add_attribut(signal_annuler_img, "sible",    "fenetre_image");
    signal_annuler_img->add_attribut(signal_annuler_img, "fonction", "cacher");
    signal_annuler_img->add_attribut(signal_annuler_img, "type",     "clicked");

    btn_annuler->set_child(btn_annuler, signal_annuler_img);
    gerer_widget_with_id(Liste, signal_annuler_img, 0);

    /* ----------------------------------------------------------
     * SIGNAL du bouton "Ok" -> afficher fenetre_dialog
     * Ce signal est rattaché à btn_ok (pas à fenetre_dialog)
     * ---------------------------------------------------------- */
    Widget* signal_ok = init_func_widget("signal");
    signal_ok->add_attribut(signal_ok, "sible",    "fenetre_dialog");
    signal_ok->add_attribut(signal_ok, "fonction", "afficher");
    signal_ok->add_attribut(signal_ok, "type",     "clicked");

    btn_ok->set_child(btn_ok, signal_ok);
    gerer_widget_with_id(Liste, signal_ok, 0);

    /* ----------------------------------------------------------
     * BOUTON "_Quitte"
     * <button label="_Quitte" icone=".\image\fermerfenetre2.png">
     *   <signal fonction="detruire" sible="fenetre_princile"/>
     * </button>
     * ---------------------------------------------------------- */
    Widget* btn_quitte = init_func_widget("button");
    btn_quitte->add_attribut(btn_quitte, "label", "_Quitte");
    btn_quitte->add_attribut(btn_quitte, "icone", ".\\image\\fermerfenetre2.png");

    buttonbox_actions->set_child(buttonbox_actions, btn_quitte);
    btn_quitte->apply_attribut_func(btn_quitte);

    Widget* signal_quitte = init_func_widget("signal");
    signal_quitte->add_attribut(signal_quitte, "sible",    "fenetre_princile");
    signal_quitte->add_attribut(signal_quitte, "fonction", "detruire");
    signal_quitte->add_attribut(signal_quitte, "type",     "clicked");

    btn_quitte->set_child(btn_quitte, signal_quitte);
    gerer_widget_with_id(Liste, signal_quitte, 0);

    /* ========================================================
     * CONNEXION FINALE DE TOUS LES SIGNAUX
     * À ce stade, tous les widgets avec ID sont enregistrés
     * dans la Liste. Liaison_signaux parcourt la liste des
     * signaux et les connecte à leurs cibles via g_signal_connect.
     * ======================================================== */
    Liaison_signaux(Liste);

    return racine;
}
