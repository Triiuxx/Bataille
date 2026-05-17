#ifndef jeu_h
#define jeu_h
#define maxtours 10000
#include "carte.h.h"
#include "file.h.h"
#include "pile.h.h"
extern int vitesse;
//description de la structure et la logique du jeu


typedef struct { //struct du jeu
    file jo1;
    file jo2;
    int nbtours;
    int partie_finie;
}jeu;
void init_jeu (jeu *j); //initialisation du jeu
void distribuer (jeu *j, carte *pack); // distribution des cartes pour chque joueur
int verifier_fin (jeu *j); // verifie si la partie est terminee
int gerer_bataille (jeu *j , carte *c1, carte *c2); // verifie s'il y a une egalite
int jouer_tour(jeu *j, int tour); // gere un tour
void choisir_vitesse(void);
void attendre(void);
void score (jeu *j, int tour); // afficher le score
void recap (jeu *j, int gagnant); // afficher le recap a la fin de  la partie
void liberer_jeu (jeu *j); //liberer la memoire
void lancer(jeu *j); // lance le jeu

#endif // jeu_h
