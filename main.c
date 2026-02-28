#include "AppGTK/AppGTK.h"


int main(int argc, char* argv[])
{
    AppGTK* monAPP = init_APP(argc,argv);

    monAPP->debut_chargement(monAPP);
    monAPP->parsing(monAPP,"test_file.txt");
    monAPP->afficher_interface(monAPP->arbre_widget);
    monAPP->boucle();

    return 0;
}
