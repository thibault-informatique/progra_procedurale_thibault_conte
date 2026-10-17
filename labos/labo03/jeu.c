#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "jeu.h"

#define CLASSIC_GAME_MAX_TRIES 10
#define CLASSIC_GAME_CODE_LENGTH 4

#define DEBUG 1

void printMenu()
{
    puts("\n");
    puts("Code Breaker\n");
    puts("[1] Partie classique\n");
    puts("[2] Partie personnalisée\n");   
    puts("[3] Mode 2 joueurs\n"); 
    puts("0. Quitter le programme");
}

void printCode(int code[], short int tabLength)
{
    assert(code != NULL && tabLength > 0);

    for(int i = 0; i < tabLength ; i++)
    {
        printf("%d", code[i]);
    }
    putc('\n', stdout);
}

// fonction + performante et sécurisée que scanf , via IA pour tests et sécurité
short int getUserChoice(unsigned short int minValue, unsigned short int maxValue)
{
    char buffer[20];
    short int userChoice;
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

void genRandomCode(int code[], short int tabLength)
{
    assert(code != NULL && tabLength > 0);

    for(int i = 0; i < tabLength ; i++)
    {
        code[i] = rand() % 10;
    }  
}

int* intToTab(const int number, int nbOfDigit)
{
    // verif taille nbre?
    if(number < 0)
    {
        fprintf(stderr, "Erreur le code ne peut être négatif\n");
        return NULL;
    }

    int *result = (int*) calloc (nbOfDigit, sizeof(int));


    assert (result != NULL);

    for (int i = (nbOfDigit - 1); i >= 0; i--)
    {
        if (i == nbOfDigit)
            result[i] = number % 10; 
        else if (i == nbOfDigit - 1)
            result[i] = number % 10 - result[i + 1];
        else if (i == nbOfDigit - 1 -1)
            result[i] = number % 10 - result[i + 1] - result [i + 1 + 1];   
        else
            result[i] = number % 10 - result[i + 1] - result [i + 1 + 1] - result [i + 1 + 1 + 1];                  
    }
    return result;
}

void classicGame()
{    
    int code[CLASSIC_GAME_CODE_LENGTH];
    unsigned short int nbOfTries = CLASSIC_GAME_MAX_TRIES;

    genRandomCode(code, CLASSIC_GAME_CODE_LENGTH);
    
    puts("\n*** Partie Classique ***\n");
#if DEBUG
    printCode(code, CLASSIC_GAME_CODE_LENGTH);
#endif


}