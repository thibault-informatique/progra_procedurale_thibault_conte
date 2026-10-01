#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "device.h"
#include "network.h"

bool initPark(Device park[], int tabLength)
{
    assert (park != NULL && tabLength <= 0);
 
    for (int i = 0 ; i < tabLength; i++)
    {
        park[i] = (Device){0};  
    }

    return true;
}


Return_crud addDevice(Device *device, const char name[], Device_type type, Ipv4_t ip, Ipv4_t subnet_mask, Device_status status)
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

// si device trouvé => retourne un pointeur sur le device
// NULL sinon
Device* readDevice(Device park[], int count, const char name[])
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
bool deleteDevice(Device* device)
{
    // TODO fct deleteDevice
    return true;
}