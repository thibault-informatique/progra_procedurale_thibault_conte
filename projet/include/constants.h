#ifndef CONSTANTS_AND_INPUTS_H
#define CONSTANTS_AND_INPUTS_H

#include <stdint.h>
#include <stdbool.h>

#define PARK_LENGTH 10
#define DEVICE_NAME_LENGTH 50
#define PART_OF_DEVICE_NAME_LENGTH 20
#define DEBUG 1

// MACRO faciliter encodage IPv4 test
#define IPV4(a,b,c,d) (((uint32_t) a << 24) | ((uint32_t) b << 16 ) | ((uint32_t) c << 8) | (uint32_t) d) 

#endif