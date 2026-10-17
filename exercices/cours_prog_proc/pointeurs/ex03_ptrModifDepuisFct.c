#include <stdio.h>

void ajouterBonus(int *score, int bonus)
{
    if(score == NULL)
        return;
        
    *score += bonus;
}

int main(void)
{
    int score = 12;
    int bonus = 8;

    printf("score: %d + bonus: %d = ",score, bonus);

    ajouterBonus(&score, bonus);

    printf("%d", score);

    return 0;
}