#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "network.h"
#include "compat.h"
#include "display.h"
#include "constants.h"

// TODO isValidIp, isValidMask, isPrivateIp 
bool isValidIp(Ipv4_t ip)
{
    return true;
}

bool isValidMask(Ipv4_t subnet_mask)
{
    return true;
}

// 10.0.0.0 à 10.255.255.255
// 172.16.0.0 à 172.31.255.255
// 192.168.0.0 à 192.168.255.255
bool isPrivateIp(Ipv4_t ip)
{
    return true;
}

// saisie user 'o' pour oui 'n' pour non
bool confirmation()
{
    askConfirmation();

    int answer = '\0';
    int c = '\0';

    do
    {
        answer = getchar();

        if (answer == EOF)
        {
            fprintf(stderr, "Erreur flux d'entrée\n");
            exit(EXIT_FAILURE);
        }

    } while (answer != 'o' && answer != 'n');

    // purger buffer
    while ((c = getchar()) != '\n' && c != EOF);

#if DEBUG
    printf(" char answer vaut dans confirmation : %c\n", answer);
    printf("bool answer dans confirmation : %d\n", answer == 'o');
#endif
    return answer == 'o';
}

// obtenir adresse IPv4 en Hexa via user + vérif
// plage autorisée par défaut par l'uint32_t est 
// en Hexa de 0X00.00.00.00 à 0XFF.FF.FF.FF

// aide IA pour saisie sécurisée
uint32_t setHexaIPv4Address()
{
    uint32_t address = 0;
    bool isWrong = true;
    bool userApproval = false;

    // 8 caractères pour ip en Hexa + \n + \0
    char buffer[10] = "";

    do
    {
        printf("\nEncodez une adresse IPv4 en Hexa (ex: C0A80101):\n");
        printf("Les 0 de poids fort peuvent être omis (ex: FF pour O0...FF): ");

        // étape 1: lecture donnée et vérif stdin ouvert
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
             // flux ferme (Ctrl+D, redirection) : on sort, sinon boucle infinie
            fprintf(stderr, "Erreur flux d'entrée\n");
            exit(EXIT_FAILURE);
        }

        // etape 2 : purge si la saisie depassait le buffer
        if (strchr(buffer, '\n') == NULL)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

        // étape 3 on détecte le '\n capturé dans la string et on la remplace par le caractère fin de string
        buffer[strcspn(buffer,"\n")] = '\0';

        // étape 4 vérif longueur de la chaine adéquate et pas de caractères interdits 
        // + conversion string vers hexa
        // 2e para de strtoul permet de savoir quel est le premier caractère non convertissable par stroul
        // ici chaine nettoyée avant
        size_t len = strlen(buffer);
        if(len >= 1 && len <= 8 &&
           strspn(buffer,"0123456789abcdefABCDEF") == len)
        {
            address = (uint32_t)strtoul(buffer, NULL, 16);     
            isWrong = false;

            printHexaIPv4(address);
            userApproval = confirmation();

#if DEBUG
    printf("Valeur debug userApproval dans setHexaIPv4 : %d\n", userApproval);
#endif
            if(!userApproval)
                puts("Veuillez recommencer");
        }       
            
        else
        {
            isWrong = true;
            fprintf(stderr, "Erreur: 1 à 8 chiffres[0-9] et lettres [a-f/A-F] attendus pour l'adresse en hexa\n");
        }   

    } while (isWrong || !userApproval);   


    return address;
}

// obtenir addresse IPv4 via encodage octet par octet (192.168.1.1)
// fonction + performante et sécurisée que scanf , via IA pour tests et sécurité
/*uint32_t getDecimalIPv4Address()
{
    uint32_t address;
    bool isValid = false;

    do
    {
        // etape 1 : lecture
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            // flux ferme (Ctrl+D, redirection) : on sort, sinon boucle infinie
            fprintf(stderr, "Fin de flux d'entree\n");
            exit(EXIT_FAILURE);
        }

        // etape 2 : purge si la saisie depassait le buffer
        if (strchr(buffer, '\n') == NULL)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

        // etape 3 : validation
        isValid = (sscanf_s(buffer, "%hu", &userChoice) == 1) &&
                  (userChoice >= minValue)                    &&
                  (userChoice <= maxValue);

        if (!isValid)
            fprintf(stderr, "Format attendu : 1 chiffre compris entre %hu et %hu\n", minValue, maxValue);
    } while (!isValid);

    return address;
}*/