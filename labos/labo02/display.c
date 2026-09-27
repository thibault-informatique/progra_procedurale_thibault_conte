#include "display.h"
#include <stdio.h>
#include <assert.h>

void printMenu()
{
    puts("\n");
    puts("Le DEMINEUR\n");
    puts("1. Jouer contre l'ordinateur\n");
    puts("2. Jouer contre un humain\n");    
    puts("0. Quitter le programme");
}
// gestion de l'affichage de la grille de jeu, ce qui sera montré au joueur
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
            if (dataBoard[r][c]  && gameBoard[r][c])
                printf("B ");
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

// affichage grille des bombes placées pr test dev
void printDataBoard(const bool dataBoard[][COLUMN_NB])
{
    assert(dataBoard != NULL);
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
            printf("%d ", dataBoard[r][c]);          
        }
        puts("|");
    }
    puts("     - - - - - -");
}

