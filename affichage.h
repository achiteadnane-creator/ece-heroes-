#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#define LIGNES 25
#define COLONNES 45
#define NB_TYPES 5

/* -------------------------------------------------------------
   AfficherPlateau
   Affiche le tableau du jeu
--------------------------------------------------------------*/
void AfficherPlateau(int tableau_jeu[LIGNES][COLONNES]);

/* -------------------------------------------------------------
   AfficherInfosNiveau
   Affiche :
   - niveau_actuel
   - vies_restantes
   - contrat_items
   - objectif_items
   - coups_restants
   - temps_restants
--------------------------------------------------------------*/
void AfficherInfosNiveau(int niveau, int vies,
                         int contrat[NB_TYPES], int objectif[NB_TYPES],
                         int coups, int temps);

/* -------------------------------------------------------------
   GDeplacement
   Modifie pos_item_selx et pos_item_sely selon la touche
   Entrée : ligne, colonne, touche
   Sortie : ligne et colonne modifiées
--------------------------------------------------------------*/
void GDeplacement(int *ligne, int *colonne, char touche);

#endif
