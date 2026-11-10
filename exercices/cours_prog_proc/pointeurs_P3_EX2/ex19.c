#include <stdio.h>
#include <stdbool.h>
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

void echangerProduits(Produit *a, Produit *b)
{
    assert (a != NULL && b != NULL);

    Produit temp = *a;
    *a = *b;
    *b = temp;
}

// tri par échange

void trierParEchangesPrix(Produit *cat, int n)
{
    assert(cat != NULL && n > 0);

    // soit *p le produit comparé de gauche 
    // soit *q l'autre produit comparé
    for(Produit *p = cat; p < cat + n; p++)
        for (Produit *q = p + 1; q < cat + n; q++)
            if(p->prix > q->prix)        
                echangerProduits(p, q);
        
} 

// tri à bulles
/*
Le mécanisme, une passe à la fois
Le tri à bulles fait ceci : il parcourt le tableau de gauche à droite, 
et à chaque étape il ne regarde que deux éléments côte à côte. Si le voisin 
de gauche est plus grand que le voisin de droite, il les échange. Sinon, 
il ne fait rien et passe à la paire suivante.

// après un tour, l'élément le plus à D est le plus grand
// il faut donc décrémenter de 1
*/
void trierParBullesPrix(Produit *cat, int n)
{
    assert(cat != NULL && n > 0);

    
    // la première boucle permet de parcourir tout le tableau de 0 à n puis 0 à n - 1 ...
    // la deuxième boucle permet de progresser de G à D avec 2 valeurs contigues en commençant par l'index 0 et 1
    for(int ixRight = n - 1; ixRight > 0 ; ixRight--)
    {
        bool tabtrie = true;
        for (int i = 0 ; i < ixRight; i++)
            if(cat[i].prix > cat[i + 1].prix)
            {
                echangerProduits(&cat[i], &cat[i + 1]);
                tabtrie = false;
            }
        // drapeau d'arrêt => si on fait toute la boucle interne sans echanger alors le tableau est trié et arrêt de la boucle ext
        if(tabtrie)
            break;
    }
}

void trierParBullesPointeursPrix(Produit *cat, int n)
{
    assert(cat != NULL && n > 0);

    for (Produit *fin = cat + n - 1; fin > cat; fin--)
        for (Produit *p = cat; p < fin; p++)
            if(p->prix > (p+1)->prix)
                echangerProduits(p, p + 1);

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
    putc('\n', stdout);

    trierParBullesPrix(cat, 4);
    
    afficherCatalogue(cat, 4);

    return 0;
}