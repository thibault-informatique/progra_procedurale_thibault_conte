#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main(int argc, char *argv[])
{
    SetConsoleOutputCP(CP_UTF8);

    if (argc == 2)
    {
        int i = 0;
        int numLigne = 0;

        char file[128] = {'\0'};
        char ligne[256] = {'\0'};
        

        // 1) on récupère le nom du fichier
        while (argv[1][i] != '\0')
        {
            file[i] = argv[1][i];
            i++;
        }

        file[i] = '\0';

        // 2) on l'ouvre
        FILE *f = fopen(file, "r");
        if(f == NULL)
        {
            perror("Erreur ouverture file\n");
            exit(EXIT_FAILURE);
        }

        // 3) on lit ligne par ligne
        while (fgets(ligne, sizeof(ligne), f) != NULL)
        {
            // permet d'éviter un saut de ligne indésirable
            // on contrôle le saut de ligne souhaité dans le fprintf
            ligne[strcspn(ligne, "\n")] = '\0';
            fprintf(stdout, "%3d | %s\n", numLigne++, ligne);
        }
    }
    else
        fprintf(stdout, "Paramètre attendu : nom d'un seul fichier\n");
    
    return EXIT_SUCCESS;
}