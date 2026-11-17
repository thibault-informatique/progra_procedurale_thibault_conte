#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*** CHAINES DYNAMIQUES***/

// copie de s
// alloue strlen(s) + 1
char *dupliquer(const char *s)
{
    if (s == NULL)
        return NULL;

    // calcul taille de s 
    // + 1 car strlen s'arrête au dernier caractère avant '\0'
    int n = strlen(s) + 1;

    char *tempString = (char*) malloc (sizeof(*tempString) * n);

    if (tempString == NULL)
        return NULL;
    
    for (int i = 0; i < n ; i++)
        tempString[i] = s[i];

    return tempString;    
}

// concatener a et b
// alloue exactement la place pour a + b +'\0'
char *concatener(const char *a, const char *b)
{
    if(a == NULL || b == NULL)
        return NULL;

    int aLength = strlen(a);
    int bLength = strlen(b);     
    int n = aLength + bLength + 1;

    char *tempString = (char*) malloc (sizeof(*tempString) * n);

    if (tempString == NULL)
        return NULL;

    int i;
    // tempString copie a
    for (i = 0; i < aLength ; i++)
        tempString[i] = a[i];

     // tempString copie b directement après i = aLength
     // arrêt à n - 1 pour laisser la place finale à '\0'
    for (int j = 0 ; i < n -1 && j < bLength ; i++, j++)
        tempString[i] = b[j];
    
    // on ajoute '\0' pour finir proprement la chaine
    tempString[i] = '\0';

    return tempString;    
    
}

int main(void)
{

    char string1[] = "Bonjour";
    char string2[] = ", ITLG";

    char *pFinalString = concatener(string1, string2);

    // +1 pour le '\0' qui utilise de la mémoire également
    printf("Resultat concaténation : %s \nTaille %zu caractères | Mémoire %lld octets\n", pFinalString, strlen(pFinalString), (strlen(pFinalString) + 1) * sizeof(char));


    free(pFinalString);
    return 0;
}