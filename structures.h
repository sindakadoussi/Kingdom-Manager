#ifndef STRUCTURES_H
#define STRUCTURES_H

/* Gestion des ressources du royaume */
typedef struct {
    double or;
    int bois;
    int pierre;
    int nourriture;
    int fer;
} Ressources;

/* Types de batiments */
typedef enum {
    CHATEAU,
    FERME,
    SCIERIE,
    CARRIERE,
    MINE_FER,
    CASERNE,
    MAISON,
    ENTREPOT
} TypeBatiment;

/* Informations d'un batiment */
typedef struct {
    int id;
    TypeBatiment type;
    int niveau;
} Batiment;

/* Liste chainee des batiments */
typedef struct NoeudBatiment {
    Batiment batiment;
    struct NoeudBatiment *suivant;
} NoeudBatiment;

/* Configuration des batiments */
typedef struct {
    char nom[30];

    int cout_or;
    int cout_bois;
    int cout_pierre;

    int production;
    int type_production;

    int niveau_requis;

    int effet_niveau1;
    int effet_niveau2;
    int effet_niveau3;

} ConfigurationBatiment;

/* Gestion des evenements aleatoires */
typedef struct {
    int id;
    int jour;
    int type;
    int valeur;
    char description[100];
} Evenement;

/* Informations de l'historique */
typedef struct {
    int jour;
    char description[150];
} Historique;

/* Liste chainee de l'historique */
typedef struct NoeudHistorique {
    Historique historique;
    struct NoeudHistorique *suivant;
} NoeudHistorique;

#endif