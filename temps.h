#ifndef TEMPS_H
#define TEMPS_H
#include "structures.h"

/* Fait avancer le royaume d'une journée et applique les opérations quotidiennes. */
int avancer_jour(Royaume *r);
void afficher_date_royaume(const Royaume *r);
#endif
