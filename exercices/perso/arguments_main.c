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

int main(int argc, char* argv[])
{
    printf("%d arguments reçu(s) à l'appel de %s\n", argc - 1, argv[0]);

    // on appelle les arguments reçus un par un jusqu'au dernier
    for (int i = 1; i < argc; i++)
        {
            char temp[3] = "\0";
            int nbOfTrueArg = 0;

            // on met dans temp uniquement les 2 premiers caractères
            if(snprintf(temp, sizeof(temp), "%.2s", argv[i]) >= (int)sizeof(temp))
                fprintf(stderr, "Erreur snprintf\n");

            // s'ils commencent par -- on affiche les paramètres sans les --
            if(strcmp(temp, "--") == 0)
            {
                ++nbOfTrueArg;               

                /*  RACCOURCI
                char *p = argv[i];
                while (*p) {
                    char c = *p++;
                } 
                */

                 // on commence après le --
                for(int j = 2; argv[i][j] != '\0'; j++)
                {                                               
                    printf("%c", argv[i][j]);
                }
                putc('\n', stdout);
            }
        }
    
    return 0;
}