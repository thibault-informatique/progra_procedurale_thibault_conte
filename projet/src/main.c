#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef _WIN32
    #include <windows.h>
#endif

#include "../include/display.h"
#include "../include/device.h"
#include "../include/network.h"

#define NB_OF_DEVICES 3

// MACRO faciliter encodage IPv4 test
#define IPV4(a,b,c,d) (((uint32_t) a << 24) | ((uint32_t) b << 16 ) | ((uint32_t) c << 8) | (uint32_t) d) 

int main (void)
{
     #ifdef _WIN32
    // permet d'afficher les accents,... via encodage UTF8
        SetConsoleOutputCP(CP_UTF8);
    #endif


    Ipv4 testAdd1 = {.address = IPV4(192,168,1,10)};
    Ipv4 testAdd2 = {.address = IPV4(192,168,1,255)};

    Ipv4 mask = {.address = IPV4(255,255,255,0)};

    printf("L'adresse IP : ");
    printHexaIPv4(testAdd1.address);

    printf("%s", isBroadcastAddress(testAdd1,mask)? "est l'adresse broadcast\n" : "n'est pas l'adresse broadcast\n");

    // displayMainPage();


    
    // TODO fct pour convertir de IP 4 Bytes vers binaires et vice versa
    // Device test = {{"Routeur maison"}, ROUTER, {.address = 3232235777u}, {.address = 4294967040u}, STATUS_ONLINE};

    

    
    return EXIT_SUCCESS;
}
