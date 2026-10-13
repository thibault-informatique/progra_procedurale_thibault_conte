#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <time.h> // nécessaire pour gen nbre aléatoire

#define MAXVALUE 3
unsigned short int genRandowNb123(void)
{ 
    return rand()%MAXVALUE + 1;
}

unsigned short int getUserChoice(unsigned short int minValue, unsigned short int maxValue)
{
    char buffer[20];
    char reste;
    unsigned short int userChoice;

    
    while((fgets(buffer, sizeof(buffer), stdin) == NULL) ||
          // valide seulement si la ligne contient un nombre ET RIEN D'AUTRE
          (sscanf(buffer, "%hu %c", &userChoice, &reste) != 1)      ||
          (userChoice < minValue)                        ||
          (userChoice > maxValue))
    {
        // conseil sécurité IA vérifier si stdin fermé sinon boucle infinie
        if (feof(stdin) || ferror(stdin))
        {
            fprintf(stderr,"Fin de flux d'entrée\n");
            exit(EXIT_FAILURE);
        }

        // si saisie plus longue qu'autorisée', (ici si plus que 19 caractères saisis)
        // fgets ne sait pas ajouter \n dans la variable char buffer[20] et elle reste alors en mémoire tampon, dans stdin       
        if(strchr(buffer, '\n') == NULL)
        {
            int c;
            while((c = getchar()) != '\n' && c != EOF);
        }
        fprintf(stderr, "Mauvais choix (min à %hu - max à %hu)\n", minValue, maxValue);
    }
    return userChoice;
}

void printChoosenNb(unsigned short int choosenNb)
{
    if (choosenNb > MAXVALUE)
    {
        fprintf(stderr, "Erreur valeur trop haute!\n");
        return;
    }
    switch(choosenNb)
    {
        case 1: 
            puts("Pierre");
            break;
        case 2:
            puts("Papier");
            break;
        case 3:
        puts("Ciseaux");
            break;
        default:
            fprintf(stderr, "Erreur du choix entre la pierre, le papier ou les ciseaux\n");
            break;
    }
}

void printWinner(unsigned short int userNb, unsigned short int computerNb,unsigned short int* userScore, unsigned short int* computerScore)
{
    assert (userScore != NULL && computerScore != NULL);

    if (userNb > MAXVALUE || computerNb > MAXVALUE)
    {
        fprintf(stderr, "Erreur valeur trop haute!");
        return;
    }

    // cas égalité
    if(userNb == computerNb)
    {
        puts("Egalité !");
        printf("Joueur: %hu - %hu Ordinateur\n", *userScore, *computerScore);
        return;
    }
    else if((userNb == 1 && computerNb == 3) || (userNb == 2 && computerNb == 1) || (userNb == 3 && computerNb == 2))
    {
        puts("Vous avez gagné !");
        printf("Joueur: %hu - %hu Ordinateur\n", ++(*userScore), *computerScore);
        return;
    }
    else
    {
       puts("Vous avez perdu !");
       printf("Joueur: %hu - %hu Ordinateur\n", *userScore, ++(*computerScore));
       return; 
    }
}

void printGameMenu(unsigned short int* userScore, unsigned short int* computerScore)
{
    
    assert (userScore != NULL && computerScore != NULL);

    unsigned short int userChoice = 0;
    unsigned short int computerChoice = 0;

    puts("=== PIERRE - PAPIER - CISEAUX ===");
    puts("1. Pierre");
    puts("2. Papier");
    puts("3. Ciseaux");

    printf("\nVotre choix: ");

    userChoice = getUserChoice(1,MAXVALUE);  
     
    printf("\nJoueur: ");   
    printChoosenNb(userChoice);

    printf("Ordinateur: ");
    computerChoice = genRandowNb123();
    printChoosenNb(computerChoice);

    printWinner(userChoice, computerChoice, userScore, computerScore);
}

int main(void)
{
    // decla
    bool gameActive = true;
    unsigned short int userScore = 0;
    unsigned short int computerScore = 0;
  
    // init générateur nbre aléatoire
    srand(time(NULL));

    do
    {
        printGameMenu(&userScore, &computerScore);
        puts("Voulez vous refaire une manche?");
        puts("[1] oui");
        puts("[0] non");
        gameActive = (bool) getUserChoice(0,1);
    } while (gameActive);  


    return EXIT_SUCCESS;
}
