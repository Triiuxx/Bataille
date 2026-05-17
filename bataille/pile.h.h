#ifndef pile_h
#define pile_h
#include "carte.h.h"
#include "file.h.h"
//struct represantante pour la pile
typedef struct {
    carte *sommet; //top card
    int taille;

} pile;
void init_pile (pile *p); //initialisation d une pile vide
void empiler (pile *p, carte *c); //pose une carte au sommet
carte *depiler (pile *p); //retire et retourne top card
int pile_vide(pile *p); //pour verifier si la pile est vide ou non
int taille_pile (pile *p); //retourne le nb de cartes dans la pile
void vider_dans_file (pile *p, file *f); //
void liberer_pile (pile *p); //liberer la memoire
#endif // pile_h
