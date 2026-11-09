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

/* Informations generales du royaume */
typedef struct {
    char nom[50];

    int niveau;
    int jour;

    Ressources ressources;

    int population;
    int bonheur;
    int soldats;
    int niveau_equipement;

    int politique_fiscale;
    int jours_famine;

    int capacite_stockage;
    int capacite_population;

    int victoires;
    int defaites;

    NoeudBatiment *batiments;
    NoeudHistorique *historique;

   struct {
    int batiments_construits;
    int jours_joues;
    int ameliorations;
    int soldats_recrutes;
    int victoires;
    int defaites;
    double revenus_totaux;
    double depenses_totales;
} statistiques;

} Royaume;

#endif