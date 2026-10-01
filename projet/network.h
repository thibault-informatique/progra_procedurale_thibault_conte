#ifndef NETWORK_H
#define NETWORK_H

#include <stdbool.h>

#include "device.h"

bool isValidIp(ipv4_t ip);
bool isValidMask(ipv4_t subnet_mask);

#endif