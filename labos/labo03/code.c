#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "code.h"

// on génère les chiffres du code 1 par 1
// il faut que chaque nouveau chiffre soit différents des autres
void genRandomCode(int code[], short int tabLength)
{
    assert(code != NULL && tabLength > 0);

    for(int i = 0; i < tabLength ; i++)
    {       
        do
        {
            code[i] = rand() % 10;
            
        }while(!isDigitDistinctInCode(code, i + 1));    
    }  
}

// vérification du code: chaque chiffre est bien différent des autres?
// si doublon => la fct retourne false
bool isDigitDistinctInCode(int code[], short int tabLength)
{
    assert(code != NULL && tabLength > 0);

    // on vérifie chaque chiffre de G à D avec tous ses voisin de D
    for (int i = 0; i < tabLength; i++)
        for(int j = i + 1; j < tabLength; j++)
        {
            if(code[i] == code[j])
                return false;
        }
    return true;
}