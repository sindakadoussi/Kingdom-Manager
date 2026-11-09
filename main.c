
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "royaume.h"

int main()
{
    int choix;
    char ligne[20];

    Royaume mon_royaume;
    int partie_creee = 0;

    do {
        printf("\n");
        printf("====================================\n");
        printf("          KINGDOM MANAGER\n");
        printf("====================================\n");

        printf("  1. Nouvelle partie\n");
        printf("  2. Charger une partie\n");
        printf("  3. Quitter\n");

        printf("\nVotre choix : ");

        if (fgets(ligne, sizeof(ligne), stdin) == NULL) {
            break;
        }

        choix = atoi(ligne);

        switch (choix) {

            case 1:
                if (partie_creee) {
                    liberer_batiments(&mon_royaume.batiments);
                    liberer_historique(&mon_royaume.historique);
                }

                creer_royaume(&mon_royaume);
                partie_creee = 1;

                afficher_tableau_bord(&mon_royaume);
                break;

            case 2:
                printf("\nLe chargement sera ajoute dans une prochaine etape.\n");
                break;

            case 3:
                printf("\nAu revoir, roi ou reine !\n");
                break;

            default:
                printf("\nChoix invalide ! Reessayez.\n");
        }

    } while (choix != 3);

    if (partie_creee) {
        liberer_batiments(&mon_royaume.batiments);
        liberer_historique(&mon_royaume.historique);
    }

    return 0;
}
