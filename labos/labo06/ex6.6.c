#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct 
{
    char *nom;
    double note;
} Etudiant;

int exporterCsv(const char *chemin, const Etudiant *t, int n)
{
    if (chemin == NULL || t == NULL) { fprintf(stderr, "exporterCsv(): arguments NULL\n"); return EXIT_FAILURE;}
    
    if (n <= 0) {fprintf(stderr, "le tableau doit contenir au moins un élève\n"); return EXIT_FAILURE;}

    FILE *f = fopen(chemin, "w");

    if(f == NULL) { perror(chemin); return EXIT_FAILURE;}

    // 1) en tête

    fprintf(f, "nom;notes\n");

    // 2) les valeurs

    for(int i = 0; i < n; i++)
        fprintf(f, "%s;%.2f\n", t[i].nom, t[i].note);

    fclose(f);

    return EXIT_SUCCESS;
}


// Sauvegarder un tableau d'étudiants dans un fichier tableur
int main(void)
{
    SetConsoleOutputCP(CP_UTF8);
    Etudiant tab[3] = {{"Alice", 15.00f},{"Bilal", 9.00f}, {"Chloé", 12.00f}};  

    if (exporterCsv("result_interro01.csv", tab, 3) == EXIT_FAILURE)
    {
        fprintf(stderr, "exportation ratée\n");
        return EXIT_FAILURE;
    }
    else
    {
        fprintf(stdout, "Export réussi!\n");
         return EXIT_SUCCESS;
    }   
}