#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n = -1;
    int result = 0;

    while(n < 1 || n > 100)
    {
        puts("Choisir un entier entre 1 et 100");
        scanf("%d", &n);
    }

    int *tab = (int *) malloc (n * sizeof(*tab));

    // init
    for (int i = 0; i < n; i++)
        *(tab + i) = 0;

    // affichage tab
    for (int i = 0; i < n; i++)
        printf("%d ", *(tab + i));
    putc('\n', stdout);

    // chaque case vaut i² ; i++
    for (int i = 0; i < n; i++)
        *(tab + i) = i * i;

    for (int i = 0; i < n; i++)
        printf("%d ", *(tab + i));
    putc('\n', stdout);

    // somme du tableau
    for (int i = 0; i < n; i++)
        result += *(tab + i);
    
    printf("Le résultat vaut : %d\n", result);


    return 0;
}