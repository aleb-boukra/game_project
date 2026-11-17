#ifndef INTERFACE_H
# define INTERFACE_H

/*Alex ouvre la fenetre au debut et la ferme a la fin*/
int interface_ouvrir(const char *titre);
void interface_fermer(void);

/*Alex passe la fonction de Choix.h sans parentheses et 1 pour afficher les choix*/
/*Exemple interface_afficher_dialogue(dialogue_afficher, 1)*/
int interface_afficher_dialogue(void (*dialogue)(void), int avec_choix);
int interface_afficher(const char *image, const char *texte,
                      const char *choix1, const char *choix2);

/*Alex recupere 1 ou 2 pour les choix, 0 pour continuer, -1 pour quitter*/
int interface_attendre_choix(void);

#endif
