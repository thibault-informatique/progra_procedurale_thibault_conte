#include <stdio.h>
#include <windows.h>
#include <assert.h>

int *rechercher(int *tab, int taille, int valeur)
{
    if(tab == NULL || taille <= 0)
        return NULL;
    
    for(int i = 0; i < taille; i++)
        if (*(tab + i) == valeur)
            return tab +i;
    
    return NULL;
}

int main(void)
{
    int tab[4] = {7,3,9,3};

    int *resultat = NULL;

    for (int i = 0; i < 4; i++)
    {
        resultat = rechercher(tab, 4, tab[i]);

        if(resultat != NULL)
            printf(" %d se trouve à l'indice %td dans le tableau\n", tab[i], resultat - tab);
        else
            printf("Valeur non trouvée ou erreur fct rechercher\n");
    }
    return 0;
}