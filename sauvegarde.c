#include <stdio.h>
#include <string.h>
#include "sauvegarde.h"

int sauvegarderPartie(char pseudo[], int niveau, int vies) {
    FILE* fichier = fopen("sauvegardes.txt", "a");
    if (fichier == NULL) {
        printf("Erreur: impossible de sauvegarder.\n");
        return 0;
    }
    
    fprintf(fichier, "%s %d %d\n", pseudo, niveau, vies);
    fclose(fichier);
    
    printf("Progression sauvegardee !\n");
    return 1;
}

int chargerPartie(char pseudo[], int* niveau, int* vies) {
    FILE* fichier = fopen("sauvegardes.txt", "r");
    if (fichier == NULL) {
        printf("Aucune sauvegarde trouvee.\n");
        return 0;
    }
    
    char pseudoLu[50];
    int niveauLu, viesLu;
    
    while (fscanf(fichier, "%s %d %d", pseudoLu, &niveauLu, &viesLu) == 3) {
        if (strcmp(pseudoLu, pseudo) == 0) {
            *niveau = niveauLu;
            *vies = viesLu;
            fclose(fichier);
            printf("Partie chargee: Niveau %d, %d vies\n", *niveau, *vies);
            return 1;
        }
    }
    
    fclose(fichier);
    printf("Pseudo non trouve.\n");
    return 0;
}

int pseudoExiste(char pseudo[]) {
    FILE* fichier = fopen("sauvegardes.txt", "r");
    if (fichier == NULL) {
        return 0;
    }
    
    char pseudoLu[50];
    int niveau, vies;
    
    while (fscanf(fichier, "%s %d %d", pseudoLu, &niveau, &vies) == 3) {
        if (strcmp(pseudoLu, pseudo) == 0) {
            fclose(fichier);
            return 1;
        }
    }
    
    fclose(fichier);
    return 0;
}