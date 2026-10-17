/*** v2 ex 10 ***/

/*
ajoute successivement trois produits à l'aide de realloc — le realloc doit se faire à chaque ajout, pas une seule fois.
Une fonction d'ajout doit recevoir l'adresse du pointeur de tableau et l'adresse du compteur — donc Produit **, pas Produit *.

Pourquoi l'adresse du pointeur ?
C'est le point central de l'exercice (un pointeur de pointeur). realloc peut déplacer le bloc mémoire : il renvoie une nouvelle adresse.
Si la fonction recevait seulement Produit *inventaire, le nouveau pointeur serait perdu au retour de la fonction—
main garderait l'ancienne adresse. En recevant Produit **inventaire, la fonction peut écrire *inventaire = <nouvelle adresse> et main voit le changement.
*/

/*
    RECAP:
    inventaire: c'est le pointeur de pointeur, et sa valeur est l'adresse du pointeur de main.
    *inventaire: c'est la valeur de ce pointeur, donc l'adresse du tableau.
    **inventaire: c'est un Produit entier (la première case).
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef _WIN32
    #include <windows.h>
#endif

typedef struct 
{
    char nom[50];
    float prix;
    unsigned int qteStock;
} Produit;

void afficherProduit(Produit *p)
{
    if (p == NULL)
        {
            fprintf(stderr, "Erreur pointeur NULL ds afficherProduit()\n");
            exit(EXIT_FAILURE);
        }

    printf("nom du produit: %s\n", p->nom);
    printf("prix: %.2f€\n", p->prix);
    printf("quantité en stock: %u\n\n", p->qteStock);
}

// le tableau grandit à chaque ajout
// Produit ** contient l'adresse du pointeur de main=> permet de transmettre au main une nouvelle adresse
bool ajouterProduit(Produit **inventaire, const Produit *nouvProduit, int *nbElementsDsInventaire)
{
    // au premier passage, *inventaire sera NULL
    // realloc(NULL, n) = malloc(n) => correct

    // par contre inventaire = adresse reçue depuis le main ne devrait pas être NULL
    if (inventaire == NULL || nouvProduit == NULL || nbElementsDsInventaire == NULL)
    {
        fprintf(stderr, "Erreur pointeur NULL ds ajouterProduit()\n");
        if(inventaire != NULL)
            free(*inventaire); // libérer le tableau si adresse reçue du main non NULL
        exit(EXIT_FAILURE);
    }

    if(*nbElementsDsInventaire < 0)
    {
        fprintf(stderr, "Erreur le nombre de produits ne peut être < 0\n");
        return false;
    }

    // créer un pointeur temp sécurise (n'écrase pas le premier inventaire si erreur)
    // si realloc échoue, on n'écrase pas *inventaire
    Produit *temp = realloc (*inventaire, (*nbElementsDsInventaire +1) * sizeof(Produit));
    if (temp == NULL)
    {
        fprintf(stderr, "Erreur pointeur NULL ds ajouterProduit()\n");
        exit(EXIT_FAILURE);
    }


    temp[*nbElementsDsInventaire] = *nouvProduit;    
    (*nbElementsDsInventaire)++;

   // *inventaire = pointeur de main ; il reçoit la nouvelle adresse du tableau (temp)
    *inventaire = temp;

    return true;    
}

float calculerValeurInventaire(const Produit *inv, int nbElDsInventaire)
{
    if(inv == NULL)
    {
         fprintf(stderr, "Erreur pointeur NULL dans calculerValeurInventaire()\n");
         exit(EXIT_FAILURE);
    }

    if(nbElDsInventaire < 0)
    {
        fprintf(stderr, "Erreur le nb d'éléments dans l'inventaire ne peut être < 0\n");
        return -1;
    }

    float total = 0.0f;

    for (int i = 0; i < nbElDsInventaire; i++)
        total += inv[i].prix * (float) inv[i].qteStock;

    return total;
}

int main(void)
{  
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
    
    Produit cahier = {"cahier", 2.5f, 4};
    Produit classeur = {"classeur", 4.0f, 2};
    Produit stylo = {"stylo", 1.20f, 10};

    Produit *inventaire = NULL;
    int nbElDsInventaire = 0;

    if(!ajouterProduit(&inventaire, &cahier, &nbElDsInventaire))
    {
        fprintf(stderr, "Erreur ajout produit dans l'inventaire\n");
    }

    if(!ajouterProduit(&inventaire, &classeur, &nbElDsInventaire))
    {
        fprintf(stderr, "Erreur ajout produit dans l'inventaire\n");
    }

    if(!ajouterProduit(&inventaire, &stylo, &nbElDsInventaire))
    {
        fprintf(stderr, "Erreur ajout produit dans l'inventaire\n");
    }

    printf("\n\nCONTENU INVENTAIRE:\n\n");
    for (int i = 0; i < nbElDsInventaire; i ++)
    {
        afficherProduit(&inventaire[i]);
    }

    printf("Valeur inventaire = %.2f€\n\n", calculerValeurInventaire(inventaire, nbElDsInventaire));

    free(inventaire);
    inventaire = NULL;
    return 0;
}