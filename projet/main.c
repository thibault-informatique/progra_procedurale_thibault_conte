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

    // TODO fct pour convertir de IP 4 Bytes vers binaires et vice versa
    Device test = {{"Routeur maison"}, ROUTER, {.address = 3232235777u}, {.address = 4294967040u}, STATUS_ONLINE};

    displayDevice(test);

    
    return EXIT_SUCCESS;
}
