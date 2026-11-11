#ifndef NETWORK_H
#define NETWORK_H

#include <stdbool.h>

#include "device.h"
#include "constants.h"

Return_code checkLocalAddress(Ipv4 ip, Ipv4 mask);

bool isSameSubnet(Ipv4 newIp, Ipv4 mask, Ipv4 networkAddress);

Return_code getNetworkAddress(Ipv4 ip, Ipv4 mask, Ipv4 *networkAddress);

// pour qu'un masque soit valide il faut que tous les bits soient contigus à 1
bool isValidMask(Ipv4 subnet_mask);

bool isPrivateIPv4Address(Ipv4 address);

unsigned short translateMaskInPrefix(Ipv4 mask);

bool userConfirmInput();

uint32_t setHexaIpv4Address();
Return_code setDecimalIpv4Address(Ipv4 *newIp);



#endif