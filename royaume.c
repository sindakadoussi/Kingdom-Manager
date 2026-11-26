#include <stdio.h>
#include <string.h>
#include "royaume.h"
#include "batiments.h"
#include "ressources.h"
#include "entrepot.h"

static void copier_texte(char *destination, size_t taille, const char *source)
{
    if (source == NULL) source = "";
    snprintf(destination, taille, "%s", source);
}

int initialiser_royaume(Royaume *r, const char *nom, const char *joueur)
{
    if (r == NULL) return 0;
    memset(r, 0, sizeof *r);
    copier_texte(r->nom, sizeof r->nom, nom);
    copier_texte(r->nom_joueur, sizeof r->nom_joueur, joueur);

    r->ressources.or = OR_INITIAL;
    r->population = POPULATION_INITIALE;
    r->capacite_population = 100;
    r->bonheur = BONHEUR_INITIAL;
    r->capacite_stockage = STOCK_BASE;
    r->niveau_entrepot = 0;
    r->jour = JOUR_INITIAL;
    r->politique_fiscale = POLITIQUE_NORMALE;
    r->niveau_royaume = 1;
    r->points_progression = 0;
    r->prochain_id_batiment = 1;
    r->batiments = NULL;

    /* Le château initial et une ferme assurent une base jouable. */
    {
        Batiment b;
        memset(&b, 0, sizeof b);
        b.id = r->prochain_id_batiment++;
        b.type = BATIMENT_CHATEAU;
        b.niveau = 1;
        snprintf(b.nom, sizeof b.nom, "Chateau");
        if (!ajouter_batiment(&r->batiments, b)) return 0;

        b.id = r->prochain_id_batiment++;
        b.type = BATIMENT_FERME;
        b.niveau = 1;
        snprintf(b.nom, sizeof b.nom, "Ferme");
        if (!ajouter_batiment(&r->batiments, b)) {
            liberer_batiments(&r->batiments);
            return 0;
        }
    }
    return 1;
}

void afficher_royaume(Royaume r)
{
    printf("\n====== ROYAUME ======\n");
    printf("Nom : %s\nJoueur : %s\nJour : %d\n",
           r.nom, r.nom_joueur, r.jour);
    printf("Population : %d / %d\n", r.population, r.capacite_population);
    printf("Bonheur : %d/100\n", r.bonheur);
    printf("Entrepot : niveau %d, capacite %d par ressource\n",
           r.niveau_entrepot, r.capacite_stockage);
    printf("Niveau du royaume : %d (points %d)\n",
           r.niveau_royaume, r.points_progression);
    printf("====================\n");
}
