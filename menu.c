#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "royaume.h"
#include "ressources.h"
#include "batiments.h"
#include "entrepot.h"
#include "economie.h"
#include "marche.h"
#include "temps.h"
#include "progression.h"

static int lire_entier(const char *invite)
{
    char ligne[64], *fin;
    long valeur;
    printf("%s", invite);
    if (!fgets(ligne, sizeof ligne, stdin)) return -1;
    valeur = strtol(ligne, &fin, 10);
    if (fin == ligne) return -1;
    return (int)valeur;
}

static void afficher_menu(void)
{
    printf("\n========== KINGDOM MANAGER ==========\n");
    printf("1. Afficher le royaume\n");
    printf("2. Afficher les ressources\n");
    printf("3. Afficher les batiments\n");
    printf("4. Construire un batiment\n");
    printf("5. Ameliorer un batiment\n");
    printf("6. Gestion de l'entrepot\n");
    printf("7. Marche\n");
    printf("8. Bilan economique\n");
    printf("9. Choisir la politique fiscale\n");
    printf("10. Progression\n");
    printf("11. Avancer d'un jour\n");
    printf("0. Quitter\n");
    printf("====================================\n");
}

void menu_principal(Royaume *r)
{
    int choix, type, id, politique;
    if (r == NULL) return;

    do {
        afficher_menu();
        choix = lire_entier("Votre choix : ");

        switch (choix) {
        case 1:
            afficher_royaume(*r);
            break;
        case 2:
            afficher_ressources(r->ressources);
            break;
        case 3:
            afficher_batiments(r->batiments);
            break;
        case 4:
            printf("Types : 1 Ferme, 2 Scierie, 3 Carriere, 4 Mine de fer, "
                   "5 Maison, 6 Caserne, 7 Entrepot\n");
            type = lire_entier("Type : ");
            if (type >= 1 && type <= 7)
                construire_batiment(r, type);
            else
                printf("Type invalide.\n");
            break;
        case 5:
    printf("\n--- Amelioration d'un batiment ---\n");

    /* Afficher les batiments et leurs ID */
    afficher_batiments(r->batiments);

    printf("\nID du batiment a ameliorer (0 pour annuler) : ");

    if (scanf("%d", &id) != 1) {
        printf("Saisie invalide.\n");
        while (getchar() != '\n');
        break;
    }

    if (id == 0) {
        printf("Amelioration annulee.\n");
        break;
    }

    ameliorer_batiment(r, id);
    break;
        case 6:
            printf("1. Construire entrepot  2. Ameliorer entrepot\n");
            type = lire_entier("Choix : ");
            if (type == 1) construire_entrepot(r);
            else if (type == 2) ameliorer_entrepot(r);
            else printf("Choix invalide.\n");
            break;
        case 7:
            menu_marche(r);
            break;
        case 8:
            afficher_bilan_economique(*r);
            break;
        case 9:
            printf("0. Faible (0.5 or/habitant, bonheur +1)\n"
                   "1. Normale (1 or/habitant)\n"
                   "2. Elevee (2 or/habitant, bonheur -5)\n");
            politique = lire_entier("Politique : ");
            if (politique >= 0 && politique <= 2)
                definir_politique_fiscale(r, politique);
            else
                printf("Politique invalide.\n");
            break;
        case 10:
            afficher_progression(r);
            break;
        case 11:
            if (avancer_jour(r))
                printf("Une journee est passee.\n");
            break;
        case 0:
            printf("Fin de partie.\n");
            break;
        default:
            printf("Choix invalide.\n");
        }
    } while (choix != 0);
}
