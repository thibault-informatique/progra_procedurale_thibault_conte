#ifndef MANAGER_H
#define MANAGER_H

#include "device.h"

void cleanBuffer();
/***  Getters ***/

// version simplifiée getUserChoice
// obtenir un nombre compris entre la borne minimale et maximale
bool getUserChoice(int minValue, int maxValue, int *number);


bool getName(char *name, int nameLength);

/*** Setters ***/
Device_type setType();

/*** MENUS MANAGER ***/
void handleDeviceMenu(Park *park);

//void handleAddDevce(Park *park);
void handleReadDevice(Park *park);

void handleUpdateDEvice(Park *park);

void handleRemoveDevice(Park *park);

#endif