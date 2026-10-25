#ifndef CODE_H
#define CODE_H

#include <stdbool.h>

/***  OUTILS GENERATION CODE ***/

// transformer un code (nombre) depuis un integer vers un tableau de n digits (playerCode)
bool intToTab(int playerCode[], int number, int nbOfDigit);

// calcul valeur maximale du code en fonction du nbre de digits
int getCodeMaxValue(int codeLength);

// vérification du code: chaque chiffre est bien différent des autres? true : false
bool isDigitDistinctInCode(int code[], short int tabLength);

// génération aléatoire d'un code stocké dans un tableau de int (1 chiffre à la fois)
void genRandomCode(int code[], short int tabLength);

// génération du code par un autre joueur humain (stockage tab int)
void genHumanCode(int code[], short int tabLength);

/***  HISTORIQUE DU CODE ***/

void printHistoryCode(int nbOfTries, int codeLength, const int historyCode[][codeLength]);

#endif