#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Compter les lignes, les mots et les caractères d'un fichier
int main(void)
{
    SetConsoleOutputCP(CP_UTF8);

    int nbLignes = 0;
    int nbMots = 0;
    int nbCaract = 0;
    // nécessaire de savoir si on est dans un mot (sinon double espace compte à tort pour un mot)
    int inWord = 0;


    int caractLu;

    FILE *file = fopen("rapport.txt", "r");

    if(file == NULL)
    {
        perror("fopen");
        return EXIT_FAILURE;
    }

    while ((caractLu = getc(file)) != EOF)
    {
        nbCaract++;
        if(caractLu == '\n')
        {
            nbLignes++;
            inWord = 0;
        }
        else if(caractLu == '\t' || caractLu == ' ')
        {
            inWord = 0;
        }
        else if(inWord == 0)
        {
            nbMots++;
            inWord = 1;
        }
    }

    printf("Lignes     : %4d\n", nbLignes);
    printf("Mots       : %4d\n", nbMots);
    printf("Caractères : %4d\n", nbCaract);

    return EXIT_SUCCESS;
}