#include "Choix.h"

/*Les choix d utilisateur pour afficher le type de reponse qu il southaite afficher*/
void affichage_des_choix(void)
{
	ecrit("1) Positif");
	ecrit("2) Négatif");
}


/*Dialogue a afficher/contexte*/
void presentation(void)
{
	ecrit("Tu es à un rendez-vous, et pas avec n'importe qui ! Avec la fille qui te plaît depuis des années. À toi de la séduire !");
}

/*Penser du personage a afficher avant de faire les choix*/
void dialogue_afficher(void)
{
	ecrit("OK... Il ne faut pas que je me loupe. Bon, qu'est-ce que je pourrais lui dire...");
}

/*Debut des choix si il y a un p = choix positif si ya un n = negatif, si le perso fait un choix negatif alors la reponse doit etre negatif*/
void choix1_p(void)
{
	ecrit("Alors, tu deviens quoi depuis le lycée ?");
}

void choix1_n(void)
{
	ecrit("Et si on brisait la glace ? C'est l'histoire d'un zoophile qui entre dans un bar...");
	ecrit("/Merde... J'aurais peut-être pas dû.../");
}

void rep1_p(void)
{
	ecrit("Eh ben écoute, je fais des études de médecine, haha ! Et toi ? :)");
}

/*penser du perssonage a afficher*/
void penser1(void)
{
	ecrit("Hmm... C'est vrai qu'elle était bonne élève.");
}

void rep1_n(void)
{
	ecrit("...");
}

/*penser du pesonage*/
void penser2 (void)
{
	ecrit("Il faut bien quelqu'un pour faire un flop...");
}

void choix2_p(void)
{
	ecrit("Eh bien, je suis toujours dans mes études. Écoute, je termine mes études d'astronaute pour Elon Musk.");
}

void choix2_n(void)
{
	ecrit("Toujours au RSA, perso.");
}

void rep2_p(void)
{
	ecrit("Waouh, c'est vrai que t'as toujours eu le truc pour trouver les meilleurs jobs ;)");
}
void rep2_n(void)
{
	ecrit("Ah... Oui, je vois...");
}

void choix3_p(void)
{
	ecrit("La semaine prochaine, je compte partir en voyage. Pas loin, mais si tu veux venir, tu es la bienvenue :)");
}
void choix3_n(void)
{
	ecrit("J'en ai une autre ! C'est l'histoire d'un mec qui fait une blague à deux balles... PAN ! PAN !");
}

/*si le joueur a fait que des mauvais choix*/
void fin_anticiper(void)
{
	ecrit("Elle m'a balancé un verre et elle est partie...");
}


void rep3p_(void)
{
	ecrit("Haha, pourquoi pas ;)");
}
void rep3n_(void)
{
	ecrit("Euh... Et euh... Sinon, tu as une copine ?");
}

void choix4_p(void)
{
	ecrit("Hélas non. Non pas que je ne veuille pas, mais... Tu sais, le travail, tout ça.");
}
void choix4_n(void)
{
	ecrit("Nan, et je ne sais pas pourquoi d'ailleurs, mais ça me démange, si tu vois ce que je veux dire...");
}
void rep4_(void)
{
	ecrit("Surprenant, mais c'est dommage : il y a tellement peu d'hommes comme toi !");
}
void rep4_n(void)
{
	ecrit("Surprenant, ça...");
}

void choix_p5(void)
{
	ecrit("Eh bien, écoute, si tu veux, on peut continuer chez moi. Je n'habite qu'à cinq minutes.");
}
void choix_n5(void)
{
	ecrit("Bon, c'est bien gentil de jouer au saint, mais si on passait aux choses sérieuses ? Chez moi, par exemple, dans un lit. Viens en maillot de bain :)");
}

void bad_ending(void)
{
	ecrit("Elle me met une claque des ténèbres et part sans même se retourner... Ah, les femmes, jamais contentes ! Franchement, je ne comprends pas ce que j'ai fait.");
}
void good_ending(void)
{
	ecrit("On s'est embrassés et on a fini cette discussion chez moi :)");
}

/*Alex remet ending en service avec les conditions de jeu.c*/
#if 0
/*En cas d'echec ou de reussite l ecrant noir apparait*/
void ending(void)
{
	if bad_ending
	{
		ecrit("Mec, pense à consulter, sérieux...");
	}
	else if good_ending
	{
		ecrit("Bravo, maintenant va un peu dehors te trouver une vraie meuf :)");
	}
}
#endif

