#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "device.h"
#include "network.h"


enum return_crud  addDevice(Device *device, const char name[], device_type type, ipv4_t ip, ipv4_t subnet_mask, device_status status)
{
    // gestion erreurs dev
    assert (device != NULL && name != NULL);
    
    // gestion erreurs user
    // - nom trop long
    // - addresse ip / masque non valide
    if(strlen(name) >= sizeof(device->name))
        return ERR_STR_LENGTH;

    if(!isValidIp(ip))
        return ERR_INVALID_IP;
    if(!isValidMask(subnet_mask))
        return ERR_INVALID_MASK;    
    
    // code d'init / ajout device
    strcpy(device->name, name);
    device->type = type;    
    device->ip = ip;
    device->subnet_mask = subnet_mask;
    device->status = status;

    return SUCCES;
}

Device* readDevice(Device* device);
bool updateDevice(Device* device);
bool deleteDevice(Device* device);