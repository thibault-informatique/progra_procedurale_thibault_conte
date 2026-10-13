#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
    #include <windows.h>
#endif

void augmenterSalaire(float *montant, float pourcentage)
{
    if(montant == NULL) 
        return;

    *montant *= 1 + pourcentage;
}

int main(void)
{
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
    float budget = 1500.0f;

    printf("Budget initial : %19.2f€\n", budget);

    augmenterSalaire(&budget, 0.10f);

    printf("Budget après augmentation : %8.2f€\n", budget);

    return 0;
}