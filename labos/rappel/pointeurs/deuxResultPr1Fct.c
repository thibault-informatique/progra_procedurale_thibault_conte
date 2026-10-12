#include <stdio.h>

int diviser(int a, int b, int *quotient, int *reste)
{
    if(b == 0)
        return 0;
    
    *quotient = a / b;

    *reste = a % b;

    return 1;
}

int main(void)
{
    // bonne pratique d'initialiser à -1 car dans ce cas de figure ne sera pas un résultat valable ou problèmatique
    int quotient1 = -1, reste = -1;

    printf("Quotient et reste valent %d et %d avant le calcul.\n", quotient1, reste);

    if (diviser(17,5, &quotient1, &reste) == 0)
    {
        fprintf(stderr, "Erreur division par 0\n");
    }
    else
    {
        printf("17/5 | quotient = %d, reste = %d\n", quotient1, reste);
    }

    return 0;
}