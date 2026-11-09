#include <stdio.h>

int main(void)
{
    int nbre = 42;
    int *pNbre = &nbre;

    printf("Valeur nbre: %d\n", nbre);
    printf("Valeur adresse nbre: %p\n", (void*)&nbre);
    printf("Valeur adresse contenue par le pointeur: %p\n", (void*)pNbre);
    printf("Valeur pointée: %d\n", *pNbre);

    return 0;
}