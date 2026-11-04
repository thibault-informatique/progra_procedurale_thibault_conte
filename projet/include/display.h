#ifndef DISPLAY_H
#define DISPLAY_H

#include "device.h"

void displayMainPage(void);

static void printDeviceType(Device_type type);

static void printDeviceStatus(Device_status status);

void printAskConfirmation();

void printDecimalIPv4(uint32_t address);

void printHexaIPv4(uint32_t address);

void printDevice(const Device *device);

// NB: le premier device index 0 aura la valeur n°1 pour l'utilisateur
void displayPark(Park *park);

void printUpdateDeviceMenu(Park *Park);

#endif