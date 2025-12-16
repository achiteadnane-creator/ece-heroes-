#ifndef PLATEAU_H
#define PLATEAU_H

#include <stdbool.h>

/* ===== PARAMÈTRES DU JEU ===== */
#define PLATEAU_H 10
#define PLATEAU_W 15
#define NB_ITEMS 4

#define CASE_VIDE 0   // 0 = case vide, 1..4 = items

/* ===== FONCTIONS DU MODULE PLATEAU ===== */

// Génère un plateau aléatoire sans match-3 immédiat
void genererPlateau(int plateau[PLATEAU_H][PLATEAU_W]);

// Applique la gravité (les items tombent)
void faireTomberItems(int plateau[PLATEAU_H][PLATEAU_W]);

// Remplit les cases vides avec de nouveaux items
void remplirTrous(int plateau[PLATEAU_H][PLATEAU_W]);

// Détecte les figures (match >= 3)
// Retourne le nombre de figures trouvées
int detecterFigures(int plateau[PLATEAU_H][PLATEAU_W]);

// Supprime les figures, met à jour le contrat,
// puis stabilise le plateau (gravité + remplissage)
void eliminerItems(int plateau[PLATEAU_H][PLATEAU_W],
                   int contrat_items[NB_ITEMS]);

#endif
