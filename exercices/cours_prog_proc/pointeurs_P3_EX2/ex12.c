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


void inverserTableau(int *tab, int taille)
{
    assert(tab != NULL && taille > 0);

    int *debut = tab, *fin = tab + taille - 1;
    int temp;

    int i = 0;

    while(debut < fin && i < taille)
            {
                temp = *debut;
                *debut = *fin;
                *fin = temp;

                // IA simplifiable sans i via
                // debut++; fin--;
                i++;
                debut = tab + i;
                fin = tab + (taille - 1 - i);
            }
}


int main(void)
{
    SetConsoleOutputCP(CP_UTF8);

    int tab[4] = {1,2,3,4};

    afficherTableau(tab, 4);
    inverserTableau(tab, 4);
    afficherTableau(tab, 4);
  

    return 0;
}