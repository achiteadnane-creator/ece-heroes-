#include <stdio.h>
#include "affichage.h"

/* =============================================================
   AfficherPlateau
   Affiche simplement le tableau du jeu
============================================================= */
void AfficherPlateau(int tableau_jeu[LIGNES][COLONNES])
{
    printf("\n--- PLATEAU DE JEU ---\n");

    for (int i = 0; i < LIGNES; i++)
    {
        for (int j = 0; j < COLONNES; j++)
        {
            printf("%d ", tableau_jeu[i][j]);
        }
        printf("\n");
    }
}

/* =============================================================
   AfficherInfosNiveau
   Affiche toutes les infos du niveau
============================================================= */
void AfficherInfosNiveau(int niveau, int vies,
                         int contrat[NB_TYPES], int objectif[NB_TYPES],
                         int coups, int temps)
{
    printf("\n--- INFORMATIONS NIVEAU ---\n");

    printf("Niveau actuel     : %d\n", niveau);
    printf("Vies restantes    : %d\n", vies);
    printf("Coups restants    : %d\n", coups);
    printf("Temps restant     : %d secondes\n", temps);

    printf("\nContrat :\n");
    for (int i = 0; i < NB_TYPES; i++)
        printf("  Type %d : %d / %d restants\n", i+1, contrat[i], objectif[i]);
}

/* =============================================================
   GDeplacement
   Modifie ligne et colonne selon la touche
============================================================= */
void GDeplacement(int *ligne, int *colonne, char touche)
{
    if (touche == 'z' && *ligne > 0)
        (*ligne)--;
    else if (touche == 's' && *ligne < LIGNES - 1)
        (*ligne)++;
    else if (touche == 'q' && *colonne > 0)
        (*colonne)--;
    else if (touche == 'd' && *colonne < COLONNES - 1)
        (*colonne)++;
}
