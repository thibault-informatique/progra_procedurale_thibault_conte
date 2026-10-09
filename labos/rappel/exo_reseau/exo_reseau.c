/***  MINI PROG RESEAU ***/

// avec conditions binaires

// 2 adresses ip avec préfixe - masque /26 
// afficher réseaux + partie machine + même réseau ou réseau différent grâce à condition binaire
// afficher les adresses en Hexa avec print("0x%08X",...);

#include <stdio.h>
#include <stdint.h>



int main(void)
{
    uint32_t ip1 = (192u << 24) | (168u << 16) | (1u << 8) | (10u);
    uint32_t ip2 = (192u << 24) | (168u << 16) | (1u << 8) | (200u);

    uint32_t mask = ~(uint32_t)0 << (32 - 26); // masque /26

    uint32_t network1 = ip1 & mask;
    uint32_t network2 = ip2 & mask;

    uint32_t host1 = ip1 & ~mask;
    uint32_t host2 = ip2 & ~mask;


    puts ("ADRESSES IP en HEXA: ");

    printf("\nAdresse ip1 : 0x%08X\n", ip1);
    printf("Adresse ip2 : 0x%08X\n\n", ip2);

    puts ("PARTIE RESEAU en HEXA: ");

    printf("\nAdresse réseau (ip1) : 0x%08X\n", network1);
    printf("Adresse réseau (ip2) : 0x%08X\n\n", network2);

    puts ("PARTIE HOTE en HEXA: ");

    printf("\nAdresse hôte (ip1) : 0x%08X\n", host1);
    printf("Adresse hôte (ip2) : 0x%08X\n\n", host2);

    if (network1 == network2)
        puts("Même réseau");
    else
        puts("Réseaux différents");

    return 0;

}
