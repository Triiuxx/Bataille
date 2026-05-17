#ifndef carte_h
#define carte_h
//carte.h pour pour decrire la structure carte


typedef struct carte{
    int valeur; //valeur de la carte
    char couleur[10]; //couleur de la carte
    struct carte *suivant; //pointe vers la carte suivante
}carte;
#endif
