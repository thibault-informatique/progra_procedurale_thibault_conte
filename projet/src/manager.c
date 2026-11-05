#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../include/manager.h"
#include "../include/display.h"

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
                handleUpdateDEvice(park);
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

void handleUpdateDEvice(Park *park)
{
    // declaration variables points 1 et 2
    char device[DEVICE_NAME_LENGTH];
    int indexDevice;

    int userChoice = -1;
    bool runningMenu = true;

    // 1. Choix de l'équipement à modifier
    displayCrudMenu(DISPLAY_UPDATE);

        if(!getName(device, DEVICE_NAME_LENGTH))
    {
        fprintf(stderr, "Erreur retour getName appelé par handleReadDevice()\n");
        return;
    }

    if(indexDevice = findDevice(park, device) == -1)
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
        getUserChoice(0,5,&userChoice);
        cleanBuffer();

        switch(userChoice)
        {
            case 0: 
                runningMenu = false;
                break;
                
            case 1: 
                // modifier nom
                break;
                
            case 2: 
                // modifier type
                break;
                
            case 3: 
                // modifier adresse
                break;
                
            case 4: 
                // modifier masque
                break;
            
            case 5:
                //modifier statut
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