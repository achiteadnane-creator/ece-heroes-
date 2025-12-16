#include "niveaux.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ==================== Etat interne ==================== */
static ContratItems *g_contrat_ptr = NULL;

void niveaux_set_contrat(ContratItems *contrat_items) {
    g_contrat_ptr = contrat_items;
}

/* ==================== Utilitaires ==================== */
static int clamp_int(int v, int lo, int hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

static bool in_bounds(int r, int c) {
    return (r >= 0 && r < NB_LIGNES && c >= 0 && c < NB_COLONNES);
}

static int rand_item(void) {
    return (rand() % NB_ITEM_TYPES) + 1; /* 1..NB_ITEM_TYPES */
}

static void swap_int(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

static bool parse_dir(char ch, Direction *out) {
    switch (ch) {
        case 'u': case 'U': *out = DIR_HAUT;   return true;
        case 'd': case 'D': *out = DIR_BAS;    return true;
        case 'l': case 'L': *out = DIR_GAUCHE; return true;
        case 'r': case 'R': *out = DIR_DROITE; return true;
        default: return false;
    }
}

/* ==================== Détection/élimination ==================== */

/* Marque les cases à supprimer selon :
 * - suite >= 6 : supprime tous les items de ce type sur le plateau
 * - croix de 9 (bras longueur 2) : supprime type t sur ligne+col du centre
 * - carré 4x4 : supprime les 16
 * - suite >= 4 : supprime la suite
 */
static int scan_and_mark(int plateau[NB_LIGNES][NB_COLONNES],
                         bool mark[NB_LIGNES][NB_COLONNES]) {
    memset(mark, 0, sizeof(bool) * NB_LIGNES * NB_COLONNES);

    bool remove_all[NB_ITEM_TYPES + 1];
    memset(remove_all, 0, sizeof(remove_all));

    /* 1) runs >= 6 => remove_all */
    for (int r = 0; r < NB_LIGNES; r++) {
        int c = 0;
        while (c < NB_COLONNES) {
            int t = plateau[r][c];
            if (t == 0) { c++; continue; }
            int start = c;
            while (c < NB_COLONNES && plateau[r][c] == t) c++;
            int len = c - start;
            if (len >= 6) remove_all[t] = true;
        }
    }
    for (int c = 0; c < NB_COLONNES; c++) {
        int r = 0;
        while (r < NB_LIGNES) {
            int t = plateau[r][c];
            if (t == 0) { r++; continue; }
            int start = r;
            while (r < NB_LIGNES && plateau[r][c] == t) r++;
            int len = r - start;
            if (len >= 6) remove_all[t] = true;
        }
    }

    for (int r = 0; r < NB_LIGNES; r++) {
        for (int c = 0; c < NB_COLONNES; c++) {
            int t = plateau[r][c];
            if (t != 0 && t <= NB_ITEM_TYPES && remove_all[t]) mark[r][c] = true;
        }
    }

    /* 2) croix de 9 : nécessite au moins marge 2 */
    if (NB_LIGNES >= 5 && NB_COLONNES >= 5) {
        for (int r = 2; r < NB_LIGNES - 2; r++) {
            for (int c = 2; c < NB_COLONNES - 2; c++) {
                int t = plateau[r][c];
                if (t == 0) continue;

                if (plateau[r-1][c] == t && plateau[r-2][c] == t &&
                    plateau[r+1][c] == t && plateau[r+2][c] == t &&
                    plateau[r][c-1] == t && plateau[r][c-2] == t &&
                    plateau[r][c+1] == t && plateau[r][c+2] == t) {

                    for (int cc = 0; cc < NB_COLONNES; cc++)
                        if (plateau[r][cc] == t) mark[r][cc] = true;

                    for (int rr = 0; rr < NB_LIGNES; rr++)
                        if (plateau[rr][c] == t) mark[rr][c] = true;
                }
            }
        }
    }

    /* 3) carré 4x4 */
    if (NB_LIGNES >= 4 && NB_COLONNES >= 4) {
        for (int r = 0; r <= NB_LIGNES - 4; r++) {
            for (int c = 0; c <= NB_COLONNES - 4; c++) {
                int t = plateau[r][c];
                if (t == 0) continue;

                bool ok = true;
                for (int dr = 0; dr < 4 && ok; dr++) {
                    for (int dc = 0; dc < 4; dc++) {
                        if (plateau[r+dr][c+dc] != t) { ok = false; break; }
                    }
                }
                if (ok) {
                    for (int dr = 0; dr < 4; dr++)
                        for (int dc = 0; dc < 4; dc++)
                            mark[r+dr][c+dc] = true;
                }
            }
        }
    }

    /* 4) runs >= 4 */
    for (int r = 0; r < NB_LIGNES; r++) {
        int c = 0;
        while (c < NB_COLONNES) {
            int t = plateau[r][c];
            if (t == 0) { c++; continue; }
            int start = c;
            while (c < NB_COLONNES && plateau[r][c] == t) c++;
            int len = c - start;
            if (len >= 4) for (int cc = start; cc < start + len; cc++) mark[r][cc] = true;
        }
    }
    for (int c = 0; c < NB_COLONNES; c++) {
        int r = 0;
        while (r < NB_LIGNES) {
            int t = plateau[r][c];
            if (t == 0) { r++; continue; }
            int start = r;
            while (r < NB_LIGNES && plateau[r][c] == t) r++;
            int len = r - start;
            if (len >= 4) for (int rr = start; rr < start + len; rr++) mark[rr][c] = true;
        }
    }

    int count = 0;
    for (int r = 0; r < NB_LIGNES; r++)
        for (int c = 0; c < NB_COLONNES; c++)
            if (mark[r][c]) count++;

    return count;
}

static void apply_marked(int plateau[NB_LIGNES][NB_COLONNES],
                         bool mark[NB_LIGNES][NB_COLONNES],
                         int eliminated[NB_ITEM_TYPES + 1]) {
    for (int t = 0; t <= NB_ITEM_TYPES; t++) eliminated[t] = 0;

    for (int r = 0; r < NB_LIGNES; r++) {
        for (int c = 0; c < NB_COLONNES; c++) {
            if (!mark[r][c]) continue;
            int t = plateau[r][c];
            if (t <= 0 || t > NB_ITEM_TYPES) continue;
            plateau[r][c] = 0;
            eliminated[t]++;
        }
    }
}

static void apply_gravity_and_refill(int plateau[NB_LIGNES][NB_COLONNES]) {
    for (int c = 0; c < NB_COLONNES; c++) {
        int write_r = NB_LIGNES - 1;
        for (int r = NB_LIGNES - 1; r >= 0; r--) {
            if (plateau[r][c] != 0) {
                if (write_r != r) {
                    plateau[write_r][c] = plateau[r][c];
                    plateau[r][c] = 0;
                }
                write_r--;
            }
        }
        for (int r = write_r; r >= 0; r--) {
            plateau[r][c] = rand_item();
        }
    }
}

static void update_contrat_from_elim(const int eliminated[NB_ITEM_TYPES + 1]) {
    if (!g_contrat_ptr) return;

    for (int t = 1; t <= NB_ITEM_TYPES; t++) {
        if (g_contrat_ptr->restant[t] > 0) {
            g_contrat_ptr->restant[t] -= eliminated[t];
            if (g_contrat_ptr->restant[t] < 0) g_contrat_ptr->restant[t] = 0;
        }
    }
}

static void stabilize(int plateau[NB_LIGNES][NB_COLONNES]) {
    bool mark[NB_LIGNES][NB_COLONNES];

    for (int loops = 0; loops < 200; loops++) {
        int m = scan_and_mark(plateau, mark);
        if (m == 0) return;

        int eliminated[NB_ITEM_TYPES + 1];
        apply_marked(plateau, mark, eliminated);
        update_contrat_from_elim(eliminated);
        apply_gravity_and_refill(plateau);
    }
}

/* ==================== API ==================== */

int Tempsniveau(time_t debut, int duree_max_sec) {
    time_t now = time(NULL);
    double elapsed = difftime(now, debut);
    int restant = duree_max_sec - (int)elapsed;
    return (restant < 0) ? 0 : restant;
}

int definircontrat(int numeroNiveau, ContratItems *contrat_items,
                   int *coups_restants, int *temps_restants) {
    if (!contrat_items || !coups_restants || !temps_restants) return 0;

    /* Ajusté pour un plateau plus petit (10x15 = 150 cases) */
    const int max_niveaux = 3;

    const int temps_par_niveau[4] = {0, 50, 65, 80}; /* secondes */
    const int coups_par_niveau[4] = {0, 20, 18, 16}; /* coups */

    int lvl = clamp_int(numeroNiveau, 1, max_niveaux);

    *temps_restants = temps_par_niveau[lvl];
    *coups_restants = coups_par_niveau[lvl];

    memset(contrat_items, 0, sizeof(*contrat_items));

    int nb_types = (lvl == 1) ? 2 : (lvl == 2 ? 3 : 4);

    bool used[NB_ITEM_TYPES + 1];
    memset(used, 0, sizeof(used));

    for (int k = 0; k < nb_types; k++) {
        int t;
        do { t = rand_item(); } while (used[t]);
        used[t] = true;

        /* objectifs plus petits (plateau plus petit) */
        int base = 10 + 4 * lvl;        /* lvl1 ~14, lvl2 ~18, lvl3 ~22 */
        int jitter = rand() % 5;        /* 0..4 */
        int obj = base + jitter + k * 2;

        contrat_items->objectif[t] = obj;
        contrat_items->restant[t]  = obj;
    }

    contrat_items->nb_items = nb_types;
    return nb_types;
}

bool contratRempli(const ContratItems *contrat_items, int nb_items) {
    (void)nb_items;
    if (!contrat_items) return false;

    for (int t = 1; t <= NB_ITEM_TYPES; t++) {
        if (contrat_items->objectif[t] > 0 && contrat_items->restant[t] > 0)
            return false;
    }
    return true;
}

bool Coupniveau(int plateau[NB_LIGNES][NB_COLONNES],
                int ligneSelect, int colSelect,
                Direction direction, int *coupsRestants) {
    if (!plateau || !coupsRestants) return false;
    if (*coupsRestants <= 0) return false;
    if (!in_bounds(ligneSelect, colSelect)) return false;

    int dr = 0, dc = 0;
    switch (direction) {
        case DIR_HAUT:   dr = -1; break;
        case DIR_BAS:    dr =  1; break;
        case DIR_GAUCHE: dc = -1; break;
        case DIR_DROITE: dc =  1; break;
        default: return false;
    }

    int r2 = ligneSelect + dr;
    int c2 = colSelect + dc;
    if (!in_bounds(r2, c2)) return false;

    swap_int(&plateau[ligneSelect][colSelect], &plateau[r2][c2]);

    bool mark[NB_LIGNES][NB_COLONNES];
    int m = scan_and_mark(plateau, mark);
    if (m == 0) {
        swap_int(&plateau[ligneSelect][colSelect], &plateau[r2][c2]);
        return false;
    }

    (*coupsRestants)--;

    /* applique suppressions + cascades */
    stabilize(plateau);

    return true;
}

void niveaux_generer_plateau_initial(int plateau[NB_LIGNES][NB_COLONNES], unsigned int seed) {
    srand(seed);

    bool mark[NB_LIGNES][NB_COLONNES];
    for (int tries = 0; tries < 2000; tries++) {
        for (int r = 0; r < NB_LIGNES; r++)
            for (int c = 0; c < NB_COLONNES; c++)
                plateau[r][c] = rand_item();

        if (scan_and_mark(plateau, mark) == 0) return;
    }

    /* sécurité : si jamais trop de tentatives */
    stabilize(plateau);
}

void niveaux_afficher_plateau(int plateau[NB_LIGNES][NB_COLONNES]) {
    const char map[NB_ITEM_TYPES + 1] = {' ', 'A', 'B', 'C', 'D', 'E'};
    for (int r = 0; r < NB_LIGNES; r++) {
        for (int c = 0; c < NB_COLONNES; c++) {
            int v = plateau[r][c];
            if (v < 0 || v > NB_ITEM_TYPES) v = 0;
            putchar(map[v]);
            putchar(' ');
        }
        putchar('\n');
    }
}

static void afficher_contrat_simple(const ContratItems *c) {
    printf("Contrat: ");
    for (int t = 1; t <= NB_ITEM_TYPES; t++) {
        if (c->objectif[t] > 0) {
            printf("[T%d %d/%d] ", t, c->objectif[t] - c->restant[t], c->objectif[t]);
        }
    }
    printf("\n");
}

int jouerNiveau(int numeroNiveau, int vies) {
    (void)vies;

    int plateau[NB_LIGNES][NB_COLONNES];
    ContratItems contrat;

    int coups_restants = 0;
    int temps_restants = 0;

    unsigned int seed = (unsigned int)time(NULL) ^ (unsigned int)(numeroNiveau * 2654435761u);
    niveaux_generer_plateau_initial(plateau, seed);

    niveaux_set_contrat(&contrat);
    definircontrat(numeroNiveau, &contrat, &coups_restants, &temps_restants);

    time_t debut = time(NULL);
    int duree_max = temps_restants;

    while (1) {
        int t = Tempsniveau(debut, duree_max);

        printf("\n=== NIVEAU %d ===\n", numeroNiveau);
        printf("Temps restant : %d s | Coups restants : %d\n", t, coups_restants);
        afficher_contrat_simple(&contrat);

        if (contratRempli(&contrat, contrat.nb_items)) {
            printf(">> Contrat rempli ! Victoire.\n");
            return 1;
        }
        if (t <= 0 || coups_restants <= 0) {
            printf(">> Temps/coups ecoules. Defaite.\n");
            return 0;
        }

        niveaux_afficher_plateau(plateau);

        printf("Entrez un coup : ligne col dir(u/d/l/r) (ex: 3 7 r)\n> ");
        int r, c;
        char dch;
        if (scanf("%d %d %c", &r, &c, &dch) != 3) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("Saisie invalide.\n");
            continue;
        }

        Direction dir;
        if (!parse_dir(dch, &dir)) {
            printf("Direction invalide.\n");
            continue;
        }

        if (!Coupniveau(plateau, r, c, dir, &coups_restants)) {
            printf("Coup invalide (pas de figure / hors limites / plus de coups).\n");
        }
    }
}
