#ifndef NETWORK_H
#define NETWORK_H

#include <stdbool.h>

#include "device.h"

bool isValidIp(Ipv4 ip);
bool isValidMask(Ipv4 subnet_mask);

bool isPrivateIp(Ipv4 ip);

bool userConfirmInput();

uint32_t setHexaIPv4Address();
//uint32_t getDecimalIPv4Address();



#endif