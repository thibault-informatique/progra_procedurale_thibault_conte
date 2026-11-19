#include <stdio.h>
#include <stdlib.h>

int *copierTableau(const int *src, int n) // NULL si erreur
{
    if(src == NULL || n <= 0)
        return NULL;

    // création nouveau tableau
    int *newTab = (int*) malloc (n * sizeof(*newTab));

    if(newTab == NULL)
        return NULL;

    //copie des éléments du premier tableau dans le 2e
    for (int i = 0; i < n ; i++)
        *(newTab + i) = *(src + i);

    return newTab;    
}


int main (void)
{
    int tab1[5] = { 1,3,5,7,9};

  

    puts("Tab 1 = ");

    // affichage tab 1
    for (int i = 0; i < 5; i++)
        printf("%d ", *(tab1 + i));
    putc('\n', stdout);

    int *tab2 = copierTableau(tab1, 5);

    puts("Tab 2 = ");

     // affichage tab 1
    for (int i = 0; i < 5; i++)
        printf("%d ", *(tab2 + i));
    putc('\n', stdout);

    free(tab2);
    tab2 = NULL;
    
    return 0;
}