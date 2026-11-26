#include <stdio.h>
#include "economie.h"
#include "constantes.h"

void collecter_impots(Royaume *r)
{
    double taux, revenu;
    int variation;
    if (r == NULL) return;
    switch (r->politique_fiscale) {
    case POLITIQUE_FAIBLE: taux = TAXE_FAIBLE; variation = BONHEUR_TAXE_FAIBLE; break;
    case POLITIQUE_ELEVEE: taux = TAXE_ELEVEE; variation = BONHEUR_TAXE_ELEVEE; break;
    default: taux = TAXE_NORMALE; variation = BONHEUR_TAXE_NORMALE; break;
    }
    revenu = taux * r->population;
    r->ressources.or += revenu;
    r->economie.revenus_jour += revenu;
    r->economie.revenus_total += revenu;
    r->bonheur += variation;
    if (r->bonheur < 0) r->bonheur = 0;
    if (r->bonheur > 100) r->bonheur = 100;
}

void definir_politique_fiscale(Royaume *r, int politique)
{
    if (r == NULL || politique < POLITIQUE_FAIBLE || politique > POLITIQUE_ELEVEE) {
        printf("Politique fiscale invalide.\n");
        return;
    }
    r->politique_fiscale = (PolitiqueFiscale)politique;
    printf("Politique fiscale mise a jour.\n");
}

void enregistrer_depense(Royaume *r, double montant)
{
    if (r == NULL || montant <= 0) return;
    r->economie.depenses_jour += montant;
    r->economie.depenses_total += montant;
}

void afficher_bilan_economique(Royaume r)
{
    const char *politique = "Normale";
    if (r.politique_fiscale == POLITIQUE_FAIBLE) politique = "Faible";
    else if (r.politique_fiscale == POLITIQUE_ELEVEE) politique = "Elevee";
    printf("\n--- Bilan economique ---\n");
    printf("Politique fiscale : %s\n", politique);
    printf("Revenus aujourd'hui : %.2f or\n", r.economie.revenus_jour);
    printf("Depenses aujourd'hui : %.2f or\n", r.economie.depenses_jour);
    printf("Revenus cumules : %.2f or\n", r.economie.revenus_total);
    printf("Depenses cumulees : %.2f or\n", r.economie.depenses_total);
    printf("Tresor : %.2f or\n", r.ressources.or);
}
