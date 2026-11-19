#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    char *nom;
    double *notes;
    int nbNotes;
} Etudiant;

// copie de s
// alloue strlen(s) + 1
// permet à partir d'une chaine fournie en paramètre (pile) d'allouer sur le tas un espace mémoire pour cette chaine
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

Etudiant *creerEtudiant(const char *nom, int nbNotes)
{
    if(nom == NULL || nbNotes < 0)
        return NULL;

    // creation objet struct étudiant sur le tas
    Etudiant *nvEtudiant = (Etudiant*) malloc(sizeof(*nvEtudiant));

    if (nvEtudiant == NULL)
        return NULL;

    

    //creation *nom de la struct etudiant sur le tas
    char *nvNom = NULL;
    if((nvNom = dupliquer(nom)) == NULL)
    {
        free(nvEtudiant);
        nvEtudiant = NULL;
        return NULL;
    }

    // creationobjet tableau de notes pour la struct étudiant sur le tas(heap)

}

void detruireEtudiant (Etudiant **e)
{

}

int main(void)
{

    return EXIT_SUCCESS;
}