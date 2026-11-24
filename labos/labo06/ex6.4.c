#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <windows.h>

// ecrire une commande de copie de fichiers en binaire (permet de copier des images,...)
// refuser de copier si la destination existe déjà

int main(int argc, char *argv[])
{
    SetConsoleOutputCP(CP_UTF8);

    if (argc == 3)
    {
        char desti_file[128] = {'\0'};
        char source_file[128] = {'\0'};
        int tempChar = '\0';
        

        // 1) on récupère le nom du fichier source
        strncpy(source_file, argv[1], 127);

        // 2) idem pour la destination
        strncpy(desti_file, argv[2], 127);

        // 3) si le fichier destination est lisible "r" => erreur car il existe déjà
        FILE *existe = fopen(desti_file, "rb");
        if(existe != NULL)
        {
            fprintf(stdout, "Erreur la destination existe déjà\n");
            fclose(existe);
            return EXIT_FAILURE;
        }

        // 4) on ouvre le fichier source et on crée / ouvre le fichier destination
        FILE *src = fopen(source_file, "rb");
        if(src == NULL)
        {
            perror("fopen source_file");
            return EXIT_FAILURE;
        }

        FILE *dest = fopen(desti_file, "wb");
         if(dest == NULL)
        {
            perror("fopen desti_file");
            fclose(src);
            return EXIT_FAILURE;
        }

        // 5) on copie de source vers destination jusqu'à la fin du fichier

        while ((tempChar = getc(src)) != EOF)
            fputc(tempChar, dest);

        // 6) on ferme les FILE * ouverts
        fclose(src);
        fclose(dest);
    }
    else
        fprintf(stdout, " 2 paramètres attendus : [fichier_source] [fichier_destination]\n");

    return 0;
}