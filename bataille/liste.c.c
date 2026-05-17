#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "liste.h.h"

//libeller les cartess selon leurs valeurs
const char *libelle_valeur(int valeur) {
    switch (valeur) {
        case 11 : return "valet";
        case 12 : return "dame";
        case 13 : return "roi";
        case 14 : return "ace";
        default : {
            static char buf[4];
            snprintf(buf, sizeof (buf), "%d", valeur);
            return buf;
        }
    }
}
void nom_carte (carte *c, char *buffer, int taille) {
    snprintf(buffer, taille, "%s de %s", libelle_valeur(c->valeur), c->couleur);
}
carte *creer_carte(int valeur, const char *couleur) {
    carte *nouvelle  = (carte *)malloc(sizeof(carte));
    if (nouvelle==NULL) {
        printf("erreur: memoire insuffisante\n");
        exit(EXIT_FAILURE);
    }
    nouvelle->valeur = valeur;
    strncpy(nouvelle ->couleur, couleur, sizeof(nouvelle->couleur) - 1);
    nouvelle->couleur[sizeof(nouvelle->couleur) - 1] = '\0';
    nouvelle->suivant= NULL;
    return nouvelle;

}

void inserer_queue(carte **tete, carte *nouvelle) {
    if (nouvelle == NULL) return;
    nouvelle -> suivant = NULL;
    if (*tete == NULL) {
        *tete = nouvelle;
        return;
    }
    carte *courant = *tete;
    while (courant->suivant != NULL) {
        courant= courant->suivant;

    }
    courant->suivant = nouvelle;


}


void afficher_liste(carte *tete) {
    carte *courant = tete;
    int i =1;
    char buf[32];
    while (courant != NULL) {
        nom_carte(courant, buf, sizeof(buf));
        printf("  %2d. [%s]\n", i, buf);
        courant = courant->suivant;
        i++;
    }
}
int taille_liste(carte *tete){
    int count = 0;
    carte *courant = tete;
    while (courant != NULL) {
        count ++;
        courant = courant->suivant;
    }
    return count;

}



void effacer_liste(carte **tete) {
    carte *courant= *tete;
    carte *suivant = NULL;
    while (courant!=NULL) {
        suivant = courant->suivant;
        free(courant);
        courant=suivant;
    }
    *tete=NULL;
}


carte *creer_jeu(void) {
    const char *couleurs[]={"coeur","carreau","trefle","pique"};
    int nb_couleurs = 4;
    carte *tete = NULL;
    for (int c=0; c <nb_couleurs; c++) {
        for (int v=2; v<=14; v++) {
            carte *nouvelle = creer_carte(v, couleurs[c]);
            inserer_queue(&tete, nouvelle);
        }
    }
    return tete;
}


void melanger_jeu(carte **tete ){
    int n= taille_liste(*tete);
    if (n<=1) return;
    carte **tableau=(carte **)malloc(n * sizeof(carte *));
    if (tableau == NULL){
        printf("Erreur memoire\n");
        exit(EXIT_FAILURE);
    }
    carte *courant = *tete;
    for (int i=0; i<n; i++){
        tableau[i]= courant;
        courant = courant ->suivant;
    }
    srand((unsigned int)time(NULL));
    for (int i = n-1; i>0; i--){
        int j= rand() % (i+1);
        carte *temp = tableau [i];
        tableau[i]= tableau[j];
        tableau[j]=temp;

    }
    for  (int i =0;  i<n-1; i++){
        tableau[i]->suivant = tableau[i+1];

    }
    tableau[n-1]-> suivant = NULL;
    *tete = tableau[0];
    free(tableau);

}
