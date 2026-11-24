#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// un programme ne doit jamais planter parce qu'un fichier manque
int main(void)
{
    SetConsoleOutputCP(CP_UTF8);

    // autorisation retiré à l'utilisateur local pour rwx
    FILE *file1 = fopen("protection.txt", "r");

    if(file1 == NULL)
    {
        perror("fopen file1: ");
    }

    FILE *file2 = fopen("accessible.txt", "r");

    if(file2 == NULL)
    {
        perror("fopen file ");
        if (file1 != NULL) 
            fclose(file1);
        return EXIT_FAILURE;
    }
    else
        printf("File 2 ouvert avec succès\n");

    if (file1 != NULL) 
        fclose(file1);
    fclose(file2);
    return 0;
}