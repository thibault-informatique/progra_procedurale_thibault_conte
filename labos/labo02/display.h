#ifndef DISPLAY_H
    #define DISPLAY_H

#include <stdbool.h>

#include "constants.h"

void printMenu();

void printGameBoard(const bool gameBoard[][COLUMN_NB], const bool dataBoard[][COLUMN_NB]);

void printDataBoard(const bool dataBoard[][COLUMN_NB]);

#endif