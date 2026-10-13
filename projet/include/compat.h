#ifndef COMPAT_H
#define COMPAT_H

#include <stdio.h>

/*
 * printf_s / sscanf_s font partie de l'Annexe K (C11), implementee par MSVC
 * mais PAS par glibc (Fedora/Ubuntu/...). Sur les systemes non-Windows on
 * les remplace simplement par printf / sscanf.
 */
#ifndef _WIN32
    #define printf_s printf
    #define sscanf_s   sscanf
#endif

#endif
