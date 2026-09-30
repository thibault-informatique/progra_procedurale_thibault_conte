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

