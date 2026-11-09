#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

int main() {

    printf("\n");
    printf("====================================\n");
    printf("          KINGDOM MANAGER           \n");
    printf("====================================\n");

    printf("\n");
    printf("  1. Nouvelle partie\n");
    printf("  2. Charger une partie\n");
    printf("  3. Quitter\n");

    printf("\n");
    printf("Votre choix : ");

    int choix;
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            printf("\nNouvelle partie !\n");
            break;

        case 2:
            printf("\nChargement d'une partie...\n");
            break;

        case 3:
            printf("\nAu revoir !\n");
            break;

        default:
            printf("\nChoix invalide !\n");
    }

    return 0;
}