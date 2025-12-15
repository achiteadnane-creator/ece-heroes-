#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "menu.h"

void afficherMenu() {
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║         ECE HEROES - MENU              ║\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║                                        ║\n");
    printf("║  1. Lire les regles du jeu             ║\n");
    printf("║  2. Commencer une nouvelle partie      ║\n");
    printf("║  3. Reprendre une partie               ║\n");
    printf("║  4. Quitter                            ║\n");
    printf("║                                        ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("\n");
}

void afficherRegles() {
    system("cls");
    printf("\n╔══════════════════════════════════════════════════════╗\n");
    printf("║              REGLES DU JEU                           ║\n");
    printf("╚══════════════════════════════════════════════════════╝\n\n");
    
    printf("OBJECTIF :\n");
    printf("  - Remplir un contrat en eliminant des items\n");
    printf("  - Temps limite et nombre de coups limites\n\n");
    
    printf("FIGURES SPECIALES :\n");
    printf("  - 6 items alignes : elimine TOUS les items du meme type\n");
    printf("  - Croix (9 items) : elimine ligne et colonne\n");
    printf("  - Carre 4x4 : elimine les 16 items du carre\n");
    printf("  - 4 items alignes : elimine les 4 items\n\n");
    
    printf("CONTROLES :\n");
    printf("  - Z/Q/S/D ou FLECHES : deplacer le curseur\n");
    printf("  - ESPACE : selectionner/deselectionner un item\n");
    printf("  - Direction apres selection : permuter les items\n\n");
    
    printf("Appuyez sur une touche pour revenir au menu...\n");
    _getch();
    system("cls");
}

int attendreChoixMenu() {
    int choix;
    printf("Votre choix : ");
    scanf("%d", &choix);
    
    
    while (choix < 1 || choix > 4) {
        printf("Choix invalide. Entrez un nombre entre 1 et 4 : ");
        scanf("%d", &choix);
    }
    
    return choix;
}