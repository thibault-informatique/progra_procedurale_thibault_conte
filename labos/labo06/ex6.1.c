#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *f = fopen("rapport.txt", "w");

    if (f == NULL)
    {
        perror("Erreur fopen");
        return EXIT_FAILURE;
    }

    fprintf(f, "Rapport des carrés\n");
    for (int i = 1; i <= 10; i++)
        fprintf(f, "%d %d\n", i, i * i);

    fclose(f);
    return 0;
}