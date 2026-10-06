#ifndef DISPLAY_H
#define DISPLAY_H

#include "device.h"

void displayMainPage(void);

static void printDeviceType(Device_type type);

static void printDeviceStatus(Device_status status);

void askConfirmation();

void printDecimalIPv4(uint32_t address);

void printHexaIPv4(uint32_t address);

void displayDevice(Device device);

void displayPark(Device park[], int tabLength);

#endif