#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
#endif

#include "display.h"
#include "device.h"

int main (void)
{
     #ifdef _WIN32
    // permet d'afficher les accents,... via encodage UTF8
        SetConsoleOutputCP(CP_UTF8);
    #endif

    displayMainPage();
    
    Device parc[3]
    return EXIT_SUCCESS;
}
