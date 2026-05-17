#include <stdio.h>
#include <stdlib.h>
#include "pile.h.h"
#include "file.h.h"
void init_pile(pile *p){
    p->sommet = NULL;
    p->taille= 0;

}
void empiler(pile *p, carte *c) {
    if (c==NULL) return;
    c-> suivant = p->sommet;
    p-> sommet = c;
    p->taille++;
}
carte *depiler(pile *p) {
    if (pile_vide(p)){

        printf("erreur : pile vide\n");
        return NULL;
    }
    carte *retrait = p->sommet;
    p->sommet = p->sommet->suivant;
    retrait->suivant = NULL;
    p->taille--;
    return retrait;

}
int pile_vide(pile *p) {
    return (p->sommet == NULL);
}
int taille_pile(pile *p) {
    return p->taille;
}
void liberer_pile(pile *p){
    carte *courant = p->sommet;
    carte *suivant = NULL;
    while (courant != NULL) {
        suivant = courant ->suivant;
        free(courant);
        courant = suivant;
    }
    p -> sommet = NULL;
    p -> taille = 0;
}
void vider_dans_file(pile *p, file *f) {
    while (!pile_vide(p)) {
        carte *c = depiler(p);
        if (c != NULL) {
            enfiler(f, c);
        }
    }
}
