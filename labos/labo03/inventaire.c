#include <string.h>

#include "inventaire.h"


Inventaire ajouterProduit(Inventaire inv, Produit p)
{
    Inventaire temp;

    int i;

     // on copie tous les éléments précédents de l'inventaire s'il n'était pas vide
    if (inv.nbreProduitStocke > 0)
    {       
        for (i = 0; i < inv.nbreProduitStocke; i++)
        {
            strcpy(temp.inventaire[i].nom, inv.inventaire[i].nom);
            temp.inventaire[i].prix = inv.inventaire[i].prix;
            temp.inventaire[i].qteStock = inv.inventaire[i].qteStock;
        }
    }

    // on ajoute le nouveau produit p dans l'inventaire temp
    strcpy(temp.inventaire[i].nom, p.nom);
    temp.inventaire[i].prix = p.prix;
    temp.inventaire[i].qteStock = p.qteStock;

    // on ajoute 1 au nbre de produit dans l'inventaire
    temp.nbreProduitStocke = ++i;

    // on return le nouvel inventaire 
    return temp;
}

float calculerValeurStock(Inventaire inv)
{
    float total = 0.0f;

    for (int i = 0; i < inv.nbreProduitStocke; i++)
        total += inv.inventaire[i].prix * (float) inv.inventaire[i].qteStock;

    return total;
}
