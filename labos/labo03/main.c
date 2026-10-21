#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h> // pour srand

#ifdef _WIN32
    #include <windows.h>
#endif

#include "jeu.h"
#include "code.h"
#include "debug.h"

#define DEBUG 1

int main(void)
{
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    bool play = true;
    short int userChoice = -1;

    srand((unsigned)time(NULL)); // initialisation graine pour gestion nbre aléatoire

    do
    {
        printMenu();
#if DEBUG
        userChoice = getUserChoice(0,4);
#else
        userChoice = getUserChoice(0,3);
#endif
        
        switch(userChoice)
        {
            case 0 : 
                play = false;
                puts("\n*** Fin du programme ***\n");               
                break;
            case 1 :                
                //classicGame();


                break;
            case 2 : 
                puts("\n*** Partie personnalisée ***\n");
                break;
            case 3 :
                puts("\n*** Mode 2 joueurs ***\n");
                break;
#if DEBUG
            case 4:
                puts("\nTest debug fonctions: \n");
                
                int code1[4] = {1,2,3,4};
                int code2[4] = {2,3,4,1};  //  0 - 4
                int code3[4] = {7,8,9,1};  //  0 - 1
                int code4[4] = {1,0,4,3};  //  1 - 2
                int code5[4] = {5,6,7,8};  //  0 - 0
                int code6[4] = {1,2,3,4};  //  4 - 0

                int goodPos = 0;
                int wrongPos = 0;

                updatePositionsCounters(code1, code6, 4, &goodPos, &wrongPos);
                printValuesPositionsCounter(&goodPos, &wrongPos);
                printf("%s\n", playerWin(&goodPos, 4)? "Victoire" : "Encore x essais");                        


                
                break;
#endif
            default :
            fprintf(stderr, "Erreur dans le choix du Menu principal\n");
        }
    } while (play);
    
    
    return 0;
}