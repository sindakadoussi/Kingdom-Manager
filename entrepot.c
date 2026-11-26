#include <stdio.h>
#include "entrepot.h"
#include "ressources.h"
#include "batiments.h"
#include "economie.h"

void mettre_a_jour_capacite_stockage(Royaume *r)
{
    if (r == NULL) return;
    switch (r->niveau_entrepot) {
    case 1: r->capacite_stockage = STOCK_ENTREPOT_N1; break;
    case 2: r->capacite_stockage = STOCK_ENTREPOT_N2; break;
    case 3: r->capacite_stockage = STOCK_ENTREPOT_N3; break;
    default: r->capacite_stockage = STOCK_BASE; break;
    }
}

int construire_entrepot(Royaume *r)
{
    if (r == NULL) return 0;
    /* L'entrepot est construit via construire_batiment afin d'ajouter son noeud. */
    return construire_batiment(r, BATIMENT_ENTREPOT);
}

int ameliorer_entrepot(Royaume *r)
{
    NoeudBatiment *p;
    if (r == NULL || r->niveau_entrepot <= 0) {
        printf("Aucun entrepot a ameliorer.\n");
        return 0;
    }
    for (p = r->batiments; p; p = p->suivant) {
        if (p->batiment.type == BATIMENT_ENTREPOT)
            return ameliorer_batiment(r, p->batiment.id);
    }
    printf("Entrepot introuvable dans la liste des batiments.\n");
    return 0;
}
