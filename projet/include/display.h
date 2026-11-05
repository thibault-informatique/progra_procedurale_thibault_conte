#ifndef DISPLAY_H
#define DISPLAY_H

#include "device.h"

/***  AFFICHAGE DES MENUS ***/
void displayMainPage(void);

void displayHandlingDevicesMenu(void);

void printUpdateDeviceMenu(Park *park);

void printUpdateDeviceMenu(Park *park);

void printAskConfirmation();

void printDecimalIPv4(uint32_t address);

void printHexaIPv4(uint32_t address);

void printDevice(const Device *device);

// NB: le premier device index 0 aura la valeur n°1 pour l'utilisateur
void displayPark(Park *park);



#endif