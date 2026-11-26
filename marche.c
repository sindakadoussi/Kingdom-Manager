#include <stdio.h>
#include <stdlib.h>
#include "marche.h"
#include "ressources.h"
#include "economie.h"
#include "constantes.h"

static int lire_nombre(const char *invite)
{
    char ligne[80], *fin;
    long n;
    printf("%s", invite);
    if (!fgets(ligne, sizeof ligne, stdin)) return -1;
    n = strtol(ligne, &fin, 10);
    if (fin == ligne || n < 0 || n > 1000000) return -1;
    return (int)n;
}

static int prix_achat(TypeRessource t)
{
    switch (t) {
    case RESSOURCE_BOIS: return PRIX_ACHAT_BOIS;
    case RESSOURCE_PIERRE: return PRIX_ACHAT_PIERRE;
    case RESSOURCE_NOURRITURE: return PRIX_ACHAT_NOURRITURE;
    case RESSOURCE_FER: return PRIX_ACHAT_FER;
    default: return 0;
    }
}

static int prix_vente(TypeRessource t)
{
    switch (t) {
    case RESSOURCE_BOIS: return PRIX_VENTE_BOIS;
    case RESSOURCE_PIERRE: return PRIX_VENTE_PIERRE;
    case RESSOURCE_NOURRITURE: return PRIX_VENTE_NOURRITURE;
    case RESSOURCE_FER: return PRIX_VENTE_FER;
    default: return 0;
    }
}

static void afficher_prix(void)
{
    printf("\n--- Marche (prix par unite) ---\n");
    printf("1 Bois       : achat %d / vente %d or\n", PRIX_ACHAT_BOIS, PRIX_VENTE_BOIS);
    printf("2 Pierre     : achat %d / vente %d or\n", PRIX_ACHAT_PIERRE, PRIX_VENTE_PIERRE);
    printf("3 Nourriture : achat %d / vente %d or\n", PRIX_ACHAT_NOURRITURE, PRIX_VENTE_NOURRITURE);
    printf("4 Fer        : achat %d / vente %d or\n", PRIX_ACHAT_FER, PRIX_VENTE_FER);
}

void menu_marche(Royaume *r)
{
    int action, choix, quantite, prix, total, ajoute;
    TypeRessource type;
    if (r == NULL) return;
    do {
        afficher_prix();
        printf("1 Acheter  2 Vendre  0 Retour\n");
        action = lire_nombre("Action (0 pour retour) : ");
        if (action == 0) return;
        if (action != 1 && action != 2) {
            printf("Choix invalide.\n");
            continue;
        }
        choix = lire_nombre("Ressource (1 bois, 2 pierre, 3 nourriture, 4 fer) : ");
        if (choix < 1 || choix > 4) {
            printf("Ressource invalide.\n");
            continue;
        }
        type = (TypeRessource)(choix - 1);
        quantite = lire_nombre("Quantite : ");
        if (quantite <= 0) {
            printf("Quantite invalide.\n");
            continue;
        }
        if (action == 1) {
            prix = prix_achat(type);
            total = prix * quantite;
            if (r->ressources.or < total) {
                printf("Or insuffisant : il faut %d or.\n", total);
                continue;
            }
            r->ressources.or -= total;
            ajoute = ajouter_ressource(r, type, quantite);
            /* Ne facturer que ce qui a réellement été stocké. */
            if (ajoute < quantite) r->ressources.or += prix * (quantite - ajoute);
            enregistrer_depense(r, prix * ajoute);
            printf("Achat effectue : %d unite(s).\n", ajoute);
        } else {
            prix = prix_vente(type);
            if (retirer_ressource(r, type, quantite) == 0) {
                printf("Stock insuffisant.\n");
                continue;
            }
            total = prix * quantite;
            r->ressources.or += total;
            r->economie.revenus_jour += total;
            r->economie.revenus_total += total;
            printf("Vente effectuee : +%d or.\n", total);
        }
    } while (action != 0);
}
