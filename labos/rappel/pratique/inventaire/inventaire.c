#include <string.h>

#include "inventaire.h"


Inventaire ajouterProduit(Inventaire inv, Produit p)
{   
    Inventaire temp = inv;  

     // on ajoute le nouveau produit p dans l'inventaire temp s'il reste de la place
     // sinon on retourne l'inventaire initial
     
    if (inv.nbreProduitStocke < 10)
    {
         temp.inventaire[inv.nbreProduitStocke] = p;     

        // on ajoute 1 au nbre de produit dans l'inventaire
        temp.nbreProduitStocke++;
    }

    return temp;  
}

float calculerValeurStock(Inventaire inv)
{
    float total = 0.0f;

    for (int i = 0; i < inv.nbreProduitStocke; i++)
        total += inv.inventaire[i].prix * (float) inv.inventaire[i].qteStock;

    return total;
}
