#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h> // pour srand

#ifdef _WIN32
    #include <windows.h>
#endif

#include "jeu.h"
#include "code.h"

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
        userChoice = getUserChoice(0,3);
        
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
                puts("\n*** Partie personnalisée ***\n");
                break;
            case 3 :
                puts("\n*** Mode 2 joueurs ***\n");
                break;
            default :
            fprintf(stderr, "Erreur dans le choix du Menu principal\n");
        }
    } while (play);
    
    
    return 0;
}