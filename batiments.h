#ifndef BATIMENTS_H
#define BATIMENTS_H
#include "structures.h"

void afficher_batiments(NoeudBatiment *liste);
int construire_batiment(Royaume *r, int type);
int ajouter_batiment(NoeudBatiment **liste, Batiment b);
Batiment *rechercher_batiment(NoeudBatiment *liste, int id);
int supprimer_batiment(Royaume *r, int id);
int ameliorer_batiment(Royaume *r, int id);
void calculer_production_batiments(NoeudBatiment *liste, Ressources *production);
int compter_batiments(NoeudBatiment *liste);
void liberer_batiments(NoeudBatiment **liste);

#endif
