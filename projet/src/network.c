#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "network.h"
#include "display.h" 
#include "manager.h"

static bool isDecimalBetween0And255(const int nb);
static bool isNetworkAddress(Ipv4 address, Ipv4 mask);
static bool isBroadcastAddress(Ipv4 address, Ipv4 mask);
static bool isLoopBackIPv4Address(Ipv4 address);
static bool isLinkLocalIPv4Address(Ipv4 address);
static bool isTestNetIPv4Address(Ipv4 address);
static bool isExperimentalAddress(Ipv4 address);
static bool isMulticastAddress(Ipv4 address);
static bool isLimitedBroadcast(Ipv4 address);
static bool isThisNetworkAddress(Ipv4 address);

// octet reçu (int) compris entre 0 et 255 => utilisé dans les saisies IPv4 en décimal
static bool isDecimalBetween0And255(const int nb)
{
    return nb >= 0 && nb <= 255;
}

// IP valide si n'est pas une adresse IPv4 spéciale et si adresse locale
Return_code checkLocalAddress(Ipv4 ip, Ipv4 mask)
{
    if(!isPrivateIPv4Address(ip))
        return ERR_PUBLIC_IP;

    if(isNetworkAddress(ip, mask))
        return ERR_IS_NETWORK_ADDRESS;

    if(isBroadcastAddress(ip, mask))
        return ERR_IS_BROADCAST;
    
    return SUCCESS;
}

// vérifie si la nouvelle adresse IP fait partie du réseau renseigné
bool isSameSubnet(Ipv4 newIp, Ipv4 mask, Ipv4 networkAddress)
{
    if((newIp.address & mask.address) == networkAddress.address)
        return true;
    else
        return false;
}

// obtenir l'adresse du réseau
Return_code getNetworkAddress(Ipv4 ip, Ipv4 mask, Ipv4 *networkAddress)
{
    assert(networkAddress != NULL);

    if(!isValidMask(mask))
    {
        return ERR_INVALID_MASK;
    }

    networkAddress->address = ip.address & mask.address;

    return SUCCESS;
}

// seuls les bits de poids le plus fort valent 1 et ce de façon contiguë
// si un seul bit vaut 1 après le préfixe c'est qu'il y a une erreur de masque
// on rejete 0.0.0.0/0
bool isValidMask(Ipv4 subnet_mask)
{
    if(subnet_mask.address == 0)
        return false;

    unsigned short prefix = translateMaskInPrefix(subnet_mask);

    if(prefix == 0)
        return false;

    for(int i = 31 - prefix; i >= 0; i--)
        if (subnet_mask.address & (1u << i))
            return false;
    
    return true;
}

// tous les bits de l'hôte sont-ils à zéro?
// 1) extraire les bits partie l'hôte
// 2) vérifier si = à 0
static bool isNetworkAddress(Ipv4 address, Ipv4 mask)
{
    return (address.address & ~mask.address) == 0;
}

// tous les bits de l'hôte sont-ils à 1?
// 1) extraire les bits partie l'hôte
// 2) vérifier si tous bits de la partie hôte = 1 ou = à l'inverse du masque réseau
static bool isBroadcastAddress(Ipv4 address, Ipv4 mask)
{
    return (address.address & ~mask.address) == ~mask.address;
}


// 10.0.0.0 à 10.255.255.255
// 172.16.0.0 à 172.31.255.255
// 192.168.0.0 à 192.168.255.255
bool isPrivateIPv4Address(Ipv4 address)
{
    return  (address.address >= IPV4(10,0,0,0)    && address.address <= IPV4(10,255,255,255)) ||
            (address.address >= IPV4(172,16,0,0)  && address.address <= IPV4(172,31,255,255)) ||
            (address.address >= IPV4(192,168,0,0) && address.address <= IPV4(192,168,255,255));
}

static bool isLoopBackIPv4Address(Ipv4 address)
{
    return (address.address >= IPV4(127,0,0,0) && address.address <= IPV4(127,255,255,255));
}

static bool isLinkLocalIPv4Address(Ipv4 address)
{
    return (address.address >= IPV4(169,254,0,0) && address.address <= IPV4(169,254,255,255));
}


static bool isTestNetIPv4Address(Ipv4 address)
{
            // TEST-NET 1
    return (address.address >= IPV4(192,0,2,0) && address.address <= IPV4(192,0,2,255)) ||
            // TEST-NET 2 et 3 (ajout IA)
           (address.address >= IPV4(198,51,100,0) && address.address <= IPV4(198,51,100,255)) ||
           (address.address >= IPV4(203,0,113,0) && address.address <= IPV4(203,0,113,255));
}

static bool isExperimentalAddress(Ipv4 address)
{
    return (address.address >= IPV4(240,0,0,0) && address.address <= IPV4(255,255,255,254));
}

static bool isMulticastAddress(Ipv4 address)
{
    return (address.address >= IPV4(224,0,0,0) && address.address <= IPV4(239,255,255,255));
}

static bool isLimitedBroadcast(Ipv4 address)
{
    return address.address == IPV4(255,255,255,255);
}

static bool isThisNetworkAddress(Ipv4 address)
{
    return address.address < IPV4(1,0,0,0);
}

// compte le nbre de bits de poids fort contigüs à 1
unsigned short translateMaskInPrefix(Ipv4 mask)
{
    unsigned int prefix = 0;

    // si bit à 1 dans l'adresse => on incrémente le préfixe
    // sinon si bit à 0: on est à la fin du masque
    for(int i = 31; i >= 0 ; i--)
        if (mask.address &  (1u << i))
            prefix++;
        else
            break;

    return prefix;
}

// saisie user 'o' pour oui 'n' pour non
bool userConfirmInput()
{
    printAskConfirmation();

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
uint32_t setHexaIpv4Address()
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

            printHexaIpv4(address);
            userApproval = userConfirmInput();

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

// obtenir addresse IPv4 via encodage avec '.' (192.168.1.1)
// fonction + performante et sécurisée que scanf , via IA pour tests et sécurité
Return_code setDecimalIpv4Address(Ipv4 *newIp)
{
    assert (newIp != NULL);

    char buffer[17] = "";
    int octet1;
    int octet2;
    int octet3;
    int octet4;

    int pos;

    // etape 1 : lecture
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        // flux ferme (Ctrl+D, redirection) : on sort, sinon boucle infinie
        fprintf(stderr, "Fin de flux d'entree\n");
        exit(EXIT_FAILURE);
    }

    // etape 2 : purge si la saisie depassait le newAddress
    if (strchr(buffer, '\n') == NULL)
    {
        cleanBuffer();
        return ERR_STR_LENGTH;
    }

    // etape 3 : recup des 4 octets depuis le tab de char buffer
    // %n récupère le nbre de caractère consommé par sscanf
    // si nbre de caractère < taille buffer alors il reste des éléments excédentaires
    if(sscanf(buffer, "%d.%d.%d.%d%n", &octet1, 
                                        &octet2, 
                                        &octet3, 
                                        &octet4,
                                        &pos) != 4)
        return ERR_INVALID_DECIMAL_ADDRESS;
    
    // étape 4: on détecte le '\n capturé dans la string et on la remplace par le caractère fin de string
    buffer[strcspn(buffer,"\n")] = '\0';

    // étape 5: si buffer plus grand que pos alors saisie user trop grande
    if(pos != strlen(buffer))
        return ERR_INVALID_DECIMAL_ADDRESS;

    // etape 6 : vérifier que chaque octet soit compris dans la plage autorisée 0 à 255
    if(!isDecimalBetween0And255(octet1) ||
       !isDecimalBetween0And255(octet2) ||
       !isDecimalBetween0And255(octet3) ||
       !isDecimalBetween0And255(octet4))
        return ERR_OCTET_SIZE;
    else
        newIp->address = IPV4(octet1, octet2, octet3, octet4);

    return SUCCESS;
}