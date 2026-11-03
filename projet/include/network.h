#ifndef NETWORK_H
#define NETWORK_H

#include <stdbool.h>

#include "device.h"

bool isValidAsLocalIpAddress(Ipv4 ip, Ipv4 mask);

// pour qu'un masque soit valide il faut que tous les bits soient contigus à 1
bool isValidMask(Ipv4 subnet_mask);

bool isPrivateIPv4Address(Ipv4 address);

bool userConfirmInput();

uint32_t setHexaIPv4Address();
//uint32_t getDecimalIPv4Address();



#endif