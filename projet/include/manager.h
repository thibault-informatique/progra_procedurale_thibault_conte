#ifndef MANAGER_H
#define MANAGER_H

#include "device.h"
#include "constants.h"

void cleanBuffer();
/***  Getters ***/

// version simplifiée getUserChoice
// obtenir un nombre compris entre la borne minimale et maximale
bool getUserChoice(int minValue, int maxValue, int *number);


bool getName(char *name, int nameLength);


/*** Setters ***/
Device_type setType();
Device_status setStatus();

/*** HANDLERS UPDATE ***/

Return_code handleUpdateName(Device *device);
Return_code handleUpdateType(Device *device);
Return_code handleUpdateAddressAndMask(Device *device);
Return_code handleUpdateStatus(Device *device);

/*** MENUS MANAGER ***/
void handleDeviceMenu(Park *park);

//void handleAddDevce(Park *park);
void handleReadDevice(Park *park);

void handleUpdateDevice(Park *park);

void handleRemoveDevice(Park *park);

#endif