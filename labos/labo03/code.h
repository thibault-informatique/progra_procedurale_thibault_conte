#ifndef CODE_H
#define CODE_H

#include <stdbool.h>

/***  OUTILS GENERATION CODE ***/

bool intToTab(int playerCode[], int number, int nbOfDigit);

int getCodeMaxValue(int codeLength);

bool isDigitDistinctInCode(int code[], short int tabLength);

void genRandomCode(int code[], short int tabLength);

void genHumanCode(int code[], short int tabLength);

#endif