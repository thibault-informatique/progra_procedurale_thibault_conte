#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdint.h>

#define PARK_LENGTH 10
#define DEBUG 1

// MACRO faciliter encodage IPv4 test
#define IPV4(a,b,c,d) (((uint32_t) a << 24) | ((uint32_t) b << 16 ) | ((uint32_t) c << 8) | (uint32_t) d) 

#endif