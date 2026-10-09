#include <stdio.h>
#include <stdarg.h>

#include "utils.h"

// ecrire log en utilisant printf car accepte différents paramètres grâce à vprintf() )
void ecrireLog(FILE* flux, const char* message,...)
{
    va_list ap; // 1.decla liste arg
    
    va_start(ap, message); // 2. init liste arg

    vfprintf(flux, message, ap);
    va_end(ap);
}

void logHoroDate(FILE* flux)
{
    ecrireLog(flux, "date: %s | heure: %s\n", __DATE__, __TIME__);
}

void logDebutProg(FILE* flux)
{
    fputs("\nDébut programme", flux);
    logHoroDate(flux);
}

void logFinProg(FILE* flux)
{
    fputs("\nFin du programme", flux);
    logHoroDate(flux);
}