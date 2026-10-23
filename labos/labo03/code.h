#ifndef CODE_H
#define CODE_H

#include <stdbool.h>



void genRandomCode(int code[], short int tabLength);

void genHumanCode(int code[], short int tabLength);

int getCodeMaxValue(int codeLength);

// vérification du code: chaque chiffre est bien différent des autres?
bool isDigitDistinctInCode(int code[], short int tabLength);

#endif