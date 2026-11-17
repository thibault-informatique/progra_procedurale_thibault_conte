#include <stdio.h>
#include <stdlib.h>

// extrait les nbrs pairs d'un tableau dans un nouveau tableau de taille exacte
int *filtrerPairs(const int *tab, int n, int *nbResultats)
{
    if (tab == NULL || nbResultats == NULL)
        return NULL;

    int nbPairs = 0;

    // 1 compter les nbres pairs au premier passage
    for (int i = 0; i < n; i++)
        if( (*(tab + i) % 2) == 0)
            nbPairs++;
    
    // si aucun nb pair
    if (nbPairs == 0)
    {
        *nbResultats = 0;
        return NULL;
    }

    //2 Allouer un tab de la bonne taille et le remplir au deuxième passage
    int *pNewTab = (int *) malloc (nbPairs * sizeof(*pNewTab));

    if(pNewTab == NULL)
        return NULL;
    
   for (int i = 0, j = 0; i < n && j < nbPairs; i++)
        if( (*(tab + i) % 2) == 0)
            *(pNewTab + j++) = *(tab + i);
    
    //3 Ecrire le nb de Resultat dans *nbResultats et return
    *nbResultats = nbPairs;
    return pNewTab;
}

int main(void)
{

    // int tab[] = {3,8,5,12,7,4};
    int tab[] = {1,3,5};
    int nbResultats = 0;

    int *tabNbPairs = filtrerPairs(tab, 3, &nbResultats);

    if (tabNbPairs == NULL)
        fprintf(stdout, "Aucun nbre pair ou erreur: pointeur NULL\n");
    else
    {
        printf("Le tableau contient les nbrs pairs suivants : ");
            // affichage tab
        for (int i = 0; i < nbResultats; i++)
            printf("%d ", *(tabNbPairs + i));
        putc('\n', stdout);

    }

    return EXIT_SUCCESS;
}