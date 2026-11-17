#include <unistd.h>
#include <stdio.h>

int ft_scene_1(char *correct, char *wrong,int points);
int ft_scene_2(char *correct, char *wrong,int points);
int ft_scene_3(char *correct, char *wrong,int points);
int ft_scene_4(char *correct, char *wrong,int points);
int ft_scene_5(char *correct, char *wrong,int points);

int main()
{
    int score = 0;
    score = ft_scene_1("1", "2", score);
    score = ft_scene_2("1", "2", score);
    score = ft_scene_3("1", "2", score);
    score = ft_scene_4("1", "2", score);
    score = ft_scene_5("1", "2", score);
    printf("Your score is :  %d\n", score);
    return (0);
}
