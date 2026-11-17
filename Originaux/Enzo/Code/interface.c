#include "interface.h"
#include "Choix.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#define LARGEUR 960
#define HAUTEUR 760
#define IMAGE_H 540
#define MARGE 24

#ifndef DOSSIER_IMAGES
# define DOSSIER_IMAGES "/home/axe/Bureau/Learning/Project/Games/img"
#endif

#define IMAGE_RESTO DOSSIER_IMAGES "/1.png"
#define IMAGE_POSITIVE DOSSIER_IMAGES "/1G.png"
#define IMAGE_NEGATIVE DOSSIER_IMAGES "/1F.png"

static const struct {
    void (*dialogue)(void);
    const char *image;
} scenes[] = {
    {presentation, NULL},
    {dialogue_afficher, IMAGE_RESTO},
    {choix1_p, IMAGE_POSITIVE},
    {rep1_p, IMAGE_POSITIVE},
    {choix2_p, IMAGE_POSITIVE},
    {rep2_p, IMAGE_POSITIVE},
    {choix3_p, IMAGE_POSITIVE},
    {rep3p_, IMAGE_POSITIVE},
    {choix4_p, IMAGE_POSITIVE},
    {rep4_, IMAGE_POSITIVE},
    {choix_p5, IMAGE_POSITIVE},
    {choix1_n, IMAGE_NEGATIVE},
    {rep1_n, IMAGE_NEGATIVE},
    {choix2_n, IMAGE_NEGATIVE},
    {rep2_n, IMAGE_NEGATIVE},
    {choix3_n, IMAGE_NEGATIVE},
    {rep3n_, IMAGE_NEGATIVE},
    {choix4_n, IMAGE_NEGATIVE},
    {rep4_n, IMAGE_NEGATIVE},
    {choix_n5, IMAGE_NEGATIVE},
    {penser1, IMAGE_RESTO},
    {penser2, IMAGE_RESTO},
    {fin_anticiper, DOSSIER_IMAGES "/Alternatifending.png"},
    {good_ending, DOSSIER_IMAGES "/Goodending.png"},
    {bad_ending, DOSSIER_IMAGES "/Badending.png"}
};

struct capture_texte {
    char texte[2048];
    size_t longueur;
    int erreur;
};

static SDL_Window *fenetre;
static SDL_Renderer *rendu;
static TTF_Font *police;
static struct capture_texte *capture;

void ecrit(const char *texte)
{
    size_t place;
    int longueur;

    if (!capture)
    {
        puts(texte);
        return;
    }
    if (capture->erreur)
        return;
    place = sizeof capture->texte - capture->longueur;
    longueur = snprintf(capture->texte + capture->longueur, place,
                        "%s%s", capture->longueur ? "\n" : "", texte);
    if (longueur < 0 || (size_t)longueur >= place)
        capture->erreur = 1;
    else
        capture->longueur += (size_t)longueur;
}

int interface_afficher_dialogue(void (*dialogue)(void), int avec_choix)
{
    struct capture_texte texte = {0};
    struct capture_texte choix = {0};
    size_t index;

    for (index = 0; index < sizeof scenes / sizeof scenes[0]; index++)
        if (scenes[index].dialogue == dialogue)
            break;
    if (index == sizeof scenes / sizeof scenes[0])
        return (fprintf(stderr, "Dialogue sans scene associee\n"), -1);
    capture = &texte;
    dialogue();
    if (avec_choix)
    {
        capture = &choix;
        affichage_des_choix();
    }
    capture = NULL;
    if (texte.erreur || choix.erreur)
        return (fprintf(stderr, "Texte trop long pour la scene\n"), -1);
    return (interface_afficher(scenes[index].image, texte.texte,
                               avec_choix ? choix.texte : NULL, NULL));
}

void interface_fermer(void)
{
    if (police)
        TTF_CloseFont(police);
    police = NULL;
    if (rendu)
        SDL_DestroyRenderer(rendu);
    rendu = NULL;
    if (fenetre)
        SDL_DestroyWindow(fenetre);
    fenetre = NULL;
    if (TTF_WasInit())
        TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int interface_ouvrir(const char *titre)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return (fprintf(stderr, "%s\n", SDL_GetError()), -1);
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
        return (fprintf(stderr, "%s\n", IMG_GetError()),
                interface_fermer(), -1);
    if (TTF_Init() < 0)
        return (fprintf(stderr, "%s\n", TTF_GetError()),
                interface_fermer(), -1);
    fenetre = SDL_CreateWindow(titre, SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, LARGEUR, HAUTEUR,
                              SDL_WINDOW_SHOWN);
    if (!fenetre)
        return (fprintf(stderr, "%s\n", SDL_GetError()),
                interface_fermer(), -1);
    rendu = SDL_CreateRenderer(fenetre, -1,
                              SDL_RENDERER_ACCELERATED |
                              SDL_RENDERER_PRESENTVSYNC);
    if (!rendu)
        rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_SOFTWARE);
    if (!rendu)
        return (fprintf(stderr, "%s\n", SDL_GetError()),
                interface_fermer(), -1);
    police = TTF_OpenFont("/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf",
                         22);
    if (!police)
        police = TTF_OpenFont(
            "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 22);
    if (!police)
        return (fprintf(stderr, "%s\n", TTF_GetError()),
                interface_fermer(), -1);
    return (0);
}

static int tracer_texte(const char *texte, int y, SDL_Color couleur)
{
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect zone;

    if (!texte || !*texte)
        return (0);
    surface = TTF_RenderUTF8_Blended_Wrapped(police, texte, couleur,
                                            LARGEUR - MARGE * 2);
    if (!surface)
        return (-1);
    zone = (SDL_Rect){MARGE, y, surface->w, surface->h};
    texture = SDL_CreateTextureFromSurface(rendu, surface);
    SDL_FreeSurface(surface);
    if (!texture)
        return (-1);
    if (SDL_RenderCopy(rendu, texture, NULL, &zone) != 0)
    {
        SDL_DestroyTexture(texture);
        return (-1);
    }
    SDL_DestroyTexture(texture);
    return (zone.h);
}

int interface_afficher(const char *image, const char *texte,
                      const char *choix1, const char *choix2)
{
    SDL_Texture *texture;
    SDL_Rect zone;
    SDL_Color blanc;
    SDL_Color gris;
    int y;
    int h;
    int erreur;

    if (!rendu || !police)
        return (-1);
    blanc = (SDL_Color){245, 245, 245, 255};
    gris = (SDL_Color){196, 206, 219, 255};
    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
    SDL_RenderClear(rendu);
    if (image)
    {
        texture = IMG_LoadTexture(rendu, image);
        if (!texture)
            return (fprintf(stderr, "Image %s : %s\n", image,
                            IMG_GetError()), -1);
        zone = (SDL_Rect){0, 0, LARGEUR, IMAGE_H};
        erreur = SDL_RenderCopy(rendu, texture, NULL, &zone);
        SDL_DestroyTexture(texture);
        if (erreur < 0)
            return (-1);
    }
    y = image ? IMAGE_H + 15 : HAUTEUR / 2 - 30;
    h = tracer_texte(texte, y, blanc);
    if (h < 0)
        return (-1);
    y += h + 16;
    h = tracer_texte(choix1, y, gris);
    if (h < 0)
        return (-1);
    y += h + 8;
    if (tracer_texte(choix2, y, gris) < 0)
        return (-1);
    SDL_RenderPresent(rendu);
    return (0);
}

int interface_attendre_choix(void)
{
    SDL_Event evenement;

    while (SDL_WaitEvent(&evenement))
    {
        if (evenement.type == SDL_QUIT)
            return (-1);
        if (evenement.type != SDL_KEYDOWN || evenement.key.repeat)
            continue;
        if (evenement.key.keysym.sym == SDLK_ESCAPE)
            return (-1);
        if (evenement.key.keysym.sym == SDLK_RETURN ||
            evenement.key.keysym.sym == SDLK_SPACE)
            return (0);
        if (evenement.key.keysym.sym == SDLK_1 ||
            evenement.key.keysym.sym == SDLK_KP_1)
            return (1);
        if (evenement.key.keysym.sym == SDLK_2 ||
            evenement.key.keysym.sym == SDLK_KP_2)
            return (2);
    }
    return (-1);
}
