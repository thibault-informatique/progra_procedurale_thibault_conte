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

static void askPlayerChoice(int codeLength, int nbOfRemainingTries)
{
    printf("\nCode de %d chiffres - %d tentatives\n", codeLength, nbOfRemainingTries);
    printf("Quel est le bon code? ");
}

void printValuesPositionsCounter(const int *goodPosition, const int *wrongPosition)
{
    assert(goodPosition != NULL && wrongPosition != NULL);

    printf("Bien placés : " GREEN"%d"RESET " | Mal placés : " RED"%d"RESET"\n", *goodPosition, *wrongPosition);
}

// fonction + performante et sécurisée que scanf , via IA pour tests et sécurité
int getUserChoice(unsigned int minValue, unsigned int maxValue)
{
    char buffer[20];
    int userChoice;
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
        isValid = (sscanf_s(buffer, "%d", &userChoice) == 1) &&
                  (userChoice >= (int)minValue)                    &&
                  (userChoice <= (int)maxValue);

        if (!isValid)
            fprintf(stderr, "Format attendu : 1 chiffre compris entre %u et %u\n", minValue, maxValue);
    }
    return userChoice;
}

// transformer un int en n digit dans un tableau de int
bool intToTab(int playerCode[], int number, int nbOfDigit)
{
    assert (playerCode != NULL);

    if(number < 0)
    {
        fprintf(stderr, "Erreur le code ne peut être négatif\n");
        return false;
    }

    if(nbOfDigit <= 0)
    {
        fprintf(stderr, "Erreur le nombre de digit doit valoir au moins 1\n");
        return false;
    }

    // verif taille nbre et attribution valeurs tableau
    // 1) si nbre plus petit que le tableau => remplissage à G par des 0
    for (int i = nbOfDigit - 1; i >=0 ; i--)
    {
        playerCode[i] =  number % 10;
        
        number /= 10;          
    }

     // 2) si nbre plus grand que le tableau (conseil IA)
     // donc nombre pas nul à la fin
    if (number != 0)
    {
        fprintf(stderr, "Erreur code trop grand par rapport au nbre de digit\n");
        return false;           
    }

    return true;
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

// lance le jeu
// retourne vrai si le joueur a gagné, faux s'il a perdu
bool launchGame(int codeLength, int maxTries, int *nbOfTries)
{
    assert(nbOfTries != NULL && maxTries >= 1 && codeLength >= 1);

    int trueCode[codeLength], playerCode[codeLength];

    int remainingTries = maxTries;

    int maxValue = 1;
    for (int i = 0; i < codeLength; i++)
        maxValue *= 10;
    maxValue -= 1; //(pour 4 chiffres: de 0 à 9999 possibilités)

    
#if DEBUG
    printf("Valeur max pour l'utilisateur = %d\n", maxValue);
#endif

    int goodPosition = 0, wrongPosition = 0;
    bool playerWins = false;

    // création du code secret

    genRandomCode(trueCode, codeLength);    

#if DEBUG
    puts("Debug: code aléatoire généré");
    printCode(trueCode, codeLength);
#endif

    // demande au joueur de proposer et trouver le code en x tentatives
    // MAJ des compteurs puis affichage
    // test pour voir si le joueur a gagné avant de reboucler
    do
    {
        askPlayerChoice(codeLength, remainingTries);

        bool distinctsDigits = true;

        // choix joueur doit être adéquat à la longueur du code et à l'unicité des chiffres choisis
        do
        {            
            if(intToTab(playerCode, (int)getUserChoice(0,maxValue),codeLength) == false)
                fprintf(stderr, "Erreur fct intToTab\n");

            distinctsDigits = isDigitDistinctInCode(playerCode, codeLength);

            if(!distinctsDigits)
                printf("Attention le code doit contenir %d chiffres différents, recommencez.\n", codeLength);

        } while (!distinctsDigits);

        (*nbOfTries)++;
        remainingTries--;

        updatePositionsCounters(trueCode, playerCode, codeLength, &goodPosition, &wrongPosition);

        printValuesPositionsCounter(&goodPosition, &wrongPosition);

        playerWins = hasPlayerWin(&goodPosition, codeLength);

    } while (!playerWins && *nbOfTries < maxTries);

    return playerWins;
}

// 1) générer code aléatoirement
// 2) lancer le jeu avec affichage / choix du joueur
// 3) vérifier si le joueur a gagné ou perdu
void classicGame()
{    
    
    int nbOfTries = 0;    
    bool hasPlayerWon;

    puts("\n*** Partie Classique ***\n");

    // jeu
    hasPlayerWon = launchGame(CLASSIC_GAME_CODE_LENGTH, CLASSIC_GAME_MAX_TRIES, &nbOfTries);

    if(hasPlayerWon)
        printf(BOLD"\nFélicitations! Victoire en %d tentative(s)!\n"RESET, nbOfTries);
    else
        puts("Vous avez perdu...\n");
}


void customGame()
{
    int nbOfTries = 0;    
    bool hasPlayerWon;

    // declaration et affichage
    puts("\n*** Partie Personnalisée ***\n");

    puts("Veuillez choisir la longueur du code (4-6)");
    int codeLength = (int)getUserChoice(4,6);

    puts("Veuillez choisir le nombre de tentatives autorisées (5-15)");
    int maxTries = (int)getUserChoice(5,15);

    // jeu
    hasPlayerWon = launchGame(codeLength, maxTries, &nbOfTries);

    if(hasPlayerWon)
        printf(BOLD"\nFélicitations! Victoire en %d tentative(s)!\n"RESET, nbOfTries);
    else
        puts("Vous avez perdu...\n");   
}