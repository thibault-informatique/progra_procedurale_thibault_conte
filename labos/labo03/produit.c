#include <stdio.h>

#include "produit.h"

void afficherProduit(Produit p)
{
    printf("nom du produit: %s\n", p.nom);
    printf("prix: %.2f€\n", p.prix);
    printf("quantité en stock: %u\n\n", p.qteStock);
}