#ifndef JEU_H
#define JEU_H


void printMenu();

short int getUserChoice(unsigned short int minValue, unsigned short int maxValue);

void classicGame();

void genRandomCode(int code[], short int tabLength);

#endif