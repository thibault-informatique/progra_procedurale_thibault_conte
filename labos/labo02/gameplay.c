#include <stdio.h>
#include "gameplay.h"

void initBoard(bool board[][COLUMN_NB])
{
     for(unsigned short int row = 0; row < ROW_NB; row++)
        for (unsigned short int col = 0; col < COLUMN_NB; col++)
            board[row][col] = false;
}
// affichage menu principal

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


void setBombInDataBoard(bool dataBoard[][COLUMN_NB])
{  
    printf("Combien de mines voulez-vous placer dans le jeu [1-%d]?\n", MAX_BOMBS);
    unsigned short int nbOfBombs = getUserChoice(1,MAX_BOMBS);

    // conseil IA: vérifier que le nbre de bombes ne dépassera jamais le nombre de cases totales 
    // sinon boucle for infinie
    assert(nbOfBombs <= ROW_NB * COLUMN_NB);

    unsigned short int row = 0;
    unsigned short int column = 0;

    for(unsigned short int i = 0; i < nbOfBombs; i++)
    {    
       row = rand() % ROW_NB;
       column = rand() % COLUMN_NB;
       // si bombe pas présente sur la case choisie aléatoirement, on la place
       if (!dataBoard[row][column])
            dataBoard[row][column] = true;
        // si on n'a pas pu placer de bombe car déjà présente sur la case, on décrémente de 1
        // pour "recommencer un tour de boucle"
        else
            i--;            
    }
}

bool wasCellAlreadyVisible(const bool gameBoard[][COLUMN_NB], unsigned short int row, unsigned short int column)
{
   return gameBoard[row][column];
}

bool hasPlayerWon(const bool gameBoard[][COLUMN_NB], const bool dataBoard[][COLUMN_NB])
{  
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
void gameAgainstComputer(bool gameBoard[][COLUMN_NB], bool dataBoard[][COLUMN_NB])
{
    bool isGameActive;
    unsigned short int choosenRow = 0;
    unsigned short int choosenColumn = 0;

    setBombInDataBoard(dataBoard);

#ifdef DEBUG
    printDataBoard(dataBoard);
#endif

    printGameBoard(gameBoard, dataBoard);

    isGameActive = true;

    while(isGameActive)
    {
       do
       {
            puts("Veuillez choisir les coordonnées d'une case qui n'a pas encore été retournée '?'");
            // choix ligne puis colonne par le joueur
            printf("Choisir une ligne : ");
            choosenRow = getUserChoice(1,ROW_NB);
            printf("Choisir une colonne : ");
            choosenColumn = getUserChoice(1,COLUMN_NB);

            // on décrémente pour correspondre aux index du tableau 2D
            --choosenRow;
            --choosenColumn;
       } while (wasCellAlreadyVisible(gameBoard, choosenRow, choosenColumn));
       // si la ligne était déjà connue, le joueur doit faire une nouvelle sélection de coordonnées
       
        // on rend la case du jeu visible
        gameBoard[choosenRow][choosenColumn] = true;

        putc('\n', stdout);
        printGameBoard(gameBoard, dataBoard);

        // si bombe révélée => perdu
        if (dataBoard[choosenRow][choosenColumn])
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

void gameAgainstHuman(bool gameBoard[][COLUMN_NB], bool dataBoard[][COLUMN_NB])
{

}