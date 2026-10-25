#ifndef JEU_H
#define JEU_H

#include <stdbool.h>

// affichage couleurs / bold console
#define GREEN "\033[32m" 
#define YELLOW "\033[33m"
#define BOLD  "\033[1m"
#define RESET "\033[0m"

/*** AFFICHAGE  ***/
void printMenu();

/*** MECANIQUES DE JEU ***/

// fonction + performante et sécurisée que scanf (recup saisie user pour un unsigned int), via IA pour tests et sécurité
int getUserChoice(unsigned int minValue, unsigned int maxValue);

/*** DIFFERENTS TYPES DE JEU ***/

void classicGame();
void customGame();
void gameAgainstHuman();

#endif