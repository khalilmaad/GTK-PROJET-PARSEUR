#include "AppGTK/AppGTK.h"


int main(int argc, char* argv[])
{
    AppGTK* monAPP = init_APP(argc,argv);

    monAPP->debut_chargement(monAPP);
    monAPP->parsing(monAPP,"Preparation_controle.txt");
    //monAPP->create_with_macro(monAPP);
    monAPP->boucle();
    monAPP->boucle();

    return 0;
}
