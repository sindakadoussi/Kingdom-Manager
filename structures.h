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

#endif