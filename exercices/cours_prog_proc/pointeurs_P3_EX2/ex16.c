#include <stdio.h>
#include <assert.h>

typedef struct 
{
    char nom[50];
    float prix;
    int quantite;
} Produit;

void afficherCatalogue(const Produit *cat, int n)
{
    assert(cat != NULL && n > 0);

    // for(; cat < cat + n; cat++) pas correct car boucle infine et débordement mémoire
    // for(; cat < fin; cat++)) correct avec const Produit *fin = cat + n;
    for (const Produit *p = cat; p < cat + n; p++)
        printf("%-12s %8.2f EUR x %d\n", p->nom, p->prix, p->quantite);
}

double valeurStock(const Produit *cat, int n)
{
    assert(cat != NULL && n > 0);

    double result = 0;    
    const Produit *fin = cat + n;

    for(; cat < fin; cat++)
        result += (cat->prix * cat->quantite);
        
    return result;
}

int main(void)
{
    Produit cat[4] = {
    {"Clavier",    25.00f,  3},
    {"Souris",     12.50f,  8},
    {"Ecran",     149.99f,  2},
    {"Cable HDMI",  7.90f,  10},
    };

    afficherCatalogue(cat, 4);
    printf("Valeur totale du stock : %.2f EUR\n", valeurStock(cat, 4));

    return 0;
}