#include <stdio.h>
#include <stdlib.h>
#include "file.h.h"
#include "liste.h.h"
void init_file(file *f){
    f->tete = NULL;
    f->queue = NULL;
    f->taille = 0;
}
void enfiler(file *f, carte *c){
    if (c==NULL) return;
    c->suivant=NULL;
    if (file_vide(f)) {
        f->tete = c;
        f->queue = c;

    }
    else {
        f->queue->suivant=c;
        f->queue = c;
    }
    f->taille++;
}
carte *defiler(file *f) {
    if (file_vide(f)) {
        printf ("erreur : file vide\n");
        return NULL;

    }
    carte *retrait = f->tete;
    f->tete = f->tete->suivant;
    if (f->tete==NULL) {
        f->queue=NULL;
    }
    retrait->suivant = NULL;
    f->taille--;
    return retrait;
}
int file_vide(file *f){
    return (f->tete == NULL);

}
int taille_file(file *f){
    return f->taille;
}
void afficher_file(file *f) {
    carte *courant=f->tete;
    int i=1;
    char buf[32];
    if (file_vide(f)) {
        printf ("(file vide)\n");
        return;

    }
    while (courant!= NULL){
        nom_carte(courant, buf , sizeof(buf));
        printf("%2d [%s]\n", i, buf);
        courant = courant->suivant;
        i++;
    }
}
void liberer_file(file *f) {
    carte *courant = f->tete;
    carte *suivant = NULL;
    while (courant != NULL) {
        suivant = courant->suivant;
        free(courant);
        courant = suivant;

    }
    f->tete = NULL;
    f->queue = NULL;
    f->taille =0;

}
