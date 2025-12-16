#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

// Sauvegarde la progression
int sauvegarderPartie(char pseudo[], int niveau, int vies);

// Charge une progression
int chargerPartie(char pseudo[], int* niveau, int* vies);

// Vérifie si un pseudo existe
int pseudoExiste(char pseudo[]);

#endif