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

static void askPlayerChoice(int codeLength, int nbOfTries)
{
    printf("\nCode de %d chiffres - %d tentatives\n", codeLength, nbOfTries);
    printf("Quel est le bon code? ");
}

void printValuesPositionsCounter(const int *goodPosition, const int *wrongPosition)
{
    assert(goodPosition != NULL && wrongPosition != NULL);

    printf("Bien placés : " GREEN"%d"RESET " | Mal placés : " RED"%d"RESET"\n", *goodPosition, *wrongPosition);
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

void updatePositionsCounters(const int trueCode[], const int playerCode[], int codeLength, int * goodPosition, int *wrongPosition)
{
    assert(trueCode != NULL && playerCode != NULL && goodPosition != NULL && wrongPosition != NULL && codeLength > 0);

    // init / reinit compteurs
    *goodPosition = 0;
    *wrongPosition = 0;

    // on compare les 2 tableaux
    // si ça match, on vérifie si les indexs sont les mêmes ou non
    for (int i = 0; i < codeLength; i++)
        for(int j = 0; j < codeLength; j++)
            {
                if (trueCode[i] == playerCode[j])
                {
                    if( i == j)
                    {
                        // erreur car problème de priorité sans les ()
                        (*goodPosition)++;
                        break;
                    }
                    else
                    {
                        (*wrongPosition)++;
                        break;
                    }
                }
            }
}

// le joueur gagne s'il trouve tous les chiffres du code au bon endroit
bool hasPlayerWin( const int * goodPosition, int codeLength)
{
    return *goodPosition == codeLength;
}

// 1) générer code aléatoirement
// 2) lancer le jeu avec affichage / choix du joueur
// 3) vérifier si le joueur a gagné ou perdu
// 4) boucler jusqu'à atteindre 1 des 2 résultats 
void classicGame()
{    
    // declaration

    int trueCode[CLASSIC_GAME_CODE_LENGTH] = {0};
    int *playerCode = NULL;
    unsigned short int nbOfTries = CLASSIC_GAME_MAX_TRIES;    
    // contient le nbre de chiffres trouvés et si 
    // à la bonne ou mauvaise place
    int goodPosition = 0, wrongPosition = 0;
    bool playerWins = false;

    // création du code secret

    genRandomCode(trueCode, CLASSIC_GAME_CODE_LENGTH);
    
    puts("\n*** Partie Classique ***\n");

#if DEBUG
    printCode(trueCode, CLASSIC_GAME_CODE_LENGTH);
#endif

    // demande au joueur de proposer et trouver le code en x tentatives
    // MAJ des compteurs puis affichage
    // test pour voir si le joueur a gagné avant de reboucler
    do
    {
        askPlayerChoice(CLASSIC_GAME_CODE_LENGTH, nbOfTries);

        bool distinctsDigits = true;

        do
        {
            playerCode = intToTab(getUserChoice(0,9999),CLASSIC_GAME_CODE_LENGTH);

            distinctsDigits = isDigitDistinctInCode(playerCode, CLASSIC_GAME_CODE_LENGTH);

            if(!distinctsDigits)
                puts("Attention le code doit contenir 4 chiffres différents, recommencez.");

        } while (!distinctsDigits);

        if (playerCode == NULL)
            exit(EXIT_FAILURE);

        nbOfTries--;

        updatePositionsCounters(trueCode, playerCode, CLASSIC_GAME_CODE_LENGTH, &goodPosition, &wrongPosition);

        printValuesPositionsCounter(&goodPosition, &wrongPosition);

        playerWins = hasPlayerWin(&goodPosition, CLASSIC_GAME_CODE_LENGTH);
        free(playerCode);

    } while (!playerWins && nbOfTries > 0);

    if(playerWins)
        printf(BOLD"\nFélicitations! Victoire en %d tentative(s)!\n"RESET, CLASSIC_GAME_MAX_TRIES - nbOfTries);
    else
        puts("Vous avez perdu...\n");
}