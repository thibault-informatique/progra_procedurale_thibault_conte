#include <stdio.h>

int main(void)
{
    int a = 5, b = 10;
    int *p = &a;
    
    *p = 20;
     p = &b;
    *p += 5;
    printf("%d %d %d\n", a, b, *p);

    return 0;
}