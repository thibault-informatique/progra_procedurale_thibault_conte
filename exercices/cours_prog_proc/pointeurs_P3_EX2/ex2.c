#include <stdio.h>

int main(void)
{
    // declaration
    int x = 10;
    int *p = &x;

    *p = 25;
    int y = *p + 5;

    printf("x  = %d\n", x);
    printf("*p = %d\n", *p); 
    printf("y  = %d\n", y);

    return 0;
}