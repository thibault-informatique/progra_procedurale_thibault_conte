#include <stdio.h>
#include <stdlib.h>

/*** TABLEAU EXTENSIBLE AVEC REALLOC ***/


// ajout de valeurs dans un tab de int
// si tableau plein => agrandissement via realloc (on double la capacité)
// 1 si ok
// -1 si erreur pointeurs NULL
int ajouterValeur(int **tab, int *taille, int *capacite, int valeur)
{
    if (tab == NULL || taille == NULL || capacite == NULL || *capacite < 1)
        return -1;

  
    // gestion tab trop petit
    if(*taille >= *capacite)
    {
        int nvCapacite = *capacite * 2;

        int *pTemp = realloc(*tab, nvCapacite * sizeof(*pTemp));

        if (pTemp == NULL)
            return -1;

        *tab = pTemp;

        printf("Capacité: %d -> %d\n", *capacite, nvCapacite);

        *capacite = nvCapacite;        
    }

    // ajout valeur
    // equivalent à
    // (*tab)[(*taille)++] = valeur;
    *(*tab + (*taille)++) = valeur; 

    return 1;
}

int main(void)
{
    int *tab = (int*) malloc (2 * sizeof(*tab));

    if(tab == NULL)
        return EXIT_FAILURE;

    int tailleTab = 0; // nbre de place occupée dans le tableau
    int capacite = 2; // place totale dans le tableau (capacité initiale)

    char ligne[1024]; // va récuperer la saisie user d'un nbre variable d'entiers

     // IA nécessaire pour récupérer la saisie via notamment sscanf
    // pos pour savoir où on est dans l'extraction de la chaine récupérer via %n dans sscanf
    int offset = 0, pos = 0, valeur = 0;

    // 1) Saisie
    puts("Saisir un nombre aléatoire de nbres entiers avec un espace et finir par 0 puis taper ENTER");
    printf("Saisie: ");

    if(fgets(ligne, sizeof(ligne), stdin) == NULL) 
        return EXIT_FAILURE;
    
    // 2) on analyse et on extrait les infos de la saisie du point 1
    // tant que sscanf prélève une information dans le buffer/ char ligne
    while (sscanf(ligne + offset, "%d%n", &valeur, &pos) == 1)
    {
        // si valeur 0 alors = valeur sentinelle, fin de la saisie
        if (valeur == 0)
            break;
        else
        {
            if(ajouterValeur(&tab, &tailleTab, &capacite, valeur) == -1)
                fprintf(stderr, "pointeurs NULL passés en paramètres ou erreur REALLOC()\n");
        }

        // avancer au prochain nombre pour nouvelle saisie via sscanf
        offset += pos;
    }
    
    printf("%d valeur(s) lue(s) : ", tailleTab);
    for (int i = 0; i < tailleTab; i++)
        printf("%d ", tab[i]);
    putchar('\n');

    free(tab);
    return 0;
}