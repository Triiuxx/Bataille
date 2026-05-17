#ifndef liste_h
#define liste_h
#include "carte.h.h"
const char *libelle_valeur(int valeur);
void nom_carte(carte *c, char *buffer, int taille);
carte *creer_carte(int valeur, const char *couleur);       //creer une seule carte avec une valeur et une couleur
void inserer_queue(carte **tete, carte *nouvelle);         //ajouter une carte a la fin de la lste
void afficher_liste(carte *tete);                          //afficher la liste des cartes
int taille_liste(carte *tete);                   //nb des cartes dans la liste
void effacer_liste(carte **tete);        //liberer laa memoire de la liste
carte *creer_jeu(void);           //creer le jeu complet de 52 cartes
void melanger_jeu(carte **tete);       //melanger les cartes aleatoirement
#endif
