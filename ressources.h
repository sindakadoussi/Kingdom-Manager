#ifndef RESSOURCES_H
#define RESSOURCES_H
#include "structures.h"

void afficher_ressources(Ressources r);
int ajouter_ressource(Royaume *r, TypeRessource type, int quantite);
int retirer_ressource(Royaume *r, TypeRessource type, int quantite);
int obtenir_quantite(Ressources r, TypeRessource type);
const char *nom_ressource(TypeRessource type);

#endif
