#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#ifdef _WIN32
    #include <windows.h>
#endif

#include "produit.h"
#include "inventaire.h"
#include "utils.h"

#define FLUX stdout

int main(void)
{
    // permet d'afficher les accents,... via encodage UTF8
    #ifdef _WIN32    
        SetConsoleOutputCP(CP_UTF8);
    #endif

    logDebutProg(FLUX);

    Produit banane = {"banane", 1.5f, 10};
    Produit pomme = {"pomme", 1.0f, 8};
    Produit poire = {"poire", 1.25f, 4};

    Inventaire monInventaire = {0};
    monInventaire= ajouterProduit(monInventaire, banane);
    monInventaire= ajouterProduit(monInventaire, pomme);
    monInventaire= ajouterProduit(monInventaire, poire);

    puts("\n\n*** INVENTAIRE ***\n\n");
    printf("L'inventaire contient %u produits pour une valeur de %.2f€\n\n", 
            monInventaire.nbreProduitStocke, 
            calculerValeurStock(monInventaire));

    for (unsigned int i = 0; i < monInventaire.nbreProduitStocke; i++)
        afficherProduit(monInventaire.inventaire[i]);
    
    logFinProg(FLUX);

    return 0;
}