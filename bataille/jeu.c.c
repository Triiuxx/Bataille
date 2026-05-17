#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jeu.h.h"
#include "liste.h.h"

#include <windows.h>



int vitesse = 2;






void score(jeu *j, int tour);
void recap(jeu *j, int gagnant);
static void deco(void) {
    printf("\n");
    printf("********************************************\n");
    printf("*            JEU DE LA BATAILLE            *\n");
    printf("********************************************\n");
    printf("\n");
}

void init_jeu(jeu *j) {
    init_file(&j->jo1);
    init_file(&j->jo2);
    j -> nbtours = 0;
    j -> partie_finie = 0;
    printf("creation du jeu de 52 cartes...\n");
    carte *pack = creer_jeu();
    printf("[paquet cree : %d cartes.\n", taille_liste(pack));
    printf("melange du paquet...\n");
    melanger_jeu(&pack);
    printf("distribution des cartes...\n");
    distribuer(j, pack);
    printf("joueur 1 : %d cartes | joueur 2 : %d cartes\n\n", taille_file(&j->jo1), taille_file(&j->jo2));
}
void distribuer(jeu *j, carte *pack) {
    carte *courant = pack;
    int tour_joueur = 1;
    while (courant != NULL) {
        carte *suivant = courant->suivant;
        courant->suivant = NULL;
        if (tour_joueur == 1) {
            enfiler(&j->jo1, courant);
        } else {
            enfiler(&j->jo2, courant);
        }
        if (tour_joueur == 1) {
            tour_joueur = 2;
        } else {
            tour_joueur = 1;
        }
        courant = suivant;
    }
}
int verifier_fin(jeu *j) {
    if (file_vide(&j->jo1) && file_vide(&j->jo2)) {
        return -1; // si aucun joueur n a pas des cartes
    }
    if (file_vide(&j->jo1)) {
        return 2;
    }
    if (file_vide(&j->jo2)) {
        return 1;
    }
    return 0;
}
int gerer_bataille(jeu *j, carte *c1, carte *c2) {
    pile bataille;
    init_pile (&bataille);
    char buf1[32] , buf2[32];
    printf(" BATAILLE ! Cartes cachees posees...\n");
    empiler(&bataille, c1);
    empiler(&bataille, c2);
    while (1) {
        if (file_vide(&j->jo1) || file_vide(&j->jo2)) {
            int gagnant = (!file_vide(&j->jo1)) ? 1 : 2; // ? can replace if and else
            printf("Joueur %d n'a plus de cartes !\n", (gagnant == 1) ? 2 : 1);
            if (gagnant == 1) {
                vider_dans_file(&bataille, &j->jo1);
            } else {
                vider_dans_file(&bataille, &j->jo2);
            }
            return gagnant;
        }
        carte *cachee1 = defiler(&j->jo1);
        carte *cachee2 = defiler(&j->jo2);
        empiler(&bataille, cachee1);
        empiler(&bataille, cachee2);
        printf("  (cartes cachees posees)\n");
        if (file_vide(&j->jo1) || file_vide(&j->jo2)) {
            int gagnant = (!file_vide(&j->jo1)) ? 1 : 2;
            if (gagnant == 1) {
                vider_dans_file(&bataille, &j->jo1);
            } else {
                vider_dans_file(&bataille, &j->jo2);
            }
            return gagnant;
        }
        carte *visible1 = defiler(&j->jo1);
        carte *visible2 = defiler(&j->jo2);
        nom_carte(visible1, buf1, sizeof(buf1));
        nom_carte(visible2, buf2, sizeof(buf2));
        printf("  Joueur 1 decouvre : [%s]\n", buf1);
        printf("  Joueur 2 decouvre : [%s]\n", buf2);

        if (visible1->valeur > visible2->valeur) {
            empiler(&bataille, visible1);
            empiler(&bataille, visible2);
            int nb = taille_pile(&bataille);
            printf("joueur 1 remporte la bataille ! (+%d cartes)\n", nb);
            vider_dans_file(&bataille, &j->jo1);
            return 1;

        }else if (visible2->valeur > visible1->valeur) {
            empiler(&bataille, visible1);
            empiler(&bataille, visible2);
            int nb = taille_pile(&bataille);
            printf("joueur 2 remporte la bataille ! (+%d cartes)\n", nb);
            vider_dans_file(&bataille, &j->jo2);
            return 2;
        }else {
            empiler(&bataille, visible1);
            empiler(&bataille, visible2);
            printf(" ENCORE UNE BATAILLE !\n");
        }
    }
}
int jouer_tour(jeu *j, int tour) {
    char buf1[32], buf2[32];

    printf("\n--- MANCHE %d ---\n", tour);
    carte *c1 = defiler(&j->jo1);
    carte *c2 = defiler(&j->jo2);
    if (c1 == NULL || c2 == NULL) {
        if (c1) enfiler(&j->jo1, c1);
        if (c2) enfiler(&j->jo2, c2);
        return 0;

    }
    nom_carte(c1, buf1, sizeof(buf1));
    nom_carte(c2, buf2, sizeof(buf2));
    printf("Joueur 1 joue : [%s] (valeur = %d)\n", buf1, c1->valeur);
    printf("Joueur 2 joue : [%s] (valeur = %d)\n", buf2, c2->valeur);
    if (c1->valeur > c2->valeur) {
        printf("joueur 1 remporte la manche !\n");
        enfiler(&j->jo1, c1);
        enfiler(&j->jo1, c2);
        score(j, tour);
        attendre();
        return 1;
    } else if (c2->valeur > c1->valeur) {
        printf("joueur 2 remporte la manche !\n");
        enfiler(&j->jo2, c1);
        enfiler(&j->jo2, c2);
        score(j, tour);
        attendre();
        return 2;
    } else {
        int gagnant = gerer_bataille(j, c1, c2);
        score(j, tour);
        attendre();
        return gagnant;
    }
}
void choisir_vitesse(void) {
    int choix = 0;
    printf("\n");
    printf("********************************************\n");
    printf("*         CHOISISSEZ LA VITESSE            *\n");
    printf("********************************************\n");
    printf("  1. Lent    (1 tour par seconde)          \n");
    printf("  2. Rapide  (aussi vite que possible)      \n");
    printf("  3. Manuel  (appuyez ENTREE pour avancer)  \n");
    printf("\nVotre choix : ");
    scanf("%d", &choix);

    if (choix == 1) vitesse = 1;
    else if (choix == 2) vitesse = 2;
    else vitesse = 0;
}
void attendre(void) {
    if (vitesse == 0) {

        printf("  [Appuyez sur ENTREE pour continuer...]\n");
        getchar();
        getchar();
    } else if (vitesse == 1) {
        Sleep(1000);
    }
}
void lancer(jeu *j) {
    deco();
    choisir_vitesse();
    printf("debut de la partie !\n");
    printf("joueur 1 : %d cartes | Joueur 2 : %d cartes\n\n", taille_file (&j->jo1), taille_file(&j->jo2));
    int gagnant = 0;
    int tour = 0;
    while(tour < maxtours) {
        tour++;
        j->nbtours = tour;
        gagnant = verifier_fin(j);
        if (gagnant != 0) break;
        jouer_tour(j, tour);
        gagnant = verifier_fin(j);
        if (gagnant != 0) break;
    }
    if (tour >= maxtours && gagnant == 0) {
        printf("\n MATCH NUL : limite de %d tours atteinte !\n", maxtours);
        gagnant = -1;
    }
    recap(j, gagnant);
}


void score(jeu *j, int tour) {
    (void)tour;
    printf("score -> JO1: %d cartes | JO2: %d cartes\n", taille_file (&j->jo1), taille_file (&j->jo2));
}
void recap(jeu *j, int gagnant) {
    printf("\n");
    printf("********************************************\n");
    printf("*            FIN DE PARTIE                 *\n");
    printf("********************************************\n");
    printf(" Nombre de tours joues : %d\n", j->nbtours);
    printf(" Cartes Joueur 1 : %d\n", taille_file(&j->jo1));
    printf(" Cartes Joueur 2 : %d\n", taille_file(&j->jo2));
    if (gagnant == 1) {
        printf("\n  >>> VICTOIRE DU JOUEUR 1 !\n");
    } else if (gagnant == 2) {
        printf("\n  >>> VICTOIRE DU JOUEUR 2 !\n");
    } else {
        printf("\n  Match nul.\n");
    }
    printf("\n");
}
void liberer_jeu(jeu *j) {
    liberer_file(&j->jo1);
    liberer_file(&j->jo2);
}
