#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
#endif

//#include "inventaire.h"
#include "produit.h"

int main(void)
{
    // permet d'afficher les accents,... via encodage UTF8
    #ifdef _WIN32    
        SetConsoleOutputCP(CP_UTF8);
    #endif

    Produit test = {"bananes", 3.5, 10};

    afficherProduit(test);


    return 0;
}