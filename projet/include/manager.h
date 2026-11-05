#ifndef MANAGER_H
#define MANAGER_H

#include "device.h"

void cleanBuffer();
/***  Getters ***/

// version simplifiée getUserChoice
// obtenir un nombre compris entre la borne minimale et maximale
bool getUserChoice(int minValue, int maxValue, int *number);


bool getName(char *name, int nameLength);

/*** MENUS MANAGER ***/
void handlingDeviceMenu(Park *park);

void handlingRemoveDevice(Park *park);

#endif