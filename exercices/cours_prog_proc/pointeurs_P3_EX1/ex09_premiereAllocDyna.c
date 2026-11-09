#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NB 100

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

bool fillTab(int *tab, int tabSize)
{
    if (tab == NULL)
    {
        fprintf(stderr, "Erreur dans fillTab() (pointeur NULL) \n");
        exit(EXIT_FAILURE);
    }

    if (tabSize <= 0)
        return false;

    for (int i = 0; i < tabSize; i++)
        tab[i] = i + 1;

    return true;
}

bool addTabValue(int *tab, int tabSize, int * result)
{
    if (tab == NULL || result == NULL)       
    {
        fprintf(stderr, "Erreur dansaddTabvalue() (pointeur NULL) \n");
        exit(EXIT_FAILURE);
    }
  
    if (tabSize <= 0)
        return false;

    *result = 0;

    for (int i = 0; i < tabSize; i++)
        *result += tab[i];

    return true;
}

int main(void)
{
    int total = 0;

    printf("Choisir unn nombre entre 1 et 100 (taille tableau): ");
    int tabSize = getUserChoice(1, MAX_NB);

    int *tab = malloc(tabSize * sizeof(int));
    
    // allocation dynamique + gestion erreur allocation : ptr NULL
    if(tab == NULL)
        return EXIT_FAILURE;

    // on remplit et on prévient d'une éventuelle erreur de taille de tab
    if(!fillTab(tab, tabSize))
        fprintf(stderr, "Erreur taille tab renseigné\n");
       

    if(!addTabValue(tab, tabSize, &total))
        fprintf(stderr, "Erreur taille tab renseigné\n");
    else
        printf("Somme valeur tableau = %d\n", total);

    free(tab);
    tab = NULL;
}