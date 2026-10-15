#include <stdio.h>
#ifdef _WIN32
    #include <windows.h>
#endif

void swap(int *a, int *b)
{
    if(a == NULL || b == NULL)
        return;
        
    int temp = *a;

    *a = *b;

    *b = temp;
}

int main(void)
{
    #ifdef _WIN32    
        SetConsoleOutputCP(CP_UTF8);
    #endif
    int a = 1, b = 3;

    printf("Avant swap: a vaut %d | b vaut %d\n", a,b);
    swap(&a, &b);

    printf("Après swap: a vaut %d | b vaut %d", a,b);

    return 0;
}