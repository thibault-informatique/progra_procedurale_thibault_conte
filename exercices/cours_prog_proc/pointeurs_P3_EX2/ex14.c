#include <stdio.h>
#include <assert.h>
#include <math.h>

typedef struct 
{
    double x;
    double y;
} Point;

void deplacer(Point *p, double dx, double dy)
{
    assert (p!= NULL);

    p->x += dx;
    p->y += dy;
}

double distance(const Point *a, const Point *b)
{
    assert (a != NULL && b != NULL);

    // valeurs soustraction axe des x
    double diffX = a->x - b->x;
    // valeurs soustraction axe des y
    double diffY = a->y - b->y;

    // via pythagore calcul distance entre 2 points 
    // existe via IA dans math.h hypot(diffX, diffY)

    return sqrt(diffX * diffX + diffY * diffY);
}

int main(void)
{
    Point A = {1,2}, O = {0,0};

    printf("A avant déplacement : (%.2f ; %.2f)\n", A.x, A.y);
    deplacer(&A, 2, 2);
    printf("A après déplacement : (%.2f ; %.2f)\n", A.x, A.y);

    printf("Distance OA : %.2f\n", distance(&A, &O));

    return 0;

}