#ifndef ECONOMIE_H
#define ECONOMIE_H
#include "structures.h"

void collecter_impots(Royaume *r);
void definir_politique_fiscale(Royaume *r, int politique);
void enregistrer_depense(Royaume *r, double montant);
void afficher_bilan_economique(Royaume r);

#endif
