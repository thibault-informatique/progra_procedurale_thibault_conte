#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "debug.h"
#include "jeu.h"

void printCode(int code[], short int tabLength)
{
    assert(code != NULL && tabLength > 0);

    for(int i = 0; i < tabLength ; i++)
    {
        printf("%d", code[i]);
    }
    putc('\n', stdout);
}