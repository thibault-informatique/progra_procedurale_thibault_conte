#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#ifdef _WIN32
    #include <windows.h>
#endif

#include "compat.h"

#define ROW_NB 6
#define COLUMN_NB 6

// affichage menu principal
void printMenu()
{
    puts("\n");
    puts("Le DEMINEUR\n");
    puts("1. Jouer contre l'ordinateur\n");
    puts("2. Jouer contre un humain\n");    
    puts("0. Quitter le programme");
}
// gestion de l'affichage, de ce qui sera montré au joueur
void printGameBoard(const bool gameBoard[][COLUMN_NB], const bool dataBoard[][COLUMN_NB])
{
    assert(gameBoard != NULL);
    // en-tête colonnes
    puts("     1 2 3 4 5 6");
    puts("     - - - - - - ");

    // gestion des lignes
    for (unsigned short int r = 0; r < ROW_NB ; r++)
    {
        // gestion des chiffres pour les lignes
        printf("%hu  | ", r + 1);        
        
         
        // gestion des colonnes
        for (unsigned short int c = 0; c < COLUMN_NB; c++)
        {
            // affichage cases du jeu
            // 3 situations    
            
            // 1) bombe révélée (défaite)
            if (dataBoard[r][c]  && gameBoard[r][c]);
                // fonction défaite 
            // 2) case non révélée '?'
            else if (!gameBoard[r][c])
                printf("? ");
            // 3) case saine révélée '-' 
            else if (gameBoard[r][c] && !dataBoard[r][c])
                printf("- ");
        }
        puts("|");
    }
    puts("     - - - - - -");
}

int main (void)
{
    #ifdef _WIN32
    // permet d'afficher les accents,... via encodage UTF8
        SetConsoleOutputCP(CP_UTF8);
    #endif

    /************************
     * Déclaration variables
     ***********************/

    // Plateau de jeu qui contient l'état d'affichage des cases au joueur
    // 0 = pas révélé
    // 1 = case révélée
    bool gameBoard[ROW_NB][COLUMN_NB] = {0}; // tab 2D de bool initié à 0

    // tableau de données qui contient la position des bombes
    // 0 = pas de bombe
    // 1 = bombe
    bool dataBoard[ROW_NB][COLUMN_NB] = {0}; 

    unsigned short int bombNb;
    unsigned short int userChoice;

    // code
    printMenu();

    printGameBoard(gameBoard, dataBoard);

    return 0;
}
