#include <stdio.h>
#include "display.h"
#include "compat.h"

#define GREEN "\033[32m"
#define CYAN  "\033[36m"
#define BOLD  "\033[1m"
#define DIM   "\033[2m"
#define RESET "\033[0m"

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

    printf_s(CYAN BOLD "\t\t  Network Manager\n" RESET);
    printf_s(CYAN "----------------------------------------------------\n" RESET);
    printf_s(DIM "  Progra Procédurale | Décembre 26 | Thibault Conte\n\n" RESET); 
    printf_s(BOLD "  [ Menu ]\n" RESET);
    printf_s("   1) Gestion des équipements      2) Recherche d'un élément\n");
    printf_s("   3) Calculs réseau               4) Stats \n");
    printf_s("\n   0) Quitter\n");

      /* Banniere Network (figlet standard) - conservee pour usage futur
    printf_s("\n" GREEN BOLD
        "  _   _            _                                   _\n"
        " | \\ | |    ___   | |_   __      __    ___     _ __   | | __\n"
        " |  \\| |   / _ \\  | __|  \\ \\ /\\ / /   / _ \\   | '__|  | |/ /\n"
        " | |\\  |  |  __/  | |_    \\ V  V /   | (_) |  | |     |   <
        " |_| \\_|   \\___|   \\__|    \\_/\\_/     \\___/   |_|     |_|\\_\\\n" RESET);
    */
}

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

// conversion ipv4 32 bits en 
// TODO à comprendre et relire
// >> fait descendre les bits de gauche ; & 0xFF ne garde que les 8 derniers
// & masque qui garde les 8 bits de droite, les autres sont mis à 0
static void printIpv4(Ipv4_t ip)
{
    uint32_t a = ip.address;
    printf("%u.%u.%u.%u",
           (a >> 24) & 0xFFu,   // 1er octet
           (a >> 16) & 0xFFu,   // 2e
           (a >>  8) & 0xFFu,   // 3e
           a & 0xFFu);          // 4e
    putc('\n', stdout);
}

void displayDevice(Device device)
{    
    printf("\nNom:     %s\n", device.name);
    printf("Type:    ");
    printDeviceType(device.type);
    printf("Adresse: ");
    printIpv4(device.ip);
    printf("Masque:  ");
    printIpv4(device.subnet_mask);
    printf("Statut:  ");
    printDeviceStatus(device.status);
    putc('\n', stdout);
}

void displayPark(Device park[], int tabLength)
{
    for (int i = 0; i< tabLength; i++)
    {
        printf(BOLD "Equipement n°%d\n" RESET, i + 1);
        displayDevice(park[i]);
    }
}
