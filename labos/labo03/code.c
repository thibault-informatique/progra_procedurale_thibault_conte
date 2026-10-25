#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "code.h"
#include "jeu.h"

/****************************
      SOMMAIRE DE code.c 
*****************************/


/***  OUTILS GENERATION CODE ***/

bool intToTab(int playerCode[], int number, int nbOfDigit);

int getCodeMaxValue(int codeLength);

bool isDigitDistinctInCode(int code[], short int tabLength);

void genRandomCode(int code[], short int tabLength);

void genHumanCode(int code[], short int tabLength);

/***  HISTORIQUE DU CODE ***/

void printHistoryCode(int nbOfTries, int codeLength, const int historyCode[][codeLength]);




/**********************
   CODE DES FONCTIONS
***********************/


/***  OUTILS GENERATION CODE ***/


bool intToTab(int playerCode[], int number, int nbOfDigit)
{
    assert (playerCode != NULL);

    if(number < 0)
    {
        fprintf(stderr, "Erreur le code ne peut être négatif\n");
        return false;
    }

    if(nbOfDigit <= 0)
    {
        fprintf(stderr, "Erreur le nombre de digit doit valoir au moins 1\n");
        return false;
    }

    // verif taille nbre et attribution valeurs tableau
    // 1) si nbre plus petit que le tableau => remplissage à G par des 0
    for (int i = nbOfDigit - 1; i >=0 ; i--)
    {
        playerCode[i] =  number % 10;
        
        number /= 10;          
    }

     // 2) si nbre plus grand que le tableau (conseil IA)
     // donc nombre pas nul à la fin
    if (number != 0)
    {
        fprintf(stderr, "Erreur code trop grand par rapport au nbre de digit\n");
        return false;           
    }

    return true;
}


int getCodeMaxValue(int codeLength)
{
    int maxValue = 1;

    for (int i = 0; i < codeLength; i++)
        maxValue *= 10;

    return --maxValue;
}

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

// chiffres distincts générés 1 par 1 via rand
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

// le joueur encode un int et appel intToTab pour stocker dans un tab de int
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


/***  HISTORIQUE DU CODE ***/

void printHistoryCode(int nbOfTries, int codeLength, const int historyCode[][codeLength])
{
    assert(historyCode != NULL && codeLength > 0 && nbOfTries > 0);

    puts("\nHISTORIQUE");
    for(int i = 0; i < nbOfTries; i++)
    {
        printf("%d) ", i + 1);

        for(int j = 0; j < codeLength; j++)
            printf("%d", historyCode[i][j]);
        putchar('\n');
    }
}