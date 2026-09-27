#ifndef GAMEPLAY_H
    #define GAMEPLAY_H
#include <stdbool.h>
#include "constants.h"

void initBoard(bool board[][COLUMN_NB]);

unsigned short int getUserChoice(unsigned short int minValue, unsigned short int maxValue);

void setRandomBombInDataBoard(bool dataBoard[][COLUMN_NB]);

void setManualBombInDataBoard(bool dataBoard[][COLUMN_NB]);

void gameAgainstComputer(bool gameBoard[][COLUMN_NB], bool dataBoard[][COLUMN_NB]);

void gameAgainstHuman(bool gameBoard[][COLUMN_NB], bool dataBoard[][COLUMN_NB]);

#endif