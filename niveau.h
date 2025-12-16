#ifndef NIVEAU_H
#define NIVEAU_H

#include <stdbool.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dimensions demandées */
#define NB_LIGNES        10
#define NB_COLONNES      15

/* 5 types d'items : 1..5, 0 = vide */
#define NB_ITEM_TYPES     5

typedef struct {
    int objectif[NB_ITEM_TYPES + 1]; /* index 1..NB_ITEM_TYPES */
    int restant[NB_ITEM_TYPES + 1];  /* index 1..NB_ITEM_TYPES */
    int nb_items;                    /* nb de types réellement demandés */
} ContratItems;

typedef enum {
    DIR_HAUT = 0,
    DIR_BAS,
    DIR_GAUCHE,
    DIR_DROITE
} Direction;

/* API demandée */
int jouerNiveau(int numeroNiveau, int vies);

int Tempsniveau(time_t debut, int duree_max_sec);

int definircontrat(int numeroNiveau, ContratItems *contrat_items,
                   int *coups_restants, int *temps_restants);

bool Coupniveau(int plateau[NB_LIGNES][NB_COLONNES],
                int ligneSelect, int colSelect,
                Direction direction, int *coupsRestants);

bool contratRempli(const ContratItems *contrat_items, int nb_items);

/* Helpers utiles */
void niveaux_set_contrat(ContratItems *contrat_items);
void niveaux_generer_plateau_initial(int plateau[NB_LIGNES][NB_COLONNES], unsigned int seed);
void niveaux_afficher_plateau(int plateau[NB_LIGNES][NB_COLONNES]);

#ifdef __cplusplus
}
#endif

#endif
