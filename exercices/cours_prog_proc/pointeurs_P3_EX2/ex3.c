#include <stdio.h>

int main(void)
{
    // declaration
    int a = 3, b = 7;
    int *p = &a, *q = &b;
    *p = *q +1;
    q = p;
    *q *= 2;
    printf("%d %d %d %d\n", a, b, *p, *q);

    return 0;
}