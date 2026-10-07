#ifndef PRODUIT_H
#define PRODUIT_H

typedef struct 
{
    char nom[50];
    float prix;
    unsigned int qteStock;
} Produit;


void afficherProduit(Produit p);
#endif