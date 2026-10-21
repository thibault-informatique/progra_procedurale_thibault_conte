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

void testIntToTab(int number, int nbOfDigit)
{
    printf("intToTab(%d, %d) -> ", number, nbOfDigit);

    int *t = intToTab(number, nbOfDigit);
    if (t == NULL)
    {
        printf("NULL\n");
        return;
    }

    printCode(t, nbOfDigit);
    free(t);
}