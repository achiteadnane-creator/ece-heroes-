#ifndef PLATEAU_H
#define PLATEAU_H

void initialiserPlateau(int plateau[25][45]); //initialise le plateau de jeu 

int detecterFigures(int plateau[25][45]); // detecte les différentes figure 

void eliminerItems(int plateau[25][45], int contrat[5]); // supprime les items 

void faireTomberItems(int plateau[25][45]); //fait tomber les items 

void completerPlateau(int plateau[25][45]); //

void verifierStabilite(int plateau[25][45], int contrat[5]);

#endif