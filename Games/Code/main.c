#include "jeu.h"

#include <stdio.h>

int main(void)
{
    int score = 0;
    score = ft_scene_1("1", "2", score);
    score = ft_scene_2("1", "2", score);
    score = ft_scene_3("1", "2", score);
    score = ft_scene_4("1", "2", score);
    score = ft_scene_5("1", "2", score);
    printf("Your score is :  %d/5\n", score);
    ft_ending(score);
    return (0);
}
