#include <stdio.h>

int main(void)
{
    // declaration
    int entier = 42;
    double reel = 3.14f;
    char lettre = 'C';

    int *p = &entier;

    printf("entier : valeur = %d   adresse = %p    taille = %zu octets\n", entier, (void*)&entier, sizeof(entier));
    printf("reel :   valeur = %.2lf adresse = %p    taille = %lld octets\n", reel, (void*)&reel, sizeof(reel));
    printf("lettre : valeur = %c    adresse = %p    taille = %lld octets\n", lettre, (void*)&lettre, sizeof(lettre));
    printf("p contient : %p -> *p = %d\n", (void*)p, *p);
    
    return 0;
}