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

    Device park[2];

    if (!initPark(park, 2))
        fprintf(stderr, "erreur initialisation tab parc de machines\n");

    Device *pDevice = malloc(sizeof(Device*));

    if(createDevice(pDevice, "switch maison", SWITCH, (Ipv4_t){0xC0A80D06}, (Ipv4_t){0xFFFFFF00}, STATUS_ONLINE) != SUCCES)
    {
        fprintf(stderr, "Erreur ajout Device\n");
    }

    Device *pDevice2 = malloc(sizeof(Device*));

    if(createDevice(pDevice2, "routeur maison", ROUTER, (Ipv4_t){0xC0A80D00}, (Ipv4_t){0xFFFFFF00}, STATUS_ONLINE) != SUCCES)
    {
        fprintf(stderr, "Erreur ajout Device\n");
    }


    

  
    
    return EXIT_SUCCESS;
}
