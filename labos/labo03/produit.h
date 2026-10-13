#ifndef PRODUIT_H
#define PRODUIT_H

#include <stdbool.h>

typedef struct 
{
    char nom[50];
    float prix;
    unsigned int qteStock;
} Produit;


void afficherProduit(Produit p);

bool appliquerPromotion(Produit *produit, float reduction);
#endif