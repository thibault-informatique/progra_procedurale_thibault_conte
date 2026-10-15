#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

// fonction de log généraliste en CLI avec para variable
void ecrireLog(FILE* flux, const char* message,...);

// fct log qui affiche date et heure
void logHoroDate(FILE* flux);

void logDebutProg(FILE* flux);

void logFinProg(FILE* flux);

#endif