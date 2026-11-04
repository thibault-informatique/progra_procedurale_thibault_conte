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

    if(!isValidAsLocalIpAddress(ip, mask))
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

bool initPark(Park *park)
{
    assert (park != NULL);    
   
    // plus court,  memset(park, 0, sizeof(Device) * (size_t)tabLength);
    for (int i = 0 ; i < PARK_LENGTH; i++)
    {
        park->device[i] = (Device){0};  
    }

    park->nbOfDevice = 0;

    return true;
}

// CRUD

Return_crud addDevice(Park *park, Device *device)
{
    assert(park != NULL && device != NULL);

    if (park->nbOfDevice == PARK_LENGTH)
        return ERR_PARK_FULL;
    
    park->device[park->nbOfDevice++] = *device;    
    return SUCCES;    
}


Device* findDevice(Park *park, const char name[])
{
    for (int i = 0; i < park->nbOfDevice; i++)
    {
        if (strcmp(park->device[i].name, name) == 0)
            return &park[i];
    }

    return NULL;
}

bool updateDevice(Park *park, Device* device)
{
    printUpdateDeviceMenu(park);
    
    return true;
}

// supprimer un device via son nom
// stockage dans tab donc décaler tous les éléments après vers la G
bool removeDevice(Park *park, const char name[])
{
    assert(park != NULL && name != NULL);

    for (int i = 0; i < park->nbOfDevice; i++)
    {
        if (strcmp(park->device[i].name, name) == 0)
            {
                // décale les devices suivants d'un vers la G
                for (int j = i; j < park->nbOfDevice - 1; j++)
                {
                    park->device[j] =  park->device[j + 1];
                }
                park->nbOfDevice--;
                // on efface le doublon de fin
                park->device[park->nbOfDevice] = (Device){0};
                // on quitte la fonction removeDevice et on valide la suppression
                return true;
            }
    }
    // si pas trouvé
    return false;
}


