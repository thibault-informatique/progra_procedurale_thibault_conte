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

    printf_s(CYAN BOLD "Network Manager\n" RESET);
    printf_s(CYAN "----------------------------------------------------\n" RESET);
    printf_s(DIM "  Progra Procédurale | Décembre 26 | Thibault Conte\n\n" RESET); 
    printf_s(BOLD "\t\t\t [ Menu ]\n" RESET);
    printf_s("   1) Gestion des équipements      2) Recherche d'un élément\n");
    printf_s("   3) Calculs réseau               4) Stats \n");
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

void displayHandlingDevicesMenu(void)
{
    printf_s(CYAN BOLD "\n\t\t  Gestion des appareils réseaux\n" RESET);    
    puts("   1) Ajouter un équipement    2) Rechercher un équipement");
    puts("   3) Modifier un équipement   4) Supprimer un équipement");
    puts("   5) Afficher le parc réseau");
    puts("\t\t  0) Revenir au menu principal");
}

void displayCrudMenu(Crud_display_choice crud)
{
    switch(crud)
    {
        case DISPLAY_CREATE:
            puts("Ajout d'un nouvel équipement");
            break;
        case DISPLAY_READ:
            puts("Quel équipement réseau voulez-vous afficher");
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

void printHexaIPv4(uint32_t address)
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