#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "code.h"
#include "jeu.h"

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

void genHumanCode(int code[], short int tabLength)
{
    assert(code != NULL && tabLength > 0);

    int intCode = 0;
    bool distinctCode = false;

    printf("Veuillez choisir le code à %hd chiffres distincts pour le joueur: ", tabLength);
    do
    {
        intCode = getUserChoice(0, getCodeMaxValue(tabLength));

        if(!intToTab(code, intCode, tabLength))
            {
                fprintf(stderr, "Erreur fct intToTab dans fct genHumanCode\n");
                exit(EXIT_FAILURE);
            }
            
        distinctCode = isDigitDistinctInCode(code, tabLength);

        if(!distinctCode)
            printf("Attention le code doit contenir %d chiffres différents, recommencez.\n", tabLength);

    }while(!distinctCode);    
}

int getCodeMaxValue(int codeLength)
{
    int maxValue = 1;

    for (int i = 0; i < codeLength; i++)
        maxValue *= 10;

    return --maxValue;
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