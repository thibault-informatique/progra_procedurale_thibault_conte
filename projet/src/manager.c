#include <stdio.h>

#include "../include/manager.h"
#include "../include/display.h"

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

void handlingDeviceMenu(Park *park)
{
    int userChoice = -1;
    bool runningMenu = true;
    while(runningMenu)
    {
        displayHandlingDevicesMenu();
        getUserChoice(0,4,&userChoice);

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
                break;
            
            default :
                fprintf(stderr, "Erreur switchcase handlingDeviceMenu()\n");
        }
    }
}