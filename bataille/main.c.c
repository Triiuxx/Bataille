#include <stdio.h>
#include <stdlib.h>
#include "carte.h.h"
#include "liste.h.h"
#include "file.h.h"
#include "pile.h.h"
#include "jeu.h.h"

int main(void) {
    jeu JEU;
    init_jeu(&JEU);
    lancer(&JEU);
    liberer_jeu(&JEU);
    return EXIT_SUCCESS;
}
