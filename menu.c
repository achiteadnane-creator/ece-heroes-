#include <stdio.h>
#include "menu.h"
#include "affichage_console.h"

void afficherMenu() {
    clrscr();
    text_color(YELLOW);
    gotoxy(20, 2);
    printf("╔════════════════════════════════════════╗");
    gotoxy(20, 3);
    text_color(LIGHTCYAN);
    printf("║         ECE HEROES - MENU              ║");
    gotoxy(20, 4);
    text_color(YELLOW);
    printf("╠════════════════════════════════════════╣");
    gotoxy(20, 5);
    text_color(WHITE);
    printf("║                                        ║");
    gotoxy(20, 6);
    printf("║  1. Lire les regles du jeu             ║");
    gotoxy(20, 7);
    printf("║  2. Commencer une nouvelle partie      ║");
    gotoxy(20, 8);
    printf("║  3. Reprendre une partie               ║");
    gotoxy(20, 9);
    printf("║  4. Quitter                            ║");
    gotoxy(20, 10);
    printf("║                                        ║");
    gotoxy(20, 11);
    text_color(YELLOW);
    printf("╚════════════════════════════════════════╝");
    text_color(WHITE);
}

void afficherRegles() {
    clrscr();
    text_color(LIGHTCYAN);
    gotoxy(10, 1);
    printf("╔══════════════════════════════════════════════════════╗");
    gotoxy(10, 2);
    printf("║              REGLES DU JEU ECE HEROES                ║");
    gotoxy(10, 3);
    printf("╚══════════════════════════════════════════════════════╝");
    
    text_color(WHITE);
    gotoxy(10, 5);
    printf("OBJECTIF :");
    gotoxy(10, 6);
    printf("  - Remplir un contrat en eliminant des items");
    gotoxy(10, 7);
    printf("  - Temps limite et nombre de coups limites");
    
    gotoxy(10, 9);
    text_color(YELLOW);
    printf("FIGURES SPECIALES :");
    text_color(WHITE);
    gotoxy(10, 10);
    printf("  - 6 items alignes : elimine TOUS les items du meme type");
    gotoxy(10, 11);
    printf("  - Croix (9 items) : elimine ligne et colonne");
    gotoxy(10, 12);
    printf("  - Carre 4x4 : elimine les 16 items du carre");
    gotoxy(10, 13);
    printf("  - 4 items alignes : elimine les 4 items");
    
    gotoxy(10, 15);
    text_color(LIGHTGREEN);
    printf("CONTROLES :");
    text_color(WHITE);
    gotoxy(10, 16);
    printf("  - Z/Q/S/D ou FLECHES : deplacer le curseur");
    gotoxy(10, 17);
    printf("  - ESPACE : selectionner/deselectionner un item");
    gotoxy(10, 18);
    printf("  - Direction apres selection : permuter les items");
    
    gotoxy(10, 20);
    text_color(LIGHTRED);
    printf("Appuyez sur une touche pour revenir au menu...");
    text_color(WHITE);
    
    getch();
}

int attendreChoixMenu() {
    int choix;
    gotoxy(20, 13);
    text_color(LIGHTGREEN);
    printf("Votre choix : ");
    text_color(WHITE);
    scanf("%d", &choix);
    
    while (choix < 1 || choix > 4) {
        gotoxy(20, 14);
        text_color(LIGHTRED);
        printf("Choix invalide! Entrez 1-4 : ");
        text_color(WHITE);
        scanf("%d", &choix);
    }
    
    return choix;
}