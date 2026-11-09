
#ifndef ROYAUME_H
#define ROYAUME_H

#include "structures.h"

/* Initialiser les valeurs du royaume */
void initialiser_royaume(Royaume *r);

/* Créer une nouvelle partie */
void creer_royaume(Royaume *r);

/* Afficher les informations du royaume */
void afficher_royaume(const Royaume *r);

/* Afficher le tableau de bord */
void afficher_tableau_bord(const Royaume *r);

/* Ajouter un bâtiment à la liste */
int ajouter_batiment(Royaume *r, TypeBatiment type, int niveau);

/* Libérer la mémoire des bâtiments */
void liberer_batiments(NoeudBatiment **liste);

/* Libérer la mémoire de l'historique */
void liberer_historique(NoeudHistorique **liste);

#endif
