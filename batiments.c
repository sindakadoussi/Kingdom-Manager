#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "batiments.h"
#include "ressources.h"
#include "entrepot.h"
#include "economie.h"

static const char *nom_type(TypeBatiment type)
{
    switch (type) {
    case BATIMENT_CHATEAU: return "Chateau";
    case BATIMENT_FERME: return "Ferme";
    case BATIMENT_SCIERIE: return "Scierie";
    case BATIMENT_CARRIERE: return "Carriere";
    case BATIMENT_MINE_FER: return "Mine de fer";
    case BATIMENT_MAISON: return "Maison";
    case BATIMENT_CASERNE: return "Caserne";
    case BATIMENT_ENTREPOT: return "Entrepot";
    default: return "Inconnu";
    }
}

int ajouter_batiment(NoeudBatiment **liste, Batiment b)
{
    NoeudBatiment *n, *courant;
    if (liste == NULL) return 0;
    n = malloc(sizeof *n);
    if (n == NULL) return 0;
    n->batiment = b;
    n->suivant = NULL;
    if (*liste == NULL) {
        *liste = n;
    } else {
        courant = *liste;
        while (courant->suivant != NULL) courant = courant->suivant;
        courant->suivant = n;
    }
    return 1;
}

Batiment *rechercher_batiment(NoeudBatiment *liste, int id)
{
    while (liste != NULL) {
        if (liste->batiment.id == id) return &liste->batiment;
        liste = liste->suivant;
    }
    return NULL;
}

void afficher_batiments(NoeudBatiment *liste)
{
    if (liste == NULL) {
        printf("Aucun batiment.\n");
        return;
    }
    printf("\n--- Batiments ---\n");
    while (liste != NULL) {
        printf("ID %d | %s | niveau %d\n", liste->batiment.id,
               nom_type(liste->batiment.type), liste->batiment.niveau);
        liste = liste->suivant;
    }
}

int compter_batiments(NoeudBatiment *liste)
{
    int n = 0;
    while (liste != NULL) {
        if (liste->batiment.type != BATIMENT_CHATEAU) n++;
        liste = liste->suivant;
    }
    return n;
}

/* Coûts de construction proposés, car le cahier des charges ne les détaille pas. */
static int payer_construction(Royaume *r, TypeBatiment type)
{
    int or = 0, bois = 0, pierre = 0;
    switch (type) {
    case BATIMENT_FERME: or = 100; bois = 30; pierre = 20; break;
    case BATIMENT_SCIERIE: or = 120; bois = 40; pierre = 20; break;
    case BATIMENT_CARRIERE: or = 120; bois = 30; pierre = 30; break;
    case BATIMENT_MINE_FER: or = 180; bois = 50; pierre = 50; break;
    case BATIMENT_MAISON: or = 80; bois = 40; pierre = 20; break;
    case BATIMENT_CASERNE: or = 200; bois = 60; pierre = 60; break;
    case BATIMENT_ENTREPOT: or = 250; bois = 100; pierre = 80; break;
    default: return 0;
    }
    if (r->ressources.or < or || r->ressources.bois < bois ||
        r->ressources.pierre < pierre) {
        printf("Ressources insuffisantes (cout : %d or, %d bois, %d pierre).\n",
               or, bois, pierre);
        return 0;
    }
    r->ressources.or -= or;
    r->ressources.bois -= bois;
    r->ressources.pierre -= pierre;
    enregistrer_depense(r, or);
    return 1;
}

int construire_batiment(Royaume *r, int type)
{
    Batiment b;
    TypeBatiment t;
    if (r == NULL || type < 1 || type > 7) return 0;
    t = (TypeBatiment)type;
    if (t == BATIMENT_ENTREPOT && r->niveau_entrepot > 0) {
        printf("Un seul entrepot est autorise.\n");
        return 0;
    }
    if (!payer_construction(r, t)) return 0;
    memset(&b, 0, sizeof b);
    b.id = r->prochain_id_batiment++;
    b.type = t;
    b.niveau = 1;
    snprintf(b.nom, sizeof b.nom, "%s", nom_type(t));
    if (!ajouter_batiment(&r->batiments, b)) {
        printf("Erreur allocation memoire.\n");
        return 0;
    }
    if (t == BATIMENT_MAISON) r->capacite_population += 50;
    if (t == BATIMENT_CASERNE) { /* Les places militaires sont gerees par le module armee. */ }
    if (t == BATIMENT_ENTREPOT) {
        r->niveau_entrepot = 1;
        mettre_a_jour_capacite_stockage(r);
    }
    printf("%s construit (ID %d).\n", b.nom, b.id);
    return 1;
}

int ameliorer_batiment(Royaume *r, int id)
{
    Batiment *b;
    int or, bois, pierre;
    if (r == NULL || (b = rechercher_batiment(r->batiments, id)) == NULL) {
        printf("Batiment introuvable.\n");
        return 0;
    }
    if (b->type == BATIMENT_CHATEAU || b->niveau >= BATIMENT_NIVEAU_MAX) {
        printf("Ce batiment ne peut pas etre ameliore.\n");
        return 0;
    }
    if (b->niveau == 1) {
        or = COUT_AMELIORATION_N1_OR; bois = COUT_AMELIORATION_N1_BOIS;
        pierre = COUT_AMELIORATION_N1_PIERRE;
    } else {
        or = COUT_AMELIORATION_N2_OR; bois = COUT_AMELIORATION_N2_BOIS;
        pierre = COUT_AMELIORATION_N2_PIERRE;
    }
    if (r->ressources.or < or || r->ressources.bois < bois ||
        r->ressources.pierre < pierre) {
        printf("Ressources insuffisantes : %d or, %d bois, %d pierre.\n",
               or, bois, pierre);
        return 0;
    }
    r->ressources.or -= or; r->ressources.bois -= bois; r->ressources.pierre -= pierre;
    enregistrer_depense(r, or);
    b->niveau++;
    if (b->type == BATIMENT_MAISON) r->capacite_population += 50;
    if (b->type == BATIMENT_ENTREPOT) {
        r->niveau_entrepot = b->niveau;
        mettre_a_jour_capacite_stockage(r);
    }
    printf("Batiment ID %d passe au niveau %d.\n", id, b->niveau);
    return 1;
}

int supprimer_batiment(Royaume *r, int id)
{
    NoeudBatiment *courant, *precedent = NULL;
    if (r == NULL) return 0;
    courant = r->batiments;
    while (courant != NULL && courant->batiment.id != id) {
        precedent = courant;
        courant = courant->suivant;
    }
    if (courant == NULL) return 0;
    if (courant->batiment.type == BATIMENT_CHATEAU) {
        printf("Le chateau ne peut pas etre supprime.\n");
        return 0;
    }
    if (courant->batiment.type == BATIMENT_FERME) {
        int fermes = 0;
        NoeudBatiment *p;
        for (p = r->batiments; p; p = p->suivant)
            if (p->batiment.type == BATIMENT_FERME) fermes++;
        if (fermes <= 1) {
            printf("La derniere ferme ne peut pas etre supprimee.\n");
            return 0;
        }
    }
    if (courant->batiment.type == BATIMENT_ENTREPOT) {
        if (r->ressources.bois > STOCK_BASE || r->ressources.pierre > STOCK_BASE ||
            r->ressources.nourriture > STOCK_BASE || r->ressources.fer > STOCK_BASE) {
            printf("Impossible : stock superieur a la capacite de base.\n");
            return 0;
        }
        r->niveau_entrepot = 0;
        r->capacite_stockage = STOCK_BASE;
    }
    if (courant->batiment.type == BATIMENT_MAISON) {
        int capacite_apres = r->capacite_population - 50 * courant->batiment.niveau;
        if (capacite_apres < r->population) {
            printf("Impossible : capacite de logement insuffisante.\n");
            return 0;
        }
        r->capacite_population = capacite_apres;
    }
    if (precedent == NULL) r->batiments = courant->suivant;
    else precedent->suivant = courant->suivant;
    free(courant);
    return 1;
}

static int production_niveau(int n, int p1, int p2, int p3)
{
    if (n == 1) return p1;
    if (n == 2) return p2;
    return p3;
}

void calculer_production_batiments(NoeudBatiment *liste, Ressources *production)
{
    if (production == NULL) return;
    production->bois = production->pierre = production->nourriture = production->fer = 0;
    production->or = 0;
    while (liste != NULL) {
        Batiment b = liste->batiment;
        switch (b.type) {
        case BATIMENT_FERME:
            production->nourriture += production_niveau(b.niveau, PRODUCTION_FERME_N1, PRODUCTION_FERME_N2, PRODUCTION_FERME_N3);
            break;
        case BATIMENT_SCIERIE:
            production->bois += production_niveau(b.niveau, PRODUCTION_SCIERIE_N1, PRODUCTION_SCIERIE_N2, PRODUCTION_SCIERIE_N3);
            break;
        case BATIMENT_CARRIERE:
            production->pierre += production_niveau(b.niveau, PRODUCTION_CARRIERE_N1, PRODUCTION_CARRIERE_N2, PRODUCTION_CARRIERE_N3);
            break;
        case BATIMENT_MINE_FER:
            production->fer += production_niveau(b.niveau, PRODUCTION_MINE_N1, PRODUCTION_MINE_N2, PRODUCTION_MINE_N3);
            break;
        default: break;
        }
        liste = liste->suivant;
    }
}

void liberer_batiments(NoeudBatiment **liste)
{
    NoeudBatiment *p, *suivant;
    if (liste == NULL) return;
    p = *liste;
    while (p != NULL) {
        suivant = p->suivant;
        free(p);
        p = suivant;
    }
    *liste = NULL;
}
