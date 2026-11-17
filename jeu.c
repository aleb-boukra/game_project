#include <unistd.h>
#include <stdio.h>

int ft_verify_answer(char *correct, char *wrong, char *answer)
{
    if (answer[0] == correct[0])
        return (1);
    else if (answer[0] == wrong[0])
        return (0);
    else
        return (2);
}

int ft_scene_1(char *correct, char *wrong,int points)
{
    int score = 0;
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
