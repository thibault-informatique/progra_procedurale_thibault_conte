#ifndef NETWORK_H
#define NETWORK_H

#include <stdbool.h>

#include "device.h"
#include "constants.h"

// structure pour contenir calculs réseaux
typedef struct 
{
    Ipv4 networkAddress;
    Ipv4 broadcastAddress;
    unsigned short prefix; 
}NetworkCalcul;


Return_code checkLocalAddress(Ipv4 ip, Ipv4 mask);

bool isSameSubnet(Ipv4 newIp, Ipv4 mask, Ipv4 networkAddress);



// pour qu'un masque soit valide il faut que tous les bits soient contigus à 1
bool isValidMask(Ipv4 subnet_mask);

bool isPrivateIPv4Address(Ipv4 address);

bool userConfirmInput();

Return_code setHexaIpv4Address(Ipv4 *newIp);
Return_code setDecimalIpv4Address(Ipv4 *newIp);

/***  NETWORK CALCULATION ***/

Return_code getNetworkAddress(Ipv4 ip, Ipv4 mask, Ipv4 *networkAddress);

Return_code getBroadcast(Ipv4 ip, Ipv4 mask, Ipv4 *broadcastAddress);

unsigned short getPrefix(Ipv4 mask);

// récupérer les résultats des calculs réseaux dans une structure
NetworkCalcul calculateNetwork(Ipv4 address, Ipv4 mask);

#endif