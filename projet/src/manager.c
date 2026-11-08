#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../include/manager.h"
#include "../include/display.h"
#include "../include/network.h"

void cleanBuffer()
{
    int c;
    while ((c=getchar()) != '\n' && c != EOF);
}

/***  Getters ***/

bool getUserChoice(int minValue, int maxValue, int *number)
{
    bool correctNumber = false;    

    while (!correctNumber)
    {
        printf("Votre choix: ");
        int nbRead = scanf("%d", number);

        if(nbRead == 1 && *number >= minValue && *number <= maxValue)
        {
            correctNumber = true;
            putchar('\n');
        }

        else
        {
            // si scanf a échoué => il reste des éléments à vider dans le buffer
            if (nbRead != 1)
            {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }
            printf("\nLe nombre doit être compris entre [%d-%d].\n", minValue, maxValue);
        }
    }
    return true;
}

bool getName(char *name, int nameLength)
{
    assert (name != NULL && nameLength > 1);

    bool correctName = false;

    fprintf(stdout, "Indiquez le nom de l'appareil: ");

    while(!correctName)
    {
        if(fgets(name, nameLength, stdin) == NULL)
        {
            fprintf(stderr, "Erreur de lecture dans getName()\n");
            return false;
        }        

        // si ligne tronquée '\n' pas récupéré
        if (strchr(name, '\n') == NULL)
        {
            cleanBuffer();
            fprintf(stdout, "Max %d caractères\n", nameLength - 1);
            fprintf(stdout, "Recommencez: ");
        }
        else if (name[0] == '\n')
        {
            fprintf(stdout, "Le nom doit contenir au moins une lettre\n");
            fprintf(stdout, "Recommencez: ");
        }
        // sinon c'est correct et on remplace le '\n' par '\0'
        else
        {
            name[strcspn(name, "\n")] ='\0';
            correctName = true;
        }
    }

    return true;
}


Device_type setType()
{
    int choice;

    displayDeviceType();
    getUserChoice(1,9, &choice);

    switch(choice)
    {
        case 1 : return ROUTER;
        case 2 : return SWITCH;
        case 3 : return FIREWALL;
        case 4 : return SERVER;
        case 5 : return WORKSTATION;
        case 6 : return PRINTER;
        case 7 : return ACCESS_POINT;
        case 8 : return OTHER;
        case 9 : return UNKNOWN;
        default : 
            fprintf(stdout, "Erreur dans le choix du switchcase fct setType()\n");
            return UNKNOWN;
    }
}

Device_status setStatus()
{
     int choice;

    displayDeviceStatus();
    getUserChoice(1,5, &choice);

    switch(choice)
    {
        case 1 : return STATUS_ONLINE;
        case 2 : return STATUS_OFFLINE;
        case 3 : return STATUS_MAINTENANCE;
        case 4 : return STATUS_FAILED;
        case 5 : return STATUS_UNKNOWN;
        default : 
            fprintf(stdout, "Erreur dans le choix du switchcase fct setType()\n");
            return STATUS_UNKNOWN;
    }
}

/*** HANDLERS UPDATE ***/

Return_code handleUpdateName(Device *device)
{
    assert(device != NULL);
    
    char newName[DEVICE_NAME_LENGTH];

    if(!getName(newName, DEVICE_NAME_LENGTH))
        return ERR_STR_LENGTH;

    Return_code result = setDeviceName(device, newName);

    switch(result)
    {
        case SUCCESS :
            fprintf(stdout,"Nom modifié avec succès!\n");
            break;
        case ERR_STR_LENGTH :
            fprintf(stdout,"Nom trop long\n");
            break;
        default :
            fprintf(stdout, "La modification a échouée\n");
    }

    return result;
}

// return_code peu utile mais pour respecter le même style
Return_code handleUpdateType(Device *device)
{
    assert(device != NULL);

    setDeviceType(device, setType());

    return SUCCESS;
}

Return_code handleUpdateAddressAndMask(Device *device)
{
    assert(device != NULL);

 Ipv4 newAddress = {0};
    Ipv4 newMask    = {0};

    // saisie de la nouvelle adresse IP
    fprintf(stdout, "\nNouvelle adresse IP:\n");
    newAddress.address = setHexaIPv4Address();

    // saisie du nouveau masque
    fprintf(stdout, "\nNouveau masque de sous-réseau:\n");
    newMask.address = setHexaIPv4Address();

    Return_code result = setDeviceIpAddressAndMask(device, newAddress, newMask);

    switch(result)
    {
        case SUCCESS :
            fprintf(stdout, "Adresse et masque modifiés avec succès!\n");
            break;
        case ERR_INVALID_MASK :
            fprintf(stdout, "Masque non valide (bits à 1 contigus attendus)\n");
            break;
        case ERR_PUBLIC_IP :
            fprintf(stdout, "L'adresse doit appartenir à une plage privée\n");
            break;
        case ERR_IS_NETWORK_ADDRESS :
            fprintf(stdout, "Cette adresse est celle du réseau\n");
            break;
        case ERR_IS_BROADCAST :
            fprintf(stdout, "Cette adresse est celle de broadcast\n");
            break;
        default :
            fprintf(stdout, "La modification a échouée\n");
    }

    return result;
}

// return_code peu utile mais pour respecter le même style
Return_code handleUpdateStatus(Device *device)
{
    assert(device != NULL);   

    setDeviceStatus(device, setStatus());

    return SUCCESS;
}

/*** MENUS MANAGER ***/

void handleDeviceMenu(Park *park)
{
    int userChoice = -1;
    bool runningMenu = true;
    while(runningMenu)
    {
        displayDevicesMenu();
        getUserChoice(0,5,&userChoice);
        cleanBuffer();

        switch(userChoice)
        {
            case 0: 
                runningMenu = false;
                break;
                
            case 1: 
                
                break;
                
            case 2: 
                handleReadDevice(park);
                break;
                
            case 3: 
                handleUpdateDevice(park);
                break;
                
            case 4: 
                handleRemoveDevice(park);
                break;
            
            case 5:
                displayPark(park);
                break;
            
            default :
                fprintf(stderr, "Erreur switchcase handleDeviceMenu()\n");
        }
    }
}

void handleReadDevice(Park *park)
{
    char device[DEVICE_NAME_LENGTH];
    int indexDevice;

    displayCrudMenu(DISPLAY_READ);

    if(!getName(device, DEVICE_NAME_LENGTH))
    {
        fprintf(stderr, "Erreur retour getName appelé par handleReadDevice()\n");
        return;
    }

    indexDevice = findDevice(park, device);

    if (indexDevice >=0)
        printDevice(&park->device[indexDevice]);
    else
        fprintf(stdout,"Equipement non trouvé\n");
}

void handleUpdateDevice(Park *park)
{
    // declaration variables points 1 et 2
    char device[DEVICE_NAME_LENGTH];
    int indexDevice;

    int userChoice = -1;
    bool runningMenu = true;
    int retry;

    // 1. Choix de l'équipement à modifier
    displayCrudMenu(DISPLAY_UPDATE);

        if(!getName(device, DEVICE_NAME_LENGTH))
    {
        fprintf(stderr, "Erreur retour getName appelé par handleUpdateDevice()\n");
        return;
    }

    if((indexDevice = findDevice(park, device)) == -1)
    {
        fprintf(stdout,"Equipement non trouvé\n");
        return;
    }

#if DEBUG
        printDevice(&park->device[indexDevice]);
#endif
        


    // 2. Choix de la partie de l'équipement à modifier
   
    while(runningMenu)
    {
        displayChoosePartOfDeviceToUpdate();
        getUserChoice(0,4,&userChoice);
        cleanBuffer();

        retry = 0;

        // TODO pointeurs de fonctions pour factoriser les appels répétitifs dans chaque case
        switch(userChoice)
        {
            case 0: 
                runningMenu = false;
                break;
                
            case 1: 

                do
                {
                   if(handleUpdateName(&park->device[indexDevice]) != SUCCESS)
                   {
                        printTryAgainChoice();
                        getUserChoice(0,1, &retry);
                        cleanBuffer();
                   }
                } while (retry);           
                break;
                
            case 2: 
                do
                {
                   if(handleUpdateType(&park->device[indexDevice]) != SUCCESS)
                   {
                        printTryAgainChoice();
                        getUserChoice(0,1, &retry);
                   }
                } while (retry);  
                break;
                
            case 3: 
                do
                {
                   if(handleUpdateAddressAndMask(&park->device[indexDevice]) != SUCCESS)
                   {
                        printTryAgainChoice();
                        getUserChoice(0,1, &retry);
                   }
                } while (retry);  
                break;
            
            case 4:
                 do
                {
                   if(handleUpdateStatus(&park->device[indexDevice]) != SUCCESS)
                   {
                        printTryAgainChoice();
                        getUserChoice(0,1, &retry);
                   }
                } while (retry);  
                break;
            
            default :
                fprintf(stderr, "Erreur switchcase handleUpdateDevice()\n");
        }
    }    
}

void handleRemoveDevice(Park *park)
{
    char deviceToBeRemoved[DEVICE_NAME_LENGTH];

    displayCrudMenu(DISPLAY_DELETE);

    if(!getName( deviceToBeRemoved, DEVICE_NAME_LENGTH))
    {
        fprintf(stderr, "Erreur retour getName appelé par handleRemoveDevice()\n");
        return;
    }

    if(removeDevice(park, deviceToBeRemoved))
        fprintf(stdout, "\nEquipement : %s retiré avec succès!\n", deviceToBeRemoved);
    else
        fprintf(stdout, "\nEquipement non trouvé\n");

}