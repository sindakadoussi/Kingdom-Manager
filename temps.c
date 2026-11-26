#include <stdio.h>
#include "temps.h"
#include "economie.h"
#include "batiments.h"
#include "ressources.h"
#include "progression.h"

int avancer_jour(Royaume *r)
{
    Ressources production = {0, 0, 0, 0, 0};

    if (r == NULL) return 0;

    r->jour++;
    calculer_production_batiments(r->batiments, &production);

    /* Les ressources produites sont ajoutées en respectant la capacité. */
    ajouter_ressource(r, RESSOURCE_BOIS, production.bois);
    ajouter_ressource(r, RESSOURCE_PIERRE, production.pierre);
    ajouter_ressource(r, RESSOURCE_NOURRITURE, production.nourriture);
    ajouter_ressource(r, RESSOURCE_FER, production.fer);

    collecter_impots(r);
    mettre_a_jour_progression(r);
    return 1;
}

void afficher_date_royaume(const Royaume *r)
{
    if (r == NULL) return;
    printf("Jour : %d\n", r->jour);
}
