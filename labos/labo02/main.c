#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> // generer nbre aléatoire


#ifdef _WIN32
    #include <windows.h>
#endif

#include "display.h"
#include "gameplay.h"
#include "constants.h"




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

    unsigned short int userChoice = 1;

    // initialisation graine pour nbre aléatoire
    srand((unsigned)time(NULL));

    // code
    do{
        initBoard(gameBoard);
        initBoard(dataBoard);

        printMenu();
        userChoice = getUserChoice(0,2);
        
        switch(userChoice)
        {
            case 0 : 
                puts("*** Fin du programme ***\n");
                break;
            case 1 :
                gameAgainstComputer(gameBoard, dataBoard);
                break;
            case 2 : 
                gameAgainstHuman(gameBoard, dataBoard);
                break;
            default :
            fprintf(stderr, "Erreur dans le choix du Menu principal\n");
        }
    }while (userChoice != 0);

    return 0;
}
