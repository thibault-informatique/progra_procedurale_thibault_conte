#ifndef DISPLAY_H
#define DISPLAY_H

#include "device.h"
#include "constants.h"

typedef enum: unsigned char
{
    DISPLAY_CREATE,
    DISPLAY_READ,
    DISPLAY_UPDATE,
    DISPLAY_DELETE

} Crud_display_choice;

/***  AFFICHAGE DES MENUS ***/
void displayMainPage(void);

void displayDevicesMenu(void);

void displayCrudMenu(Crud_display_choice crud);

void displayChoosePartOfDeviceToUpdate();

void displayDeviceType();

void displayDeviceStatus();

/***  AFFICHAGE AUTRE***/

void displaySetHexaIpv4Address();
void displaySetDecimalIpv4Address();

void printAddressError(Return_code code);

void printTryAgainChoice();

void printAskConfirmation();

void printDecimalIpv4(const Ipv4 ip);

void printHexaIpv4(const Ipv4 ip);

void printDevice(const Device *device);

// NB: le premier device index 0 aura la valeur n°1 pour l'utilisateur
void displayPark(Park *park);



#endif