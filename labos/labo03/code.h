#ifndef CODE_H
#define CODE_H

#include <stdbool.h>



void genRandomCode(int code[], short int tabLength);

// vérification du code: chaque chiffre est bien différent des autres?
bool isDigitDistinctInCode(int code[], short int tabLength);

#endif