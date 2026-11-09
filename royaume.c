
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "royaume.h"

/* Ajouter un bâtiment dans la liste chaînée */
int ajouter_batiment(Royaume *r, TypeBatiment type, int niveau)
{
    NoeudBatiment *nouveau = malloc(sizeof(NoeudBatiment));

    if (nouveau == NULL) {
        printf("Erreur : allocation memoire impossible.\n");
        return 0;
    }

    nouveau->batiment.id = 1;

    NoeudBatiment *courant = r->batiments;

    while (courant != NULL) {
        if (courant->batiment.id >= nouveau->batiment.id) {
            nouveau->batiment.id = courant->batiment.id + 1;
        }

        courant = courant->suivant;
    }

    nouveau->batiment.type = type;
    nouveau->batiment.niveau = niveau;

    nouveau->suivant = r->batiments;
    r->batiments = nouveau;

    return 1;
}


/* Initialiser les valeurs du royaume */
void initialiser_royaume(Royaume *r)
{
    memset(r, 0, sizeof(Royaume));

    /* Informations générales */
    r->niveau = 1;
    r->jour = 1;

    /* Population et armée */
    r->population = 100;
    r->bonheur = 75;
    r->soldats = 20;
    r->niveau_equipement = 1;

    /* Gestion du royaume */
    r->politique_fiscale = 1;
    r->jours_famine = 0;

    /* Capacités */
    r->capacite_stockage = 500;
    r->capacite_population = 100;

    /* Ressources initiales */
    r->ressources.or = 500;
    r->ressources.bois = 250;
    r->ressources.pierre = 200;
    r->ressources.nourriture = 500;
    r->ressources.fer = 100;

    /* Statistiques */
    r->victoires = 0;
    r->defaites = 0;

    r->statistiques.jours_joues = 0;
    r->statistiques.batiments_construits = 0;
    r->statistiques.ameliorations = 0;
    r->statistiques.soldats_recrutes = 0;
    r->statistiques.victoires = 0;
    r->statistiques.defaites = 0;
    r->statistiques.revenus_totaux = 0;
    r->statistiques.depenses_totales = 0;

    /* Listes chaînées vides */
    r->batiments = NULL;
    r->historique = NULL;

    /* Ajouter les bâtiments initiaux */
    if (!ajouter_batiment(r, CHATEAU, 1) ||
        !ajouter_batiment(r, FERME, 1) ||
        !ajouter_batiment(r, CASERNE, 1)) {

        liberer_batiments(&r->batiments);
        printf("Erreur lors de la creation des batiments.\n");
    }
}


/* Créer une nouvelle partie */
void creer_royaume(Royaume *r)
{
    initialiser_royaume(r);

    printf("\n====================================\n");
    printf("       CREATION DU ROYAUME\n");
    printf("====================================\n");

    printf("\nDonnez un nom a votre royaume : ");

    if (fgets(r->nom, sizeof(r->nom), stdin) == NULL) {
        strcpy(r->nom, "Mon Royaume");
    } else {
        r->nom[strcspn(r->nom, "\n")] = '\0';

        if (strlen(r->nom) == 0) {
            strcpy(r->nom, "Mon Royaume");
        }
    }

    printf("\nVotre royaume %s a ete cree !\n", r->nom);
}


/* Afficher les informations du royaume */
void afficher_royaume(const Royaume *r)
{
    printf("\n====================================\n");
    printf("          MON ROYAUME\n");
    printf("====================================\n");

    printf("Nom du royaume       : %s\n", r->nom);
    printf("Niveau               : %d\n", r->niveau);
    printf("Jour                 : %d\n", r->jour);

    printf("\n--- POPULATION ET ARMEE ---\n");
    printf("Population           : %d\n", r->population);
    printf("Bonheur              : %d%%\n", r->bonheur);
    printf("Soldats              : %d\n", r->soldats);
    printf("Niveau equipement    : %d\n", r->niveau_equipement);

    printf("\n--- RESSOURCES ---\n");
    printf("Or                  : %.0f\n", r->ressources.or);
    printf("Bois                : %d\n", r->ressources.bois);
    printf("Pierre              : %d\n", r->ressources.pierre);
    printf("Nourriture          : %d\n", r->ressources.nourriture);
    printf("Fer                 : %d\n", r->ressources.fer);

    printf("\n--- CAPACITES ---\n");
    printf("Stockage            : %d\n", r->capacite_stockage);
    printf("Population          : %d\n", r->capacite_population);

    printf("\n--- STATISTIQUES ---\n");
    printf("Victoires           : %d\n", r->victoires);
    printf("Defaites            : %d\n", r->defaites);
}


/* Afficher le tableau de bord */
void afficher_tableau_bord(const Royaume *r)
{
    printf("\n====================================\n");
    printf("       TABLEAU DE BORD\n");
    printf("====================================\n");

    printf(" Royaume : %s\n", r->nom);
    printf(" Jour    : %d\n", r->jour);
    printf(" Niveau  : %d\n", r->niveau);

    printf("------------------------------------\n");
    printf(" OR          : %.0f\n", r->ressources.or);
    printf(" BOIS        : %d\n", r->ressources.bois);
    printf(" PIERRE      : %d\n", r->ressources.pierre);
    printf(" NOURRITURE  : %d\n", r->ressources.nourriture);
    printf(" FER         : %d\n", r->ressources.fer);

    printf("------------------------------------\n");
    printf(" Population  : %d\n", r->population);
    printf(" Bonheur     : %d%%\n", r->bonheur);
    printf(" Soldats     : %d\n", r->soldats);

    printf("------------------------------------\n");
    printf(" Batiments construits : %d\n",
           r->statistiques.batiments_construits);

    printf("====================================\n");
}


/* Libérer la liste des bâtiments */
void liberer_batiments(NoeudBatiment **liste)
{
    NoeudBatiment *courant = *liste;

    while (courant != NULL) {
        NoeudBatiment *suivant = courant->suivant;

        free(courant);

        courant = suivant;
    }

    *liste = NULL;
}


/* Libérer la liste de l'historique */
void liberer_historique(NoeudHistorique **liste)
{
    NoeudHistorique *courant = *liste;

    while (courant != NULL) {
        NoeudHistorique *suivant = courant->suivant;

        free(courant);

        courant = suivant;
    }

    *liste = NULL;
}
