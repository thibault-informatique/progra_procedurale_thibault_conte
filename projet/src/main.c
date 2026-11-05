#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef _WIN32
    #include <windows.h>
#endif

#include "../include/display.h"
#include "../include/device.h"
#include "../include/manager.h"
#include "../include/network.h"
#include "../include/constantsAndInputs.h"

#define NB_OF_DEVICES 3

 // TODO fct pour convertir de IP 4 Bytes vers binaires et vice versa

int main (void)
{
     #ifdef _WIN32
    // permet d'afficher les accents,... via encodage UTF8
        SetConsoleOutputCP(CP_UTF8);
    #endif

    // DECLARATION

    bool runningProg = true;
    int userChoice = -1;
    // Ipv4 mask = {.address = IPV4(128,0,1,0)};    
    Device routeur1 = {{"Routeur maison"}, ROUTER, {.address = IPV4(192,168,1,1)}, {.address = IPV4(255,255,255,0)}, STATUS_ONLINE};
    Device switch1 = {{"Switch maison"}, SWITCH, {.address = IPV4(192,168,1,2)}, {.address = IPV4(255,255,255,0)}, STATUS_ONLINE};
    Device pc1 = {{"PC bureau"}, WORKSTATION, {.address = IPV4(192,168,1,10)}, {.address = IPV4(255,255,255,0)}, STATUS_OFFLINE};
    Device printer1 = {{"Imprimante brother DCP-L3560CDW"}, PRINTER, {.address = IPV4(192,168,1,254)}, {.address = IPV4(255,255,255,0)}, STATUS_MAINTENANCE};
    Device server1 = {{"NAS"}, SERVER, {.address = IPV4(192,168,1,2)}, {.address = IPV4(255,255,255,0)}, STATUS_FAILED};

    Park park[PARK_LENGTH];

    // INIT PARK ET AJOUT MANUEL DEVICES
    if(!initPark(park))
        fprintf(stderr, "Erreur initialisation du parc\n");
    
    if(addDevice(park, &routeur1) != SUCCES)
        fprintf(stderr, "Erreur ajout équipement au parc\n");

    if(addDevice(park, &switch1) != SUCCES)
        fprintf(stderr, "Erreur ajout équipement au parc\n");

    if(addDevice(park, &pc1) != SUCCES)
        fprintf(stderr, "Erreur ajout équipement au parc\n");

    if(addDevice(park, &printer1) != SUCCES)
        fprintf(stderr, "Erreur ajout équipement au parc\n");

    if(addDevice(park, &server1) != SUCCES)
        fprintf(stderr, "Erreur ajout équipement au parc\n");



    // MENU PRINCIPAL
    do
    {
       displayMainPage();

#if DEBUG
        if(!getUserChoice(0,5, &userChoice))
            fprintf(stderr, "Erreur dans la fct getUserChoice\n");
#else
        if(!getUserChoice(0,4, &userChoice))
            fprintf(stderr, "Erreur dans la fct getUserChoice\n");
#endif
        
        switch(userChoice)
        {
            case 0 : 
                runningProg = false;
                puts("\n*** Fin du programme ***\n");               
                break;
            case 1 :                
                handlingDeviceMenu(park);
                break;
            case 2 : 
                // recherche d'un élément
                break;
            case 3 :
                // calculs réseau
                break;
            case 4 :
                // stats
                break;
#if DEBUG
            case 5:
                puts("\nTest debug fonctions: \n");                
                break;
#endif
            default :
                fprintf(stderr, "Erreur dans le choix du Menu principal\n");
        }

    } while (runningProg);   
    
    return EXIT_SUCCESS;
}
