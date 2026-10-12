#include <stdio.h>

void doublerTableau(int *tab, int taille)
{
    for (int i = 0; i < taille; i++)
        *(tab + i) *= 2;
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
    int tab[4] = {2,4,6,8};

    printTab(tab, 4);

    doublerTableau(tab, 4);

    printTab(tab, 4);

    return 0;

}