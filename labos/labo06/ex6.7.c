#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <assert.h>

typedef struct 
{
    char *nom;
    double note;
} Etudiant;

// difficulté IA ++ avec alloc dynamique de nom et gestion de lignes sautées
// la fonction retourne le nbre de ligne écrite dans le tableau
int importerCsv(const char *chemin, Etudiant *t, int max)
{
    assert(chemin != NULL && t != NULL);

    if (max <= 0)
    { 
        fprintf(stderr, "Erreur il faut pouvoir importer au moins 1 élément\n");
        return -1;
    }

    // variables pour stocker temporaire les imports
    char buffer[256];
    char tempNom[32];
    double tempNote;

    int i; // indice du tableau à remplir
    int numLigne; // correspond à la ligne importée du fichier csv

    FILE *f = fopen(chemin, "r");
    
    if (f == NULL)
    {
        perror(chemin);
        return -1;
    }

    // On extrait les données du fichier csv
    // 1) on saute la première ligne
    if(fgets(buffer, sizeof(buffer), f) == NULL)
    {
        fprintf(stdout, "Fichier vide\n");
        fclose(f);
        return -1;
    }
    // 2) on importe les valeurs sauf si fin de ligne ou ligne mal formée
    for (i = 0; i < max ; i++)
    {
        numLigne = 1; // ligne 0 = en tête sautée

        // si fin de fichier on arrête la boucle, l'import
        if(fgets(buffer, sizeof(buffer),f) == NULL)
            break;
        
         // si alloc échoue ou le nbre d'arg extraits par sscanf != 2 => on n'intègre pas et on saute la ligne
        if(sscanf(buffer, "%31[^;];%lf", tempNom, &tempNote) != 2 || tempNom[0] == '\0')
        {
            fprintf(stderr, "Ligne %d ignorée : format invalide\n", numLigne);
        }
        // sinon on intègre dans le tableau
        else
        {
            t[i].nom = (char *)malloc(strlen(tempNom) + 1);

            if(t[i].nom == NULL)
            {
                fprintf(stderr, "Erreur alloc dynamique pour le nom\n");
                for (int j = 0; j < i; j++)
                    free(t[j].nom);
                fclose(f);
                return -1;
            }
            // copie des valeurs dans le tableau
            strcpy(t[i].nom,tempNom);
            t[i].note = tempNote;            
        }     
        
        numLigne++;
    }

    fclose(f);
    return i;
}

// Recharger le fichier result_interro01.csv de l'ex 6.6
int main(void)
{
    SetConsoleOutputCP(CP_UTF8);
    Etudiant tab[3] = {0};

    int valRetour = importerCsv("result_interro01.csv", tab, 3);

    if ( valRetour == -1)
    {
        fprintf(stderr, "Importation ratée\n");
        return EXIT_FAILURE;
    }
    else
    {
        fprintf(stdout, "Import réussi!\n");

        for(int i = 0; i < valRetour; i++)
            printf("Nom : %-30s| Note : %.2lf\n", tab[i].nom, tab[i].note);

        // liberer les malloc des noms!
        for (int j = 0; j < valRetour; j++)
                    free(tab[j].nom);

        return EXIT_SUCCESS;
    }   
}