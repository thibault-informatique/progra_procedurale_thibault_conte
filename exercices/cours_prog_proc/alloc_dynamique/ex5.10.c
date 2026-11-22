#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 
#include <assert.h>
#include <string.h>
#include <windows.h>

#define PARK_LENGTH 10
#define DEVICE_NAME_LENGTH 50
#define PART_OF_DEVICE_NAME_LENGTH 20

typedef struct 
{
    uint32_t address; // IPv4 (32bits) unsigned int qui fait exactement 32 bits       
} Ipv4;  

typedef enum 
{
    ROUTER,
    SWITCH,
    FIREWALL,
    SERVER,
    WORKSTATION,
    PRINTER,
    ACCESS_POINT,
    OTHER,
    UNKNOWN
} Device_type;

typedef enum 
{
    STATUS_ONLINE,
    STATUS_OFFLINE,
    STATUS_MAINTENANCE,
    STATUS_FAILED,
    STATUS_UNKNOWN
    
} Device_status;

typedef struct 
{
    char name[DEVICE_NAME_LENGTH];
    Device_type type;
    Ipv4 ipAddress;
    Ipv4 subnet_mask;
    Device_status status;

} Device;

typedef struct 
{
    Device *devices;
    int nbOfDevices;
    int capacity;
} Park;

int addDeviceToDynamicPark(Park *park, const Device *newDevice)
{
    // park ne peut être NULL car est initialisé au début du programme
    assert(park != NULL && newDevice != NULL && park->nbOfDevices <= park->capacity);

    // si parc trop petit => on double la capacité du parc 
    if(park->nbOfDevices == park->capacity)
    {
        size_t newCapacity = (park->capacity == 0) ? 10 : park->capacity * 2;

        Device *temp = (Device*) realloc (park->devices, newCapacity * sizeof(Device));
        
        if(temp == NULL)
            {
                fprintf(stderr, "Erreur realloc dans addDeviceDynamicPark\n");
                return -1;
            }
        
        park->devices = temp;
        park->capacity = newCapacity;
    }

    // ajout du nouvel appareil
    park->devices[park->nbOfDevices++] = *newDevice;

    return 0;
}

int removeDeviceFromDynamicPark(Park *park, const char *name)
{
    assert(park != NULL && name != NULL);

    for (int i = 0; i < park->nbOfDevices; i++)
    {
        if (strcmp(park->devices[i].name, name) == 0)
            {
                // décale les devices suivants d'un vers la G
                for (int j = i; j < park->nbOfDevices - 1; j++)
                {
                    park->devices[j] =  park->devices[j + 1];
                }
                park->nbOfDevices--;
                // on efface le doublon de fin
                park->devices[park->nbOfDevices] = (Device){0};
                // on quitte la fonction removeDevice et on valide la suppression
                return 0;
            }
    }
    // si pas trouvé
    return -1;
}

void freePark(Park *park)
{
    if (park == NULL)
        return;
    
    free(park->devices);
    park->devices = NULL;
    park->capacity = 0;
    park->nbOfDevices = 0;
}

int main(void)
{
    SetConsoleOutputCP(CP_UTF8);
    
    // un seul parc, déclaré sur la stack : pas de malloc/free sur Park elle-même
    Park park = { NULL, 0, 0 };

    // main généré par IA pour tester fcts
    Device toAdd[7] =
    {
        { "routeur-core", ROUTER,     {0xC0A80001}, {0xFFFFFF00}, STATUS_ONLINE     },
        { "sw-etage1",   SWITCH,      {0xC0A80002}, {0xFFFFFF00}, STATUS_ONLINE     },
        { "sw-etage2",   SWITCH,      {0xC0A80003}, {0xFFFFFF00}, STATUS_ONLINE     },
        { "firewall",    FIREWALL,    {0xC0A80004}, {0xFFFFFF00}, STATUS_ONLINE     },
        { "srv-dhcp",    SERVER,      {0xC0A80005}, {0xFFFFFF00}, STATUS_ONLINE     },
        { "pc-compta",   WORKSTATION, {0xC0A80006}, {0xFFFFFF00}, STATUS_OFFLINE    },
        { "impr-rdc",    PRINTER,     {0xC0A80007}, {0xFFFFFF00}, STATUS_MAINTENANCE}
    };

    for (int i = 0; i < 7; i++)
    {
        if (addDeviceToDynamicPark(&park, &toAdd[i]) != 0)
        {
            printf(" ECHEC\n");
            freePark(&park);
            return 1;
        }
    }
    printf("Ajout de %d équipements... %s (capacité  %d)\n", 
        park.nbOfDevices, 
        park.nbOfDevices <= park.capacity ? "OK" : "ERREUR",
        park.capacity);

    printf("Suppression de sw-etage1...");
    if (removeDeviceFromDynamicPark(&park, "sw-etage1") == 0)
        printf(" OK\n");
    else
        printf(" INTROUVABLE\n");

    printf("%d équipements dans le parc.\n", park.nbOfDevices);

    freePark(&park);

    return 0;
}