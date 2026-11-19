#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void afficherEtudiant(const Etudiant *e)
{
    if (e == NULL)
        return;

    printf("Nom : %s\n", e->nom);

    // affichage des notes s'il y en a
    if (e->nbNotes > 0 && e->notes != NULL)
    {
        printf("Notes (%d) : ", e->nbNotes);
        for (int i = 0; i < e->nbNotes; i++)
            printf("%.1lf%s", e->notes[i], (i < e->nbNotes - 1) ? " | " : "\n");

        // moyenne
        double somme = 0;
        for (int i = 0; i < e->nbNotes; i++)
            somme += e->notes[i];
        printf("Moyenne : %.2lf\n", somme / e->nbNotes);
    }
    else
        puts("Notes : aucune");
}

Etudiant *creerEtudiant(const char *nom, const double *notes, int nbNotes)
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
    double *nvTabNotes = (double *) malloc (nbNotes * sizeof(*nvTabNotes));
    if (nvTabNotes == NULL)
    {
        free(nvNom);
        nvNom = NULL;
        free(nvEtudiant);
        nvEtudiant = NULL;
        return NULL;
    }
    else
    {
        for (int i = 0; i < nbNotes; i++)
            *(nvTabNotes + i) = *(notes + i);
    }

    // assignation des champs à la struct étudiant
    nvEtudiant->nom = nvNom;
    nvEtudiant->nbNotes = nbNotes;
    nvEtudiant->notes = nvTabNotes;

    return nvEtudiant;
}

void detruireEtudiant (Etudiant **e)
{
    if (e == NULL || *e == NULL)
        return;

    free((*e)->nom);
    free((*e)->notes);    
    free(*e);
    *e = NULL;    
}

int main(void)
{
    double notes[3] = {14.0f,16.0f,12.0f};
    char prenom[] = "Alice";

    Etudiant *alice = creerEtudiant(prenom, notes, 3);

    if(alice == NULL)
        fprintf(stderr, "Erreur création étudiante Alice\n");
    else
        afficherEtudiant(alice);

    detruireEtudiant(&alice);
    printf("Après destruction : pointeur = %p\n", (void*)alice);
    return EXIT_SUCCESS;
}