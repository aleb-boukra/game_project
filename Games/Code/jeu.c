#include "jeu.h"

#include <stdio.h>

int ft_verify_answer(const char *correct, const char *wrong, const char *answer)
{
    if (answer[0] == correct[0])
        return (1);
    else if (answer[0] == wrong[0])
        return (0);
    else
        return (2);
}

static int ft_scene(const char *correct, const char *wrong, int points)
{
    int touche;
    int resultat;
    char answer;

    while ((touche = getchar()) != EOF)
    {
        answer = (char)touche;
        resultat = ft_verify_answer(correct, wrong, &answer);
        if (resultat != 2)
            return (points + resultat);
    }
    return (points);
}

int ft_scene_1(const char *correct, const char *wrong, int points)
{
    (void)points;
    return (ft_scene(correct, wrong, 0));
}

int ft_scene_2(const char *correct, const char *wrong, int points)
{
    return (ft_scene(correct, wrong, points));
}

int ft_scene_3(const char *correct, const char *wrong, int points)
{
    return (ft_scene(correct, wrong, points));
}

int ft_scene_4(const char *correct, const char *wrong, int points)
{
    return (ft_scene(correct, wrong, points));
}

int ft_scene_5(const char *correct, const char *wrong, int points)
{
    return (ft_scene(correct, wrong, points));
}

t_fin ft_type_fin(int points)
{
    if (points == 0)
        return (FIN_ALTERNATIVE);
    if (points >= 1 && points <= 2)
        return (FIN_MAUVAISE);
    return (FIN_BONNE);
}

void ft_ending(int n)
{
    t_fin fin = ft_type_fin(n);

    if (fin == FIN_ALTERNATIVE)
    {
        printf("( Elle est tellement énervée par tes réponses qu'elle te balance son verre au visage et quitte immédiatement le restaurant. )\n");
        printf("« Elle m'a balancé un verre et elle est partie... Je crois que j'ai complètement raté mon rendez-vous. »\n");
    }
    else if (fin == FIN_MAUVAISE)
    {
        printf("(Le rendez-vous se termine dans un silence gênant. Elle te remercie poliment, mais refuse de te revoir.)\n");
        printf("« Bon... C'était sympa, mais je pense qu'on n'est pas vraiment faits l'un pour l'autre. Bonne soirée ! »\n");
    }
    else
    {
        printf("( Elle a apprécié le rendez-vous. Elle sourit et te propose de vous revoir. )\n");
        printf("« J'ai passé une super soirée avec toi ! Ça te dirait qu'on se revoie ce week-end ? »\n");
    }
}
