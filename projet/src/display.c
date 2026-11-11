#include <stdio.h>

#include "../include/display.h"
#include "../include/compat.h"
#include "../include/device.h"

#define GREEN "\033[32m"
#define CYAN  "\033[36m"
#define BOLD  "\033[1m"
#define DIM   "\033[2m"
#define RESET "\033[0m"

/***  AFFICHAGE DES MENUS ***/


// creation via IA de la bannière PROJET
// programme en CLI "figlet" => transforme le texte en grand caractères dessinés
// ASCII Art
void displayMainPage(void)
{
    printf_s("\n" GREEN BOLD
        "  ____     ____      ___         _    _____    _____\n"
        " |  _ \\   |  _ \\    / _ \\       | |  | ____|  |_   _|\n"
        " | |_) |  | |_) |  | | | |   _  | |  |  _|      | |\n"
        " |  __/   |  _ <   | |_| |  | |_| |  | |___     | |\n"
        " |_|      |_| \\_\\   \\___/    \\___/   |_____|    |_|\n" RESET);

    printf_s(CYAN BOLD "\t\t    Network Manager\n" RESET);
    printf_s(CYAN "----------------------------------------------------\n" RESET);
    printf_s(DIM "  Progra Procédurale | Décembre 26 | Thibault Conte\n\n" RESET); 
    printf_s(BOLD "\t\t\t[ Menu ]\n" RESET);
    printf_s("   1) Gestion du parc     2) Recherche (filtre/tri)\n");
    printf_s("   3) Calculs réseau      4) Statistiques \n");
#if DEBUG
    puts("   5) test debug");
#endif 
    printf_s("   0) Quitter\n\n");

      /* Banniere Network (figlet standard) - conservee pour usage futur
    printf_s("\n" GREEN BOLD
        "  _   _            _                                   _\n"
        " | \\ | |    ___   | |_   __      __    ___     _ __   | | __\n"
        " |  \\| |   / _ \\  | __|  \\ \\ /\\ / /   / _ \\   | '__|  | |/ /\n"
        " | |\\  |  |  __/  | |_    \\ V  V /   | (_) |  | |     |   <
        " |_| \\_|   \\___|   \\__|    \\_/\\_/     \\___/   |_|     |_|\\_\\\n" RESET);
    */
}

void displayDevicesMenu(void)
{
    printf_s(CYAN BOLD "\n\t\t Gestion des appareils réseaux\n\n" RESET);    
    puts("   1) Ajouter un équipement    \t 2) Afficher un équipement");
    puts("   3) Modifier un équipement     4) Supprimer un équipement");
    puts("   5) Afficher le parc réseau");
    puts("\t\t 0) Revenir au menu principal");
}

void displayCrudMenu(Crud_display_choice crud)
{
    switch(crud)
    {
        case DISPLAY_CREATE:
            puts("Ajout d'un nouvel équipement");
            break;
        case DISPLAY_READ:
            puts("Quel équipement réseau voulez-vous afficher?");
            break;
        case DISPLAY_UPDATE:
            puts("Quel équipement réseau voulez-vous modifier?");
            break;
        case DISPLAY_DELETE:
            puts("Quel équipement réseau voulez-vous supprimer?");
            break;
        default :
            fprintf(stderr, "Erreur switchcase displayCrudMenu\n");
    }
     
}


void displayChoosePartOfDeviceToUpdate()
{
    printf_s(BOLD "\nChoix de l'élément à modifier\n\n" RESET);    
    puts("1) nom      2) type");
    puts("3) adresse et masque");
    puts("4) Statut");
    puts("0) Revenir au menu précédent\n");
}

void displayDeviceType()
{
    printf("Choisissez un type d'appareil :\n");
    puts("- ROUTER      [1]");
    puts("- SWITCH      [2]");
    puts("- FIREWALL    [3]");
    puts("- SERVER      [4]");
    puts("- WORKSTATION [5]");
    puts("- PRINTER     [6]");
    puts("- ACCES_POINT [7]");
    puts("- OTHER       [8]");
    puts("- UNKNOWN     [9]");
}

void displayDeviceStatus()
{
        printf("Choisissez un état/statut pour l'appareil:\n");
    puts("- ONLINE      [1]");
    puts("- OFFLINE     [2]");
    puts("- MAINTENANCE [3]");
    puts("- FAILED      [4]");
    puts("- UNKNOWN     [5]");
}

/***  AFFICHAGE AUTRE***/


static void printDeviceType(Device_type type)
{
    switch(type)
    {
        case ROUTER:
            puts("ROUTEUR");
            break;

        case SWITCH:
            puts("SWITCH");
            break;
        
        case FIREWALL:
            puts("FIREWALL");
            break;

        case SERVER :
            puts("SERVEUR");
            break;

        case WORKSTATION:
            puts("PC");
            break;

        case PRINTER :
            puts("IMPRIMANTE");
            break;

        case ACCESS_POINT :
            puts("POINT D'ACCES");
            break;

        case OTHER :
            puts("AUTRE");
            break;

        case UNKNOWN :
            puts("INCONNU");
            break;

        default:
            fprintf(stderr,"Erreur switch case printDeviceType");
            break;
        
    }
}

static void printDeviceStatus(Device_status status)
{
    switch(status)
    {
        case STATUS_ONLINE :
            puts("en ligne");
            break;

        case STATUS_OFFLINE :
            puts("hors ligne");
            break;

        case STATUS_MAINTENANCE :
            puts("en maintenance");
            break;

        case STATUS_FAILED :
            puts("erreur");
            break;

        case STATUS_UNKNOWN :
            puts("inconnu");
            break;

        default:
            fprintf(stderr, "Erreur switch case printDeviceStatus");
            break;

    }
}

void printAddressError(Return_code code)
{
    switch(code)
    {
        case ERR_PUBLIC_IP:
            fprintf(stdout,"Erreur: c'est une adresse IPv4 publique.\n"); 
            break;
        case ERR_IS_NETWORK_ADDRESS:
            fprintf(stdout,"Erreur: c'est l'adresse du réseau.\n");
            break;
        case ERR_IS_BROADCAST:
            fprintf(stdout,"Erreur: c'est l'adresse de broadcast.\n");
            break;
        case ERR_INVALID_MASK:
            fprintf(stdout,"Erreur masque réseau invalide\n");
            break;
        default :
            fprintf(stderr,"Erreur switchase printAddressError()\n");
    }
}

void printTryAgainChoice()
{
    printf("Voulez-vous retenter la mise à jour? \n");
    puts("[1] réessayer");
    puts("[0] annuler");
}

void printAskConfirmation()
{
    printf("Voulez-vous valider ? [o]/[n]: ");
}

// conversion ipv4 32 bits ou Hexxa en base 10, human readable
// A revoir les conditions binaires
// >> fait descendre les bits de gauche vers la D
// & 0xFF (mask) ne garde que les 8 derniers bits (sécurité si il y avait malgré tout des bits de poids forts parasites suppl)
void printDecimalIpv4(uint32_t address)
{
    printf("%u.%u.%u.%u\n", 
          (address >> 24) & 0xFFu,
          (address >> 16) & 0xFFu,
          (address >> 8)  & 0xFFu,
           address        & 0xFFu);
}

void printHexaIpv4(uint32_t address)
{
    printf("%02X.%02X.%02X.%02X\n",
          (address >> 24) & 0xFFu,
          (address >> 16) & 0xFFu,
          (address >> 8)  & 0xFFu,
           address        & 0xFFu);

    // variante
    // printf("%#x", address);
}

void printDevice(const Device *device)
{    
    printf("\nNom:     %s\n", device->name);
    printf("Type:    ");
    printDeviceType(device->type);
    printf("Adresse: ");
    printDecimalIpv4(device->ipAddress.address);
    printf("Masque:  ");
    printDecimalIpv4(device->subnet_mask.address);
    printf("Statut:  ");
    printDeviceStatus(device->status);
    putc('\n', stdout);
}

void displayPark(Park *park)
{
    for (int i = 0; i< park->nbOfDevice; i++)
    {
        printf(BOLD "Equipement n°%d\n" RESET, i + 1);
        printDevice(&park->device[i]);
    }
}