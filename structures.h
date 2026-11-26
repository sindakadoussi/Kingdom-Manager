#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdbool.h>
#include "constantes.h"

/* Types de ressources. L'or est une monnaie et n'est pas limité par l'entrepôt. */
typedef enum {
    RESSOURCE_BOIS = 0,
    RESSOURCE_PIERRE,
    RESSOURCE_NOURRITURE,
    RESSOURCE_FER,
    RESSOURCE_OR,
    NB_RESSOURCES
} TypeRessource;

typedef struct {
    int bois;
    int pierre;
    int nourriture;
    int fer;
    double or;
} Ressources;

typedef enum {
    BATIMENT_CHATEAU = 0,
    BATIMENT_FERME,
    BATIMENT_SCIERIE,
    BATIMENT_CARRIERE,
    BATIMENT_MINE_FER,
    BATIMENT_MAISON,
    BATIMENT_CASERNE,
    BATIMENT_ENTREPOT,
    NB_TYPES_BATIMENTS
} TypeBatiment;

typedef struct {
    int id;
    TypeBatiment type;
    int niveau;
    char nom[NOM_BATIMENT_MAX];
} Batiment;

typedef struct NoeudBatiment {
    Batiment batiment;
    struct NoeudBatiment *suivant;
} NoeudBatiment;

typedef enum {
    POLITIQUE_FAIBLE = 0,
    POLITIQUE_NORMALE,
    POLITIQUE_ELEVEE
} PolitiqueFiscale;

typedef struct {
    double revenus_jour;
    double depenses_jour;
    double revenus_total;
    double depenses_total;
} BilanEconomique;

typedef struct {
    char nom[NOM_ROYAUME_MAX];
    char nom_joueur[NOM_JOUEUR_MAX];

    Ressources ressources;
    Ressources production_jour;

    NoeudBatiment *batiments;
    int prochain_id_batiment;

    int population;
    int capacite_population;
    int bonheur;                 /* borné entre 0 et 100 */
    int capacite_stockage;       /* par ressource stockable */
    int niveau_entrepot;         /* 0 = aucun, 1..3 */
    int jour;

    PolitiqueFiscale politique_fiscale;
    BilanEconomique economie;

    int niveau_royaume;
    int points_progression;
} Royaume;

#endif
