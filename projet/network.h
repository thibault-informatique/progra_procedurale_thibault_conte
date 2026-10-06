#ifndef NETWORK_H
#define NETWORK_H

#include <stdbool.h>

#include "device.h"

bool isValidIp(Ipv4_t ip);
bool isValidMask(Ipv4_t subnet_mask);

bool isPrivateIp(Ipv4_t ip);

bool confirmation();

uint32_t setHexaIPv4Address();
//uint32_t getDecimalIPv4Address();



#endif