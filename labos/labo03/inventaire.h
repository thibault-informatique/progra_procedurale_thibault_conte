#ifndef INVENTAIRE_H
#define INVENTAIRE_H

#include "produit.h"

typedef struct
{
    Produit inventaire[10];
    unsigned int nbreProduitStocke;
} Inventaire;

Inventaire ajouterProduit(Inventaire inv, Produit p);

float calculerValeurStock(Inventaire inv);

#endif