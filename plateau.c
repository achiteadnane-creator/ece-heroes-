#include "plateau.h"
#include <stdlib.h>
#include <time.h>

/* ================= OUTILS INTERNES ================= */

static void initRandom(void) {
    static bool init = false;
    if (!init) {
        srand(time(NULL));
        init = true;
    }
}

static int randomItem(void) {
    return 1 + rand() % NB_ITEMS; // 1..4
}

// Vérifie si placer val en (y,x) crée un match immédiat
static bool creeMatch(int p[PLATEAU_H][PLATEAU_W], int y, int x, int val) {
    if (x >= 2 && p[y][x-1] == val && p[y][x-2] == val) return true;
    if (y >= 2 && p[y-1][x] == val && p[y-2][x] == val) return true;
    return false;
}

/* ================= FONCTIONS ================= */

void genererPlateau(int plateau[PLATEAU_H][PLATEAU_W]) {
    initRandom();

    for (int y = 0; y < PLATEAU_H; y++) {
        for (int x = 0; x < PLATEAU_W; x++) {
            int val;
            do {
                val = randomItem();
            } while (creeMatch(plateau, y, x, val));

            plateau[y][x] = val;
        }
    }
}

void faireTomberItems(int plateau[PLATEAU_H][PLATEAU_W]) {
    for (int x = 0; x < PLATEAU_W; x++) {
        int write = PLATEAU_H - 1;

        for (int y = PLATEAU_H - 1; y >= 0; y--) {
            if (plateau[y][x] != CASE_VIDE) {
                plateau[write][x] = plateau[y][x];
                if (write != y)
                    plateau[y][x] = CASE_VIDE;
                write--;
            }
        }
    }
}

void remplirTrous(int plateau[PLATEAU_H][PLATEAU_W]) {
    initRandom();

    for (int y = 0; y < PLATEAU_H; y++) {
        for (int x = 0; x < PLATEAU_W; x++) {
            if (plateau[y][x] == CASE_VIDE) {
                plateau[y][x] = randomItem();
            }
        }
    }
}

int detecterFigures(int plateau[PLATEAU_H][PLATEAU_W]) {
    int figures = 0;

    // Horizontal
    for (int y = 0; y < PLATEAU_H; y++) {
        for (int x = 0; x < PLATEAU_W - 2; x++) {
            int v = plateau[y][x];
            if (v != CASE_VIDE &&
                v == plateau[y][x+1] &&
                v == plateau[y][x+2]) {
                figures++;
            }
        }
    }

    // Vertical
    for (int x = 0; x < PLATEAU_W; x++) {
        for (int y = 0; y < PLATEAU_H - 2; y++) {
            int v = plateau[y][x];
            if (v != CASE_VIDE &&
                v == plateau[y+1][x] &&
                v == plateau[y+2][x]) {
                figures++;
            }
        }
    }

    return figures;
}

void eliminerItems(int plateau[PLATEAU_H][PLATEAU_W],
                   int contrat_items[NB_ITEMS]) {
    bool mark[PLATEAU_H][PLATEAU_W] = { false };

    // Marquage horizontal
    for (int y = 0; y < PLATEAU_H; y++) {
        for (int x = 0; x < PLATEAU_W - 2; x++) {
            int v = plateau[y][x];
            if (v != CASE_VIDE &&
                v == plateau[y][x+1] &&
                v == plateau[y][x+2]) {

                mark[y][x] = mark[y][x+1] = mark[y][x+2] = true;
            }
        }
    }

    // Marquage vertical
    for (int x = 0; x < PLATEAU_W; x++) {
        for (int y = 0; y < PLATEAU_H - 2; y++) {
            int v = plateau[y][x];
            if (v != CASE_VIDE &&
                v == plateau[y+1][x] &&
                v == plateau[y+2][x]) {

                mark[y][x] = mark[y+1][x] = mark[y+2][x] = true;
            }
        }
    }

    // Suppression + contrat
    for (int y = 0; y < PLATEAU_H; y++) {
        for (int x = 0; x < PLATEAU_W; x++) {
            if (mark[y][x]) {
                int item = plateau[y][x];
                plateau[y][x] = CASE_VIDE;

                if (item >= 1 && item <= NB_ITEMS &&
                    contrat_items[item - 1] > 0) {
                    contrat_items[item - 1]--;
                }
            }
        }
    }

    // Stabilisation
    faireTomberItems(plateau);
    remplirTrous(plateau);
}
