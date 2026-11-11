#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../include/device.h"
#include "../include/network.h"
#include "../include/display.h"
#include "../include/constants.h"

/****************************
****** DEVICE SETTERS   *****
*****************************/
// nom - type - ADRESSE IP - MASQUE - STATUT

Return_code setDeviceName(Device *device, const char newName[])
{
    assert (device != NULL && newName != NULL);

    if(strlen(newName) >= sizeof(device->name))
        return ERR_STR_LENGTH;

    strcpy(device->name, newName);
    return SUCCESS;
}

void setDeviceType(Device *device, Device_type newType)
{
    assert (device != NULL);

    device->type = newType;
}


Return_code setDeviceIpAddressAndMask(Device *device, Ipv4 address, Ipv4 mask)
{
    assert (device != NULL);

    // Vérifications

    // 1) masque contigu (tous les bits à 1 à G) 
    if(!isValidMask(mask))
        return ERR_INVALID_MASK;

    // 3) IP locale : ni publique, ni adresse du réseau ni broadcast
    Return_code result = checkLocalAddress(address, mask);

    if(result == SUCCESS)
    {
        device->ipAddress = address;
        device->subnet_mask = mask;
    }
    // Retour du return code (SUCCESS ou ERR détaillée)
    return result;

}

void setDeviceStatus(Device *device, Device_status newStatus)
{
    assert(device != NULL);

    device->status = newStatus;
}


Return_code initDevice(Device *device, const char name[], Device_type type, Ipv4 ip, Ipv4 mask, Device_status status)
{
    // gestion erreurs dev
    assert (device != NULL && name != NULL);
    
    // gestion erreurs user
    // - nom trop long
    // - addresse ip / masque non valide
    if(strlen(name) >= sizeof(device->name))
        return ERR_STR_LENGTH;

    Return_code result = checkLocalAddress(ip, mask);
    if (result != SUCCESS)
        return result;
    
    if(!isValidMask(mask))
        return ERR_INVALID_MASK;    
    
    // code d'init / ajout device
    strcpy(device->name, name);
    device->type = type;    
    device->ipAddress = ip;
    device->subnet_mask = mask;
    device->status = status;

    return SUCCESS;
}


  /****************************
  ******       PARK       *****
  *****************************/

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

Return_code addDevice(Park *park, Device *device)
{
    assert(park != NULL && device != NULL);

    if (park->nbOfDevice == PARK_LENGTH)
        return ERR_PARK_FULL;
    
    park->device[park->nbOfDevice++] = *device;    
    return SUCCESS;    
}


int findDevice(Park *park, const char name[])
{
    assert(park != NULL);

    for (int i = 0; i < park->nbOfDevice; i++)
    {
        if (strcmp(park->device[i].name, name) == 0)
            return i;
    }

    return -1;
}

bool updateDevice(Park *park, Device* device)
{
    assert (park != NULL && device != NULL);

    displayCrudMenu(DISPLAY_UPDATE);
    
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


