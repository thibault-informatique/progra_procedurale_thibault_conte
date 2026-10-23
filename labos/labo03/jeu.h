#ifndef JEU_H
#define JEU_H

#include <stdbool.h>

#define GREEN "\033[32m"
#define RED   "\033[33m"
#define BOLD  "\033[1m"
#define RESET "\033[0m"

/*** AFFICHAGE  ***/
void printMenu();

void printValuesPositionsCounter(const int *goodPosition, const int *wrongPosition);

void printResultGame(bool victory, int nbOfTries);

void clearScreen();


/*** MECANIQUES DE JEU ***/
bool launchGame(int codeLength, int maxTries, int *nbOfTries, bool gameAgainstHuman);

int getUserChoice(unsigned int minValue, unsigned int maxValue);

bool getUserChoiceOrCommand(unsigned int minValue, unsigned int maxValue, char commandChar, int *choice);

bool hasPlayerWin(const int * goodPosition, int codeLength);

void updatePositionsCounters(const int trueCode[], const int playerCode[], int codeLength, int *goodPosition, int *wrongPosition);

/*** DIFFERENTS TYPES DE JEU ***/

void classicGame();

void customGame();

void gameAgainstHuman();

#endif