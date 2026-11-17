#include "interface.h"
#include "Choix.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    static const struct {
        const char *nom;
        void (*dialogue)(void);
        int avec_choix;
    } apercus[] = {
        {"intro", presentation, 0},
        {"restaurant", dialogue_afficher, 1},
        {"positif", rep1_p, 0},
        {"negatif", choix1_n, 0},
        {"alternative", fin_anticiper, 0},
        {"bonne-fin", good_ending, 0},
        {"mauvaise-fin", bad_ending, 0}
    };
    const char *nom = argc == 2 ? argv[1] : "intro";
    size_t index;
    int erreur;

    for (index = 0; index < sizeof apercus / sizeof apercus[0]; index++)
        if (strcmp(nom, apercus[index].nom) == 0)
            break;
    if (argc > 2 || index == sizeof apercus / sizeof apercus[0])
    {
        fprintf(stderr, "Usage : %s [intro|restaurant|positif|negatif|"
                        "alternative|bonne-fin|mauvaise-fin]\n", argv[0]);
        return (1);
    }
    if (interface_ouvrir("Date Simulator") != 0)
        return (1);
    erreur = interface_afficher_dialogue(apercus[index].dialogue,
                                         apercus[index].avec_choix);
    if (!erreur)
        interface_attendre_choix();
    interface_fermer();
    return (erreur != 0);
}
