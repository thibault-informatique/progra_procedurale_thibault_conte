#ifndef MANAGER_H
#define MANAGER_H

#include "device.h"

// version simplifiée getUserChoice
// obtenir un nombre compris entre la borne minimale et maximale
bool getUserChoice(int minValue, int maxValue, int *number);

void handlingDeviceMenu(Park *park);
#endif