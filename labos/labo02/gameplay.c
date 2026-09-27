#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> // fct strchr

#include "gameplay.h"
#include "display.h"
#include "compat.h"

void initBoard(bool board[][COLUMN_NB])
{
    assert(board != NULL);

    for(unsigned short int row = 0; row < ROW_NB; row++)
        for (unsigned short int col = 0; col < COLUMN_NB; col++)
            board[row][col] = false;
}

// fonction + performante et sécurisée que scanf , via IA pour tests et sécurité
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

// placement aléatoire de bombes mode contre l'ordinateur ; nombre choisi par le joueur
void setRandomBombInDataBoard(bool dataBoard[][COLUMN_NB])
{  
    assert(dataBoard != NULL);

    printf("Combien de mines voulez-vous placer dans le jeu [1-%d]?\n", MAX_BOMBS);
    unsigned short int nbOfBombs = getUserChoice(1,MAX_BOMBS);

    // conseil IA: vérifier que le nbre de bombes ne dépassera jamais le nombre de cases totales 
    // sinon boucle for infinie
    assert(nbOfBombs <= ROW_NB * COLUMN_NB);

    unsigned short int row = 0;
    unsigned short int column = 0;

    for(unsigned short int i = 0; i < nbOfBombs; i++)
    {    
       row = (unsigned short int) rand() % ROW_NB;
       column = (unsigned short int) rand() % COLUMN_NB;
       // si bombe pas présente sur la case choisie aléatoirement, on la place
       if (!dataBoard[row][column])
            dataBoard[row][column] = true;
        // si on n'a pas pu placer de bombe car déjà présente sur la case, on décrémente de 1
        // pour "recommencer un tour de boucle"
        else
            i--;            
    }
}

// placement de bombes via le joueur 2 pour le joueur 1 (mode contre humain)
void setManualBombInDataBoard(bool dataBoard[][COLUMN_NB])
{
    assert (dataBoard != NULL);

    unsigned short int nbOfBombs = 0;
    unsigned short int row = 0;
    unsigned short int column = 0;

    printf("Joueur 1, choisis le nombre de bombe que Joueur 2 va placer [1-%d]:", MAX_BOMBS);
    nbOfBombs = getUserChoice(1, MAX_BOMBS);

    // placement des bombes par joueur 2
    for (unsigned short int i = 0; i < nbOfBombs; i++)
    {
       printDataBoard(dataBoard);
       printf("\n%hu bombe(s) restante(s)\n ", nbOfBombs - i);

       printf("Choix de ligne: ");
       row = getUserChoice(1,ROW_NB);
       printf("Choix de colonne: ");
       column = getUserChoice(1, COLUMN_NB);

       // on décrémente les valeurs fournies pour correspondre aux index débutant à 0
       --row, --column;
       // si bombe pas présente sur la case choisie aléatoirement, on la place
       if (!dataBoard[row][column])
       {
            dataBoard[row][column] = true;
            puts("Bombe amorcée");
       }
        // si on n'a pas pu placer de bombe car déjà présente sur la case, on décrémente de 1
        // pour "recommencer un tour de boucle" et on informe Joueur 2
        else
        {
            fprintf(stderr, "La bombe n'a pas pu être placée car il y a déjà une bombe sur la case [%d][%d]\n", row + 1, column + 1);
            puts("Veuillez choisir de nouvelles coordonnées");
            i--; 
        }  
    }

    printf("%hu bombes ont été enterrées avec succès !\n\n", nbOfBombs);
}

// fct qui vérifie si la case était déjà visible par le joueur
static bool wasCellAlreadyVisible(const bool gameBoard[][COLUMN_NB], unsigned short int row, unsigned short int column)
{
    assert(gameBoard != NULL);
    return gameBoard[row][column];
}

static bool hasPlayerWon(const bool gameBoard[][COLUMN_NB], const bool dataBoard[][COLUMN_NB])
{  
    assert (gameBoard != NULL && dataBoard != NULL);

    for(unsigned short int row = 0; row < ROW_NB; row++)
        for (unsigned short int col = 0; col < COLUMN_NB; col++)
        {
            // le joueur n'a pas gagné si au moins une cellule qui n'est pas une bombe n'est pas révélée
            if(gameBoard[row][col] == false && dataBoard[row][col] == false)
            {
                return false;
            }
        }
    return true;
}

// les préparatifs finis, le joueur peut enfin jouer
static void letsPlay(bool gameBoard[][COLUMN_NB], const bool dataBoard[][COLUMN_NB])
{
    assert (gameBoard != NULL && dataBoard != NULL);

    bool isGameActive;
    unsigned short int chosenRow = 0;
    unsigned short int chosenColumn = 0;

    printGameBoard(gameBoard, dataBoard);

    isGameActive = true;

    while(isGameActive)
    {
       do
       {
            puts("Veuillez choisir les coordonnées d'une case qui n'a pas encore été retournée '?'");
            // choix ligne puis colonne par le joueur
            printf("Choisir une ligne : ");
            chosenRow = getUserChoice(1,ROW_NB);
            printf("Choisir une colonne : ");
            chosenColumn = getUserChoice(1,COLUMN_NB);

            // on décrémente pour correspondre aux index du tableau 2D
            --chosenRow;
            --chosenColumn;
       } while (wasCellAlreadyVisible(gameBoard, chosenRow, chosenColumn));
       // si la ligne était déjà connue, le joueur doit faire une nouvelle sélection de coordonnées
       
        // on rend la case du jeu visible
        gameBoard[chosenRow][chosenColumn] = true;

        putc('\n', stdout);
        printGameBoard(gameBoard, dataBoard);

        // si bombe révélée => perdu
        if (dataBoard[chosenRow][chosenColumn])
        {
            puts("    !!! BOUM !!!");
            puts("   Vous avez perdu.\n");
            isGameActive = false;
        }
       
        // cas victoire
        else if(hasPlayerWon(gameBoard, dataBoard))
        {
            puts("    !!! BRAVO !!!");
            puts("   Vous avez gagné!\n");
            isGameActive = false;
        }       
    }
}

// ***cas joueur contre ordinateur ***

// 1) placement bombes aléatoirement
// 2) jeu en lui-même
void gameAgainstComputer(bool gameBoard[][COLUMN_NB], bool dataBoard[][COLUMN_NB])
{
    assert (gameBoard != NULL && dataBoard != NULL);

    setRandomBombInDataBoard(dataBoard);

#if DEBUG
    printDataBoard(dataBoard);
#endif

    letsPlay(gameBoard, dataBoard);  
}

// ***cas joueur contre joueur***

// 1) placement bombes par un des joueurs
// 2) jeu en lui-même pour l'autre joueur
void gameAgainstHuman(bool gameBoard[][COLUMN_NB], bool dataBoard[][COLUMN_NB])
{
    assert (gameBoard != NULL && dataBoard != NULL);

    setManualBombInDataBoard(dataBoard);
    
#if DEBUG
    printDataBoard(dataBoard);
#endif
    letsPlay(gameBoard, dataBoard);

}