#include <unistd.h>

#include <stdio.h>

// "*" designe les pensees du perso, "()" designe le contexte qu'on donne, "<< >>" designe les dialogues mettre des bulles comme dqns les bd en analysant l,image donc la bonne taille etc.. donc bulle de reflexion a la place des * bulle de dialoge a la place des << et les contexte on le met en image comme une legende de bd

int ft_verify_answer(char *correct, char *wrong, char *answer)
{
    if (answer[0] == correct[0])
        return (1);
    else if (answer[0] == wrong[0])
        return (0);
    else
        return (2);
}

void ft_intro()
{
    printf("( Tu es à un rendez-vous, et pas avec n'importe qui ! Avec la fille qui te plaît depuis des années. À toi de la séduire ! )\n"); 
   
}

int ft_scene_1(char *correct, char *wrong,int points)
{
    printf("* OK... Il ne faut pas que je me loupe. Bon, qu'est-ce que je pourrais lui dire... *\n"); // ne pas laisser cette phrase affichee quand on appuie sur entree pour enchainer
    printf("1) << Alors, tu deviens quoi depuis le lycée ? >>\n");
    printf("2) << Et si on brisait la glace ? C'est l'histoire d'un zoophile qui entre dans un bar... >>\n");
    // quand on a selectionne la reponse on arrete d'afficher ce texte a moins que  verify_answer == 2
    int score = 0;
    int n;
    char answer[2];
    n = read(0, answer, 2);
    if (ft_verify_answer(correct, wrong, answer) == 1)
    {
        score++;
        printf("<< Eh ben écoute, je fais des études de médecine, haha ! Et toi ? :) >>\n"); // reponse de la femme (mettre un vrai emoji)
        printf("* Hmm... C'est vrai qu'elle était bonne élève. *"); // pensee du mec
    }
    else if (ft_verify_answer(correct, wrong, answer) == 0)
    {
        score = score;
        printf(" << ... >>\n"); // meme pattern que pour le if precedent et ainsi de suite
        printf("* Merde... J'aurais peut-être pas dû... *\n");
    }
    else if (ft_verify_answer(correct, wrong, answer) == 2)
    {
        while (ft_verify_answer(correct, wrong, answer) != 1 && ft_verify_answer(correct, wrong, answer) != 0)
                n = read(0, answer, 2);
        if (ft_verify_answer(correct, wrong, answer) == 1)
        {
            score++;
            printf("<< Eh ben écoute, je fais des études de médecine, haha ! Et toi ? :) >>\n"); // reponse de la femme (mettre un vrai emoji)
            printf("* Hmm... C'est vrai qu'elle était bonne élève. *"); // pensee du mec
        }
        else if (ft_verify_answer(correct, wrong, answer) == 0)
            score =score;
    }
    return (score);
}

int ft_scene_2(char *correct, char *wrong, int points)
{
    int score = points;
    int n;
    char answer[2];
    n = read(0, answer, 2);
    if (ft_verify_answer(correct, wrong, answer) == 1)
        score++;
    else if (ft_verify_answer(correct, wrong, answer) == 0)
        score =score;
    else if (ft_verify_answer(correct, wrong, answer) == 2)
    {
        while (ft_verify_answer(correct, wrong, answer) != 1 && ft_verify_answer(correct, wrong, answer) != 0)
                n = read(0, answer, 2);
        if (ft_verify_answer(correct, wrong, answer) == 1)
        score++;
        else if (ft_verify_answer(correct, wrong, answer) == 0)
        score =score;
    }
    return (score);
}

int ft_scene_3(char *correct, char *wrong, int points)
{
    int score = points;
    int n;
    char answer[2];
    n = read(0, answer, 2);
    if (ft_verify_answer(correct, wrong, answer) == 1)
        score++;
    else if (ft_verify_answer(correct, wrong, answer) == 0)
        score =score;
    else if (ft_verify_answer(correct, wrong, answer) == 2)
    {
        while (ft_verify_answer(correct, wrong, answer) != 1 && ft_verify_answer(correct, wrong, answer) != 0)
                n = read(0, answer, 2);
        if (ft_verify_answer(correct, wrong, answer) == 1)
        score++;
        else if (ft_verify_answer(correct, wrong, answer) == 0)
        score =score;        
    }
    return (score);
}

int ft_scene_4(char *correct, char *wrong, int points)
{
    int score = points;
    int n;
    char answer[2];
    n = read(0, answer, 2);
    if (ft_verify_answer(correct, wrong, answer) == 1)
        score++;
    else if (ft_verify_answer(correct, wrong, answer) == 0)
        score =score;
    else if (ft_verify_answer(correct, wrong, answer) == 2)
    {
        while (ft_verify_answer(correct, wrong, answer) != 1 && ft_verify_answer(correct, wrong, answer) != 0)
                n = read(0, answer, 2);
        if (ft_verify_answer(correct, wrong, answer) == 1)
        score++;
        else if (ft_verify_answer(correct, wrong, answer) == 0)
        score =score;
    }
    return (score);
}

int ft_scene_5(char *correct, char *wrong, int points)
{
    int score = points;
    int n;
    char answer[2];
    n = read(0, answer, 2);
    if (ft_verify_answer(correct, wrong, answer) == 1)
        score++;
    else if (ft_verify_answer(correct, wrong, answer) == 0)
        score =score;
    else if (ft_verify_answer(correct, wrong, answer) == 2)
    {
        while (ft_verify_answer(correct, wrong, answer) != 1 && ft_verify_answer(correct, wrong, answer) != 0)
                n = read(0, answer, 2);
        if (ft_verify_answer(correct, wrong, answer) == 1)
        score++;
        else if (ft_verify_answer(correct, wrong, answer) == 0)
        score =score;
    }
    return (score);
}

void ft_ending(int n)
{
    if (n == 0)
    {
        printf("( Elle est tellement énervée par tes réponses qu'elle te balance son verre au visage et quitte immédiatement le restaurant. )\n");
        printf("« Elle m'a balancé un verre et elle est partie... Je crois que j'ai complètement raté mon rendez-vous. »\n");
    }
    else if (n >= 1 && n <= 2)
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
