#include <stdio.h>

#include "produit.h"
#include "utils.h"

void afficherProduit(Produit p)
{
    printf("nom du produit: %s\n", p.nom);
    printf("prix: %.2f€\n", p.prix);
    printf("quantité en stock: %u\n\n", p.qteStock);
}

bool appliquerPromotion(Produit *produit, float reduction)
{
    if (produit == NULL)
        return false;

    float temp = produit->prix;

    // si prix devient négatif avec la réduction
    if((temp -= reduction) <= 0)
    {
        ecrireLog(stderr, "erreur fct appliquerProduit: le prix ne peut être <= 0\n");
        return false;
    }
    else 
    {
        produit->prix -= reduction;
        return true;
    }
}