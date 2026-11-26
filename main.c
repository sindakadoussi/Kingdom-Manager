#include <stdio.h>
#include "royaume.h"
#include "menu.h"
#include "batiments.h"

int main(void)
{
    Royaume royaume;

    if (!initialiser_royaume(&royaume, "Mon Royaume", "Joueur")) {
        fprintf(stderr, "Erreur lors de l'initialisation du royaume.\n");
        return 1;
    }

    menu_principal(&royaume);

    liberer_batiments(&royaume.batiments);
    return 0;
}
