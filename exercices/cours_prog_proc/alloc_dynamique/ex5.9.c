#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <windows.h>

// IA nécessaire +++ pour m'y retrouver

/*** LISTE DE MOTS DYNAMIQUES */

/*** Lire des mots jusqu'à "fin" et les stocker sans gaspiller de mémoire ***/

/*** CHAINES DYNAMIQUES***/

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

// tab = pointeur du pointeur
// *tab = pointeur vers un mot
// **tab = un mot
char **ajoutMotDansTab(char **tab, const char *mot, int *nbMots)
{
    // pas d'assert sur tab car il sera nul au premier appel
    assert(mot != NULL && nbMots != NULL);

    char *motTemp = dupliquer(mot);    

    if (motTemp == NULL)
        return NULL;
    
    // pTaTemp = pointeur vers le tableau de mots
    char **pTabTemp = (char**) realloc(tab, (*nbMots + 1) * sizeof(*pTabTemp));

    // si realloc échoue, on libère l'alloc générée par dupliquer()
    if(pTabTemp == NULL)
    {
        free(motTemp);
        return NULL;
    }
    
    pTabTemp[(*nbMots)++] = motTemp;

    return pTabTemp;
    
}

int main(void)
{
    SetConsoleOutputCP(CP_UTF8);
    
    /************
     DECLARATION
    *************/

    // "équivalent dynamique d'un tab statique 2D de char"
    char **tabString= NULL;

    // stocke l'ensemble des mots
    char buffer[1024] = {'\0'};

    // va stocker un mot à la fois extrait de buffer
    char bufferIntermediaire[30] = {'\0'};

    // pour avancer dans buffer via sscanf grâce à la position et l'avancement 
    int offset = 0, pos = 0;

    int nbMots = 0;


    /************
        CODE
    *************/

    puts("Saisir un nombre aléatoire de mots séparés par un espace et finir par le mot fin puis taper ENTER");
    printf("Mot: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Erreur dans fgets lors de la saisie des mots\n");
        return EXIT_FAILURE;
    }

    while (sscanf(buffer + offset, "%29s%n", bufferIntermediaire, &pos) == 1)
    {
        if(strcmp(bufferIntermediaire, "fin") == 0)
            break;
       
        char **nouveau = ajoutMotDansTab(tabString, bufferIntermediaire, &nbMots);
        
        if(nouveau == NULL)   
            {       
                fprintf(stderr, "Erreur ajout d'un mot ou pointeur NULL\n");
                // libérer tous les mots (intérieur du tab)
                for (int i = 0; i < nbMots; i++)
                    free(tabString[i]);
                // libérer le tab
                free(tabString);
                return EXIT_FAILURE;                
            }

        tabString = nouveau;
        offset += pos;        
    }

   /*******************
     AFFICHAGE INVERSE
    ******************/

    printf("Inverse: ");
    for (int i = nbMots - 1; i >= 0; i--)
        printf("%s ", tabString[i]);
    putc('\n', stdout);

    printf("%d mot(s)\n", nbMots);


    /************
        FREE
    *************/

    for (int i = 0; i < nbMots; i++)
        free(tabString[i]);
    
    free(tabString);
    tabString = NULL;

    return EXIT_SUCCESS;
}