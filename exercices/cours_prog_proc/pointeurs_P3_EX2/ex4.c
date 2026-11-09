#include <stdio.h>
#include <windows.h>

int main(void)
{
    SetConsoleOutputCP(CP_UTF8);

    // declaration
    int x = 4, y = 4;
    int *p = &x, *q = &y;

    printf("p == q   : %d\n", (p == q));
    printf("*p == *q : %d\n", (*p == *q));

    q = &x;

    printf("Après q = &x -> p == q : %d\n", (p == q));
    
    return 0;
}