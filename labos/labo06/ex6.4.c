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

        /*
            VERSION IA plus efficace : lecture par buffer de 4096 octets

            char buffer[4096];
            size_t n;
            while ((n = fread(buffer, 1, sizeof buffer, src)) > 0)
            {
                if (fwrite(buffer, 1, n, dst) != n)
                {
                    perror("fwrite");
                    fclose(src); fclose(dst);
                    return EXIT_FAILURE;
                }
            }
        */

        /*
            POINTS D'ATTENTION
            fread(buffer, 1, 4096, src) renvoie le nombre d'octets lus (avec size = 1, n = octets, 
            pas nombre de blocs) : 4096, sauf au dernier passage où il renvoie le reste (ex. 80 pour 
            un fichier de 4096+80 octets) ;
            au passage suivant, la fin de fichier est atteinte → fread renvoie 0 → la condition > 0 
            est fausse → la boucle s'arrête.
            Donc la boucle tourne ceil(taille_fichier / 4096) fois, et s'arrête proprement à EOF. 
            Pour rapport.txt (~80 octets) : 1ᵉʳ passage n = 80 (tout le fichier, oui), 2ᵉ passage n = 0 → arrêt. 
            C'est exactement le comportement voulu.

            Piège à éviter : écrire fread(buffer, sizeof buffer, 1, src) (size et nmemb inversés) — 
            là fread renvoie 0 ou 1 (nombre de blocs), et un dernier bloc partiel serait compté 0 → tronqué. 
            Avec fread(buffer, 1, sizeof buffer, src) + > 0, aucun octet n'est perdu, 
            d'où le fwrite(buffer, 1, n, dst) avec n et non sizeof buffer.
        */
       
        // 6) on ferme les FILE * ouverts
        fclose(src);
        fclose(dest);
    }
    else
        fprintf(stdout, " 2 paramètres attendus : [fichier_source] [fichier_destination]\n");

    return 0;
}