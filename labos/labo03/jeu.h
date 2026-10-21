#ifndef JEU_H
#define JEU_H

#define GREEN "\033[32m"
#define RED   "\033[33m"
#define BOLD  "\033[1m"
#define RESET "\033[0m"


void printMenu();

void printValuesPositionsCounter(const int *goodPosition, const int *wrongPosition);

short int getUserChoice(unsigned short int minValue, unsigned short int maxValue);

bool intToTab(int playerCode[], int number, int nbOfDigit);

void updatePositionsCounters(const int trueCode[], const int playerCode[], int codeLength, int *goodPosition, int *wrongPosition);

bool hasPlayerWin(const int * goodPosition, int codeLength);

void classicGame();

void customGame();

bool launchGame(int codeLength, int maxTries, int *nbOfTries);


#endif