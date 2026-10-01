#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
#endif

#include "display.h"
#include "device.h"

#define NB_OF_DEVICES 3

int main (void)
{
     #ifdef _WIN32
    // permet d'afficher les accents,... via encodage UTF8
        SetConsoleOutputCP(CP_UTF8);
    #endif

    displayMainPage();
    
    Device park[NB_OF_DEVICES];
    if (initPark(park, NB_OF_DEVICES) == false) 
    {
        fprintf(stderr, "Erreur initialisation parc\n");
        return EXIT_FAILURE;
    }

    
    
    return EXIT_SUCCESS;
}
