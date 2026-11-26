#include <stdio.h>
#include "ressources.h"

const char *nom_ressource(TypeRessource type)
{
    switch (type) {
    case RESSOURCE_BOIS: return "Bois";
    case RESSOURCE_PIERRE: return "Pierre";
    case RESSOURCE_NOURRITURE: return "Nourriture";
    case RESSOURCE_FER: return "Fer";
    case RESSOURCE_OR: return "Or";
    default: return "Inconnue";
    }
}

int obtenir_quantite(Ressources r, TypeRessource type)
{
    switch (type) {
    case RESSOURCE_BOIS: return r.bois;
    case RESSOURCE_PIERRE: return r.pierre;
    case RESSOURCE_NOURRITURE: return r.nourriture;
    case RESSOURCE_FER: return r.fer;
    case RESSOURCE_OR: return (int)r.or;
    default: return 0;
    }
}

void afficher_ressources(Ressources r)
{
    printf("\n--- Ressources ---\n");
    printf("Bois       : %d\n", r.bois);
    printf("Pierre     : %d\n", r.pierre);
    printf("Nourriture : %d\n", r.nourriture);
    printf("Fer        : %d\n", r.fer);
    printf("Or         : %.2f\n", r.or);
}

int ajouter_ressource(Royaume *r, TypeRessource type, int quantite)
{
    int *stock = NULL, capacite, accepte;
    if (r == NULL || quantite <= 0) return 0;
    if (type == RESSOURCE_OR) {
        r->ressources.or += quantite;
        return quantite;
    }
    switch (type) {
    case RESSOURCE_BOIS: stock = &r->ressources.bois; break;
    case RESSOURCE_PIERRE: stock = &r->ressources.pierre; break;
    case RESSOURCE_NOURRITURE: stock = &r->ressources.nourriture; break;
    case RESSOURCE_FER: stock = &r->ressources.fer; break;
    default: return 0;
    }
    capacite = r->capacite_stockage > 0 ? r->capacite_stockage : STOCK_BASE;
    accepte = capacite - *stock;
    if (accepte < 0) accepte = 0;
    if (accepte > quantite) accepte = quantite;
    *stock += accepte;
    if (accepte < quantite)
        printf("Stockage plein : %d unite(s) non stockee(s).\n", quantite - accepte);
    return accepte;
}

int retirer_ressource(Royaume *r, TypeRessource type, int quantite)
{
    int *stock = NULL;
    if (r == NULL || quantite <= 0) return 0;
    if (type == RESSOURCE_OR) {
        if (r->ressources.or < quantite) return 0;
        r->ressources.or -= quantite;
        return quantite;
    }
    switch (type) {
    case RESSOURCE_BOIS: stock = &r->ressources.bois; break;
    case RESSOURCE_PIERRE: stock = &r->ressources.pierre; break;
    case RESSOURCE_NOURRITURE: stock = &r->ressources.nourriture; break;
    case RESSOURCE_FER: stock = &r->ressources.fer; break;
    default: return 0;
    }
    if (*stock < quantite) return 0;
    *stock -= quantite;
    return quantite;
}
