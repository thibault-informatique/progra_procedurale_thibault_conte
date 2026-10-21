#ifndef JEU_H
#define JEU_H


void printMenu();

void printValuesPositionsCounter(const int *goodPosition, const int *wrongPosition);

short int getUserChoice(unsigned short int minValue, unsigned short int maxValue);

int* intToTab(int number, int nbOfDigit);

void updatePositionsCounters(const int trueCode[], const int playerCode[], int codeLength, int *goodPosition, int *wrongPosition);

bool playerWin( const int * goodPosition, int codeLength);

void classicGame();



#endif