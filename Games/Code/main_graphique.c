#include "Choix.h"
#include "interface.h"
#include "jeu.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct s_scene
{
    t_dialogue choix[2];
    t_dialogue reponse[2];
    t_dialogue pensee[2];
} t_scene;

static const t_scene scenes[] = {
    {{choix1_p, choix1_n}, {rep1_p, rep1_n}, {penser1, penser2}},
    {{choix2_p, choix2_n}, {rep2_p, rep2_n}, {NULL, NULL}},
    {{choix3_p, choix3_n}, {rep3p_, rep3n_}, {NULL, NULL}},
    {{choix4_p, choix4_n}, {rep4_, rep4_n}, {NULL, NULL}},
    {{choix_p5, choix_n5}, {NULL, NULL}, {NULL, NULL}}
};

enum e_resultat
{
    ERREUR_AFFICHAGE = -2,
    QUITTER = -1
};

static int montrer(t_dialogue dialogue)
{
    int touche;

    if (interface_afficher_dialogue(dialogue, 0) != 0)
        return (ERREUR_AFFICHAGE);
    do {
        touche = interface_attendre_choix();
    } while (touche > 0);
    return (touche);
}

static int demander_choix(t_dialogue plan, const t_scene *scene)
{
    int premier = rand() % 2;
    const char *correct = premier == 0 ? "1" : "2";
    const char *erreur = premier == 0 ? "2" : "1";
    int touche;
    int resultat;
    char reponse;

    if (interface_afficher_choix(plan, scene->choix[premier],
                                scene->choix[1 - premier]) != 0)
        return (ERREUR_AFFICHAGE);
    do {
        touche = interface_attendre_choix();
        if (touche < 0)
            return (QUITTER);
        reponse = (char)('0' + touche);
        resultat = ft_verify_answer(correct, erreur, &reponse);
    } while (resultat == 2);
    return (resultat);
}

static int montrer_fin(int score)
{
    switch (ft_type_fin(score))
    {
        case FIN_ALTERNATIVE:
            return (montrer(fin_anticiper));
        case FIN_MAUVAISE:
            return (montrer(bad_ending));
        case FIN_BONNE:
            return (montrer(good_ending));
    }
    return (ERREUR_AFFICHAGE);
}

static int jouer(void)
{
    t_dialogue plan = dialogue_afficher;
    int score = 0;
    int resultat = montrer(presentation);
    int branche;

    if (resultat >= 0)
        resultat = montrer(dialogue_afficher);
    if (resultat < 0)
        return (resultat);
    for (size_t i = 0; i < sizeof scenes / sizeof scenes[0]; ++i)
    {
        resultat = demander_choix(plan, &scenes[i]);
        if (resultat < 0)
            return (resultat);
        score += resultat;
        branche = 1 - resultat;
        if (scenes[i].reponse[branche])
        {
            plan = scenes[i].reponse[branche];
            resultat = montrer(plan);
            if (resultat < 0)
                return (resultat);
        }
        if (scenes[i].pensee[branche])
        {
            resultat = montrer(scenes[i].pensee[branche]);
            if (resultat < 0)
                return (resultat);
        }
    }
    printf("Score : %d/5\n", score);
    return (montrer_fin(score));
}

int main(void)
{
    struct timespec depart = {0};
    int resultat;

    timespec_get(&depart, TIME_UTC);
    srand((unsigned int)depart.tv_sec ^ (unsigned int)depart.tv_nsec);
    if (interface_ouvrir("Date Simulator") != 0)
        return (1);
    resultat = jouer();
    interface_fermer();
    return (resultat == ERREUR_AFFICHAGE);
}
