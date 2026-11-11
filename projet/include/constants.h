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


typedef enum 
{
    SUCCESS,
    ERR_STR_LENGTH,
    ERR_PUBLIC_IP,
    ERR_INVALID_DECIMAL_ADDRESS,
    ERR_INVALID_HEXA_ADDRESS,
    ERR_OCTET_SIZE,
    ERR_INVALID_LOCAL_IP,
    ERR_INVALID_MASK,
    ERR_NOT_IN_SUBNET,
    ERR_IS_NETWORK_ADDRESS,
    ERR_IS_BROADCAST,
    ERR_PARK_FULL,
    ERR_DEVICE_NOT_FOUND
} Return_code;


#endif