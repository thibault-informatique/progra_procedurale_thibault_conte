#include <stdio.h>

int statistiques(const int *tab, int taille, int *minimum, int *maximum, double *moyenne)
{
    int total = 0;

    *minimum = tab[0];
    *maximum = tab[0];

    *moyenne = 0;

    for (int i = 0; i < taille; i++)
    {
        if (tab[i] < *minimum)
            *minimum = tab[i];

        if(tab[i] > *maximum)
            *maximum = tab[i];

        total += tab[i]; 
    }

    // tab vide si tous les élements valent 0
    if(total == 0)
        return 0;

    *moyenne = (double) total / (double) taille;
    
    return 1;
}

void printTab(int *tab, int taille)
{
    int i;

    for (i = 0; i < taille - 1 ; i++)
        printf("%d, ", *(tab + i));

    printf("%d\n", *(tab + i));
}

int main(void)
{
    int tab[4] = {8,3,11,6};

    int minimum = 0, maximum = 0;

    double moyenne = 0;

    printTab(tab, 4);

    if(statistiques(tab, 4, &minimum, &maximum, &moyenne) == 0)
        fprintf(stderr, "Tableau vide");
    else
    {
        printf("min = %d, max = %d, moyenne = %.2lf\n", minimum, maximum, moyenne);
    }

    return 0;
}