#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "device.h"
#include "network.h"


Return_crud initDevice(Device *device, const char name[], Device_type type, Ipv4 ip, Ipv4 mask, Device_status status)
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
    if(!isValidMask(mask))
        return ERR_INVALID_MASK;    
    
    // code d'init / ajout device
    strcpy(device->name, name);
    device->type = type;    
    device->ipAddress = ip;
    device->subnet_mask = mask;
    device->status = status;

    return SUCCES;
}


//  ***  PARK    ***

bool initPark(Device park[], int tabLength)
{
    assert (park != NULL && tabLength > 0);
 
    for (int i = 0 ; i < tabLength; i++)
    {
        park[i] = (Device){0};  
    }

    return true;
}

// CRUD



Device* findDevice(Device park[], int count, const char name[])
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(park[i].name, name) == 0)
            return &park[i];
    }

    return NULL;
}

bool updateDevice(Device* device)
{
    // TODO fct updateDevice
    return true;
}
bool removeDevice(Device* device)
{
    // TODO fct deleteDevice
    return true;
}


