#ifndef JEU_H
# define JEU_H

typedef enum e_fin
{
    FIN_ALTERNATIVE,
    FIN_MAUVAISE,
    FIN_BONNE
} t_fin;

int ft_verify_answer(const char *correct, const char *wrong, const char *answer);
int ft_scene_1(const char *correct, const char *wrong, int points);
int ft_scene_2(const char *correct, const char *wrong, int points);
int ft_scene_3(const char *correct, const char *wrong, int points);
int ft_scene_4(const char *correct, const char *wrong, int points);
int ft_scene_5(const char *correct, const char *wrong, int points);
t_fin ft_type_fin(int points);
void ft_ending(int points);

#endif
