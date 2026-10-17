/* https://labex.io/fr/labs/c-parsing-command-line-arguments-in-c-301496
Exigences
Le programme n'a besoin que d'afficher les arguments de ligne de commande commençant par --. 
Les arguments ne répondant pas aux exigences de format peuvent être ignorés. 
Par exemple, des arguments comme -a 123 n'ont pas besoin d'être affichés ou traités. 
Si il n'y a pas de valeur correspondante après l'argument, passez simplement outre sans l'afficher ou le traiter.
Chaque ligne de la sortie du programme est composée de deux parties : le nom du paramètre et la valeur, séparées par deux-points.
Le nom et la valeur du paramètre du programme peuvent être n'importe quelle combinaison de chiffres et de lettres.*/

/* Exemple
$ cd ~/project/
$ gcc cmd.c -o cmd
$./cmd --arg1 1 --arg2 demo --arg9 labex
arg1:1
arg2:demo
arg9:labex
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void getTwoFirstCharArgv(const char *argv, char *result, size_t resultSize)
{
    assert(argv != NULL && result != NULL);

    // on met dans result uniquement les 2 premiers caractères de argv
    if(snprintf(result, resultSize, "%.2s", argv) >= (int)resultSize)
        fprintf(stderr, "Erreur snprintf\n");
}

int main(int argc, char* argv[])
{
    printf("%d arguments reçu(s) à l'appel de %s\n", argc - 1, argv[0]);

    // on appelle les arguments reçus un par un jusqu'au dernier
    for (int i = 1; i < argc; i++)
        {
            char tempArg[3] = "\0";
            int nbOfTrueArg = 0;

            // on met dans tempArg uniquement les 2 premiers caractères
            getTwoFirstCharArgv(argv[i], tempArg, sizeof(tempArg));

            // s'ils commencent par -- on affiche les paramètres sans les --
            if(strcmp(tempArg, "--") == 0)
            {
                ++nbOfTrueArg;               

                /*  RACCOURCI
                char *p = argv[i];
                while (*p) {
                    char c = *p++;
                } 
                */

                /*
                    on affiche ce qu'il y a après les -- (index commence à 2)
                    1) on indique le nom renseigné après les --
                    2) s'il y a une valeur ( argument d'après sans --), on affiche la valeur en précédant de ':'
                */

                 // on commence après le --
                for(int j = 2; argv[i][j] != '\0'; j++)
                {                                               
                    printf("%c", argv[i][j]);
                }

                // si il reste au moins un arg à lire et que c'est une valeur de l'arg précédent (!= "--")
                if(i + 1 < argc)
                {
                    char tempValue[3] = "\0";

                    getTwoFirstCharArgv(argv[i+1], tempValue, sizeof(tempValue));

                    if(strcmp(tempValue, "--") != 0)
                    {
                        i++;
                        putc(':', stdout);
                        for(int j = 0; argv[i][j] != '\0'; j++)
                            printf("%c", argv[i][j]);
                    }        
                }
                putc('\n', stdout);
            }
        }    
    return 0;
}