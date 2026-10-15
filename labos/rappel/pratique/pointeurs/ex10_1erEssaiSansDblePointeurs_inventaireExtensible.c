/*** Construire inventaire dynamique de produits ***/

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

bool ajouterProduit(Produit *inventaire, const Produit *nouvProduit, int tailleInventaire, int *nbElementsDsInventaire)
{
    if (inventaire == NULL || nouvProduit == NULL || nbElementsDsInventaire == NULL)
    {
        fprintf(stderr, "Erreur pointeur NULL ds ajouterProduit()\n");
        exit(EXIT_FAILURE);
    }

    if(*nbElementsDsInventaire < 0 || tailleInventaire < 0)
    {
        fprintf(stderr, "Erreur la taille de l'inventaire ou le nb de produits ne peut être < 0\n");
        return false;
    }
    if(tailleInventaire <= *nbElementsDsInventaire)
    {
        fprintf(stderr, "Erreur inventaire plein\n");
        return false;
    }

    inventaire[*nbElementsDsInventaire] = *nouvProduit;    
    (*nbElementsDsInventaire)++;

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
    int tailleInventaire = 0;
    int nbElDsInventaire = 0;

    inventaire = realloc(inventaire ,(3 * sizeof(Produit)));

    if(inventaire == NULL)
        {
            fprintf(stderr, "Erreur realloc pointeur NULL\n");
            return EXIT_FAILURE;
        }

    tailleInventaire = 3;

    if(!ajouterProduit(inventaire, &cahier, tailleInventaire, &nbElDsInventaire))
    {
        fprintf(stderr, "Erreur ajout produit dans l'inventaire\n");
    }

    if(!ajouterProduit(inventaire, &classeur, tailleInventaire, &nbElDsInventaire))
    {
        fprintf(stderr, "Erreur ajout produit dans l'inventaire\n");
    }

    if(!ajouterProduit(inventaire, &stylo, tailleInventaire, &nbElDsInventaire))
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