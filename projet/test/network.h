#ifndef NETWORK_H
#define NETWORK_H

#include <stdbool.h>

#include "device.h"

bool isValidIp(Ipv4_t ip);
bool isValidMask(Ipv4_t subnet_mask);

bool isPrivateIp(Ipv4_t ip);

#endif