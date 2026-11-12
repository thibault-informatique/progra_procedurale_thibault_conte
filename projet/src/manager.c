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
        printf("   Votre choix: ");
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

    cleanBuffer();

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

/*** HANDLERS CREATE - UPDATE ***/

Return_code handleCreateDevice(Device *device)
{
    assert (device != NULL);

    int milestone = 1;
    Return_code result;

     // 1 choix nom
    displayCreateDeviceMenu(milestone);
    result = handleCreateOrUpdateName(device);

    // si échoue on quitte la fonction et renvoie le return code à l'appelant
    if (result != SUCCESS)
        return result;

    milestone++;

    // choix type appareil
    displayCreateDeviceMenu(milestone);
    result = handleCreateOrUpdateType(device);

    if (result != SUCCESS)
        return result;

    // choix adresse appareil et masque
    result = handleCreateOrUpdateAddressAndMask(device);
   
    if (result != SUCCESS)
        return result;

    milestone++;

    // choix statut
    displayCreateDeviceMenu(milestone);
    result = handleCreateOrUpdateStatus(device);

    return result;
}

Return_code handleCreateOrUpdateName(Device *device)
{
    assert(device != NULL);
    
    char newName[DEVICE_NAME_LENGTH];

    if(!getName(newName, DEVICE_NAME_LENGTH))
        return ERR_STR_LENGTH;


    Return_code result = setDeviceName(device, newName);

    switch(result)
    {
        case SUCCESS :
            fprintf(stdout,"Nom ajouté/modifié avec succès!\n");
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
Return_code handleCreateOrUpdateType(Device *device)
{
    assert(device != NULL);

    setDeviceType(device, setType());

    return SUCCESS;
}

Return_code handleCreateOrUpdateAddressAndMask(Device *device)
{
    assert(device != NULL);

    Ipv4 newAddress = {0};
    Ipv4 newMask    = {0};

    displaySetDecimalIpv4Address();

    // saisie de la nouvelle adresse IP
    fprintf(stdout, "- pour l'appareil:\n");
    Return_code result = setDecimalIpv4Address(&newAddress);

    // saisie du nouveau masque si l'info précédente est correcte
    if(result == SUCCESS)
    {
        fprintf(stdout, "\n- le masque de sous-réseau:\n");
        result = setDecimalIpv4Address(&newMask);
    }

    // idem pour attribuer l'adresse et le masque : seulement si les 2 attributions précédentes = succès
    if(result == SUCCESS)
        result = setDeviceIpAddressAndMask(device, newAddress, newMask);

    return result;
}

// return_code peu utile mais pour respecter le même style
Return_code handleCreateOrUpdateStatus(Device *device)
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
                handleAddDevice(park);
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

void handleAddDevice(Park *park)
{
    assert (park != NULL);

    Device temp = {0};
    Return_code result;

    /*** A création de l'appareil ***/
    result = handleCreateDevice(&temp);

    if (result != SUCCESS)
    {
        fprintf(stdout, "\nErreur lors de la création de l'appareil\n");
        displayMessageReturnCode(result);
        return;
    }

#if DEBUG
    printDevice(&temp);
#endif

    /*** Ajout au parc ***/
    if((result = addDevice(park, &temp)) == ERR_PARK_FULL)
        fprintf(stdout, "\nAjout impossible : parc plein\n");
    else if(result == SUCCESS)
        fprintf(stdout, "\nAppareil ajouté avec succès!\n");
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
            Return_code result;

            case 0: 
                runningMenu = false;
                break;
                
            case 1: 

                do
                {
                   if((result = handleCreateOrUpdateName(&park->device[indexDevice])) != SUCCESS)
                   {
                        displayMessageReturnCode(result);
                        printTryAgainChoice();
                        getUserChoice(0,1, &retry);
                        cleanBuffer();
                   }
                } while (retry);           
                break;
                
            case 2: 
                do
                {
                   if((result = handleCreateOrUpdateType(&park->device[indexDevice])) != SUCCESS)
                   {
                        displayMessageReturnCode(result);
                        printTryAgainChoice();
                        getUserChoice(0,1, &retry);
                        cleanBuffer();
                   }
                } while (retry);  
                break;
                
            case 3: 
                do
                {
                   if((result = handleCreateOrUpdateAddressAndMask(&park->device[indexDevice])) != SUCCESS)
                   {
                        displayMessageReturnCode(result);
                        printTryAgainChoice();
                        getUserChoice(0,1, &retry);
                        cleanBuffer();
                   }
                } while (retry);  
                break;
            
            case 4:
                 do
                {
                   if((result = handleCreateOrUpdateStatus(&park->device[indexDevice])) != SUCCESS)
                   {
                        displayMessageReturnCode(result);
                        printTryAgainChoice();
                        getUserChoice(0,1, &retry);
                        cleanBuffer();
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