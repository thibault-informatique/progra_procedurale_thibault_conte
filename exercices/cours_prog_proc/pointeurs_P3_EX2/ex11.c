#include <stdio.h>
#include <windows.h>
#include <assert.h>

void afficherTableau(const int *tab, int taille)
{
    assert (tab != NULL && taille > 0);

    printf("Endroit : ");
    for (int i = 0; i < taille ; i++)
    {
        printf("%d ", *(tab + i));
    }
    putc('\n', stdout);
}

void afficherALEnvers(const int *tab, int taille)
{
    assert (tab != NULL && taille > 0);
    
    printf("Envers  : ");
    for (int i = taille - 1; i >= 0 ; i--)
    {
        printf("%d ", *(tab + i));
    }
    putc('\n', stdout);
}


int main(void)
{
    SetConsoleOutputCP(CP_UTF8);

    int tab[5] = {3,1,4,1,5};

    afficherTableau(tab, 5);
    afficherALEnvers(tab, 5);

    return 0;
}