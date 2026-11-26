#include <stdio.h>
#include "progression.h"
#include "batiments.h"

/*
 * Règle de progression simple et facilement ajustable :
 * 10 points par bâtiment construit (hors château), 1 point par 10 habitants.
 * Le niveau augmente à chaque seuil de 100 points.
 */
void mettre_a_jour_progression(Royaume *r)
{
    int points, nb_batiments;
    if (r == NULL) return;

    nb_batiments = compter_batiments(r->batiments);
    points = nb_batiments * 10 + (r->population / 10);
    r->points_progression = points;

    r->niveau_royaume = 1 + points / 100;
    if (r->niveau_royaume < 1) r->niveau_royaume = 1;
}

void afficher_progression(const Royaume *r)
{
    if (r == NULL) return;
    printf("\n--- Progression du royaume ---\n");
    printf("Niveau : %d\n", r->niveau_royaume);
    printf("Points : %d / prochain niveau : %d\n",
           r->points_progression,
           ((r->niveau_royaume) * 100));
}
