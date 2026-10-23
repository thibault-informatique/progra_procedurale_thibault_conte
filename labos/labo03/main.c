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

// nouveautés : première utilisation de memcpy

int main(void)
{
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    bool play = true;
    short int userChoice = -1;

    // initialisation graine pour gestion nbre aléatoire
    srand((unsigned)time(NULL)); 

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
               classicGame();
                break;
            case 2 : 
                customGame();
                break;
            case 3 :
                gameAgainstHuman();
                break;
#if DEBUG
            case 4:
                puts("\nTest debug fonctions: \n");                
                break;
#endif
            default :
                fprintf(stderr, "Erreur dans le choix du Menu principal\n");
        }
    } while (play);
    
    
    return 0;
}