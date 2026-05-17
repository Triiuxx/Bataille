#ifndef file_h
#define file_h
#include "carte.h.h"


typedef struct {
    carte *tete;
    carte *queue;
    int taille;
}file;


void init_file(file *f);
void enfiler(file *f, carte *c);
carte *defiler (file *f);
int file_vide(file *f);
int taille_file(file *f);
void afficher_file(file *f);
void liberer_file(file *f);


#endif // file_h
