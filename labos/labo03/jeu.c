#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "jeu.h"
#include "code.h"
#include "debug.h"

#define STD_MAX_TRIES 10
#define STD_NB_OF_DIGITS 4


static void printGuessCode(int codeLength, int nbOfRemainingTries)
{
    printf("\nCode de %d chiffres - %d tentatives\n", codeLength, nbOfRemainingTries);
    printf("Quel est le bon code ? ");
}

static void printHistoricCommand()
{
     printf("NB: Appuyez sur " GREEN "'h'" RESET " puis " GREEN "ENTER " RESET "pour afficher " BOLD "l'historique." RESET "\n\n" );
}

/*** AFFICHAGE ***/ 

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

void printValuesPositionsCounter(const int *goodPosition, const int *wrongPosition)
{
    assert(goodPosition != NULL && wrongPosition != NULL);

    printf("Bien placés : " GREEN"%d"RESET " | Mal placés : " RED"%d"RESET"\n", *goodPosition, *wrongPosition);
}

void printResultGame(bool victory, int nbOfTries)
{
      if(victory)
        printf(BOLD"\nFélicitations! Victoire en %d tentative(s)!\n"RESET, nbOfTries);
    else
        puts("\n\nVous avez perdu...\n");
}

// appel fct système pour effacer le contenu de la console
// utile ici pour masquer le code entré par le joueur
void clearScreen()
{
    #ifdef _WIN32
        system("cls");
    #else 
        system("clear");
    #endif
}

/*** MECANIQUES DE JEU ***/

// lance le jeu
// retourne vrai si le joueur a gagné, faux s'il a perdu
// 1) générer code soit aléatoirement soit via saisie autre joueur
// 2) lancer le jeu avec affichage / choix du joueur
// 3) permettre au joueur d'afficher l'historique en pressant la touche 'h' puis enter
// 4) vérifier si le joueur a gagné ou perdu
// 5) sinon boucler
bool launchGame(int codeLength, int maxTries, int *nbOfTries, bool gameAgainstHuman)
{
    assert(nbOfTries != NULL && maxTries >= 1 && codeLength >= 1);

    // declaration
    int trueCode[codeLength], tPlayerCode[codeLength];
    int historyCode[maxTries][codeLength];
    int remainingTries = maxTries;
    int maxValue = getCodeMaxValue(codeLength);
    int goodPosition = 0, wrongPosition = 0;
    bool playerWins = false;
    
#if DEBUG
    printf("Valeur max pour l'utilisateur = %d\n", maxValue);
#endif

    // 1) création du code secret
    if(gameAgainstHuman)
    {
        genHumanCode(trueCode, codeLength);
        clearScreen();
        puts("Le code a été choisi, à son adversaire de le deviner");
    }
    else
        genRandomCode(trueCode, codeLength);    

#if DEBUG
    puts("Debug: code aléatoire généré");
    printCode(trueCode, codeLength);
#endif

    // 2) Lancer le jeu
    // demande au joueur de proposer et trouver le code en x tentatives
    // MAJ des compteurs puis affichage
    // test pour voir si le joueur a gagné avant de reboucler
    do
    {
        printGuessCode(codeLength, remainingTries);

        bool distinctsDigits = false;

        // choix joueur doit être adéquat à la longueur du code et à l'unicité des chiffres choisis
        // option: 'h' pour afficher l'historique des codes entrés
        do
        {    
            int dPlayerCode = 0;

           // cas 1 : historique demandé via touche 'h' + enter 
            if (getUserChoiceOrCommand(0,maxValue, 'h', &dPlayerCode))
            {
                if(*nbOfTries > 0)
                {
                    printHistoryCode(*nbOfTries, codeLength, historyCode);
                    printGuessCode(codeLength, remainingTries);
                }
                else
                    puts("Aucun code dans l'historique");
                continue; // relancer la saisie utilisateur
            }
            
            // cas 2 : nombre saisi
            
            if(intToTab(tPlayerCode, dPlayerCode, codeLength) == false)
            {
                fprintf(stderr, "Erreur fct intToTab\n");
                exit(EXIT_FAILURE);
            }

            distinctsDigits = isDigitDistinctInCode(tPlayerCode, codeLength);

            if(!distinctsDigits)
                printf("Attention le code doit contenir %d chiffres différents, recommencez.\n", codeLength);              

        } while (!distinctsDigits);

        // on stocke le dernier code essayé par le joueur dans le tableau historique
        // via IA pour ne pas devoir réécrire une fonction qui copie un tab dans un autre
        // memcpy = "copie moi ces N octets de là vers ici"
        memcpy(historyCode[*nbOfTries], tPlayerCode, codeLength * sizeof(int));

        (*nbOfTries)++;
        remainingTries--;

        updatePositionsCounters(trueCode, tPlayerCode, codeLength, &goodPosition, &wrongPosition);

        printValuesPositionsCounter(&goodPosition, &wrongPosition);

        // 4) verif victoire ou défaite? 
        playerWins = hasPlayerWin(&goodPosition, codeLength);

    } while (!playerWins && *nbOfTries < maxTries);

    return playerWins;
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
                  (userChoice >= (int)minValue)              &&
                  (userChoice <= (int)maxValue);

        if (!isValid)
            fprintf(stderr, "Format attendu : 1 chiffre compris entre %u et %u\n", minValue, maxValue);
    }
    return userChoice;
}

// amélioration de getUserChoice() et qui permet de retourner true si une commande est passée en premier char de la saisie user
// retourne false si un nombre est renseigné (accesible via para *choice)
bool getUserChoiceOrCommand(unsigned int minValue, unsigned int maxValue, char commandChar, int *choice)
{
    char buffer[20];
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

        // etape 3 : déterminer si encodage user d'une commande ou d'un nbre
        // si commande on retourne vrai sans l'interpréter
        if (buffer[0] == commandChar && buffer[1] == '\n')
            return true;

        // sinon , on gère et modifie le pointeur afin qu'il contienne un nbre
        isValid = (sscanf_s(buffer, "%d", choice) == 1) &&
                  (*choice >= (int)minValue)             &&
                  (*choice <= (int)maxValue);

        if (!isValid)
            fprintf(stderr, "Format attendu : 1 chiffre compris entre %u et %u\n", minValue, maxValue);
    }
    return false;
}

// le joueur gagne s'il trouve tous les chiffres du code au bon endroit
bool hasPlayerWin( const int * goodPosition, int codeLength)
{
    return *goodPosition == codeLength;
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

/*** DIFFERENTS TYPES DE JEU ***/

void classicGame()
{    
    
    int nbOfTries = 0;    
    bool hasPlayerWon;

    puts("\n*** Partie Classique ***\n");
    printHistoricCommand();

    // jeu
    hasPlayerWon = launchGame(STD_NB_OF_DIGITS, STD_MAX_TRIES, &nbOfTries, false);

    printResultGame(hasPlayerWon, nbOfTries);
  
}

void customGame()
{
    int nbOfTries = 0;    
    bool hasPlayerWon;

    // declaration et affichage
    puts("\n*** Partie Personnalisée ***\n");
    printHistoricCommand();

    puts("Veuillez choisir la longueur du code (4-6)");
    int codeLength = (int)getUserChoice(4,6);

    puts("Veuillez choisir le nombre de tentatives autorisées (5-15)");
    int maxTries = (int)getUserChoice(5,15);

    // jeu
    hasPlayerWon = launchGame(codeLength, maxTries, &nbOfTries, false);

   printResultGame(hasPlayerWon, nbOfTries);
}

void gameAgainstHuman()
{
    int nbOfTries = 0;    
    bool hasPlayerWon;

    // declaration et affichage
    puts("\n*** Mode 2 joueurs ***\n");
    printHistoricCommand();

    // jeu
    hasPlayerWon = launchGame(STD_NB_OF_DIGITS, STD_MAX_TRIES, &nbOfTries, true);

    printResultGame(hasPlayerWon, nbOfTries);
}