#include <stdio.h>
#include <stdlib.h>

unsigned short int getUserChoice(unsigned short int minValue, unsigned short int maxValue)
{
    char buffer[20];
    unsigned short int userChoice;
    bool isValid = false;

    while (!isValid)
    {
        // etape 1 : lecture
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            // flux ferme (Ctrl+D, redirection) : on sort, sinon boucle infinie
            fprintf(stderr, "Fin de flux d'entree\n");
            exit(EXIT_FAILURE);
        }

        // etape 2 : purge si la saisie depassait le buffer
        if (strchr(buffer, '\n') == NULL)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

        // etape 3 : validation
        isValid = (sscanf_s(buffer, "%hu", &userChoice) == 1) &&
                  (userChoice >= minValue)                    &&
                  (userChoice <= maxValue);

        if (!isValid)
            fprintf(stderr, "Format attendu : 1 chiffre compris entre %hu et %hu\n", minValue, maxValue);
    }
    return userChoice;
}

int main(void)
{
    int nb = 0;
    int taille = 0;

    int *tab= (int) malloc(taille * sizeof(int));


    free(tab);
    tab = NULL;
}