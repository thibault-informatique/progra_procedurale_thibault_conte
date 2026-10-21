#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "jeu.h"
#include "code.h"
#include "debug.h"

#define CLASSIC_GAME_MAX_TRIES 10
#define CLASSIC_GAME_CODE_LENGTH 4

#define DEBUG 1

void printMenu()
{
    puts("\n");
    puts("Bienvenue dans \"CODE BREAKER\"\n");
    puts("[1] Partie classique\n");
    puts("[2] Partie personnalisée\n");   
    puts("[3] Mode 2 joueurs\n"); 
#if DEBUG
    puts("[4] tests/DEBUG\n");
#endif
    puts("0. Quitter le programme");
    printf("\nQuel est votre choix? ");
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

// transformer un int de n digit et retourner un pointeur sur int tab[n]
int* intToTab(int number, int nbOfDigit)
{
    if(number < 0)
    {
        fprintf(stderr, "Erreur le code ne peut être négatif\n");
        return NULL;
    }

    if(nbOfDigit <= 0)
    {
        fprintf(stderr, "Erreur le nombre de digit doit valoir au moins 1\n");
        return NULL;
    }

    int *result = (int*) calloc (nbOfDigit, sizeof(int));

    if(result == NULL)
    {
       fprintf(stderr, "Erreur allocation de mémoire pour stocker le code dans un tableau\n");
        return NULL; 
    }

    // verif taille nbre et attribution valeurs tableau
    // 1) si nbre plus petit que le tableau => remplissage à G par des 0
    for (int i = nbOfDigit - 1; i >=0 ; i--)
    {
        result[i] =  number % 10;
        
        number /= 10;          
    }

     // 2) si nbre plus grand que le tableau (conseil IA)
    if (number != 0)
    {
        fprintf(stderr, "Erreur code trop grand par rapport au nbre de digit\n");
        free(result);
        return NULL;           
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