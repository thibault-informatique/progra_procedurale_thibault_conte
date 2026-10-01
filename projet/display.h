#ifndef DISPLAY_H
#define DISPLAY_H

#include "device.h"

void displayMainPage(void);

static void printDeviceType(Device_type type);

static void printDeviceStatus(Device_status status);

static void printIpv4(Ipv4_t ip);

void displayDevice(Device device);

void displayPark(Device park[], int tabLength);

#endif