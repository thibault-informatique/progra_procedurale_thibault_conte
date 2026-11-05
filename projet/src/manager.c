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
            fprintf(stdout, "Le nom doit contenir au moins une lettre\n");
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

void handlingDeviceMenu(Park *park)
{
    int userChoice = -1;
    bool runningMenu = true;
    while(runningMenu)
    {
        displayHandlingDevicesMenu();
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
                break;
                
            case 3: 
                break;
                
            case 4: 
               handlingRemoveDevice(park);
                break;
            
            case 5:
                displayPark(park);
                break;
            
            default :
                fprintf(stderr, "Erreur switchcase handlingDeviceMenu()\n");
        }
    }
}

void handlingRemoveDevice(Park *park)
{
    char deviceToBeRemoved[DEVICE_NAME_LENGTH];

    displayCrudMenu(DISPLAY_DELETE);

    if(!getName( deviceToBeRemoved, DEVICE_NAME_LENGTH))
    {
        fprintf(stderr, "Erreur retour getName appelé par handlingRemoveDevice()\n");
        return;
    }

    if(removeDevice(park, deviceToBeRemoved))
        fprintf(stdout, "\nEquipement : %s retiré avec succès!\n", deviceToBeRemoved);
    else
        fprintf(stdout, "\nEquipement non trouvé\n");

}