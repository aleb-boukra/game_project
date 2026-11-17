#include "interface.h"
#include "Choix.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define LARGEUR 960
#define HAUTEUR 760
#define IMAGE_H 540
#define MARGE 24

#ifndef DOSSIER_IMAGES
# define DOSSIER_IMAGES "img"
#endif

#define IMAGE_RESTO DOSSIER_IMAGES "/1.png"
#define IMAGE_POSITIVE DOSSIER_IMAGES "/1G.png"
#define IMAGE_NEGATIVE DOSSIER_IMAGES "/1F.png"

typedef enum
{
    CARTOUCHE,
    PENSEE,
    REPLIQUE,
    CHOIX,
    AIDE
} t_style;

typedef enum
{
    SANS_TITRE,
    SUCCESS,
    FAIL
} t_titre;

static const struct {
    t_dialogue dialogue;
    const char *image;
    t_style style;
} scenes[] = {
    {presentation, NULL, CARTOUCHE},
    {dialogue_afficher, IMAGE_RESTO, PENSEE},
    {choix1_p, IMAGE_POSITIVE, REPLIQUE},
    {rep1_p, IMAGE_POSITIVE, REPLIQUE},
    {choix2_p, IMAGE_POSITIVE, REPLIQUE},
    {rep2_p, IMAGE_POSITIVE, REPLIQUE},
    {choix3_p, IMAGE_POSITIVE, REPLIQUE},
    {rep3p_, IMAGE_POSITIVE, REPLIQUE},
    {choix4_p, IMAGE_POSITIVE, REPLIQUE},
    {rep4_, IMAGE_POSITIVE, REPLIQUE},
    {choix_p5, IMAGE_POSITIVE, REPLIQUE},
    {choix1_n, IMAGE_NEGATIVE, REPLIQUE},
    {rep1_n, IMAGE_NEGATIVE, REPLIQUE},
    {choix2_n, IMAGE_NEGATIVE, REPLIQUE},
    {rep2_n, IMAGE_NEGATIVE, REPLIQUE},
    {choix3_n, IMAGE_NEGATIVE, REPLIQUE},
    {rep3n_, IMAGE_NEGATIVE, REPLIQUE},
    {choix4_n, IMAGE_NEGATIVE, REPLIQUE},
    {rep4_n, IMAGE_NEGATIVE, REPLIQUE},
    {choix_n5, IMAGE_NEGATIVE, REPLIQUE},
    {penser1, IMAGE_POSITIVE, PENSEE},
    {penser2, IMAGE_NEGATIVE, PENSEE},
    {fin_anticiper, DOSSIER_IMAGES "/Alternatifending.png", PENSEE},
    {good_ending, DOSSIER_IMAGES "/Goodending.png", CARTOUCHE},
    {bad_ending, DOSSIER_IMAGES "/Badending.png", CARTOUCHE}
};

struct capture_texte {
    char texte[2048];
    size_t longueur;
    int erreur;
};

typedef struct
{
    SDL_Texture *texte;
    SDL_Texture *emoji;
    SDL_Rect zone;
    int largeur_texte;
    int hauteur_texte;
    t_style style;
} t_bulle;

typedef struct
{
    SDL_Texture *image;
    t_bulle bulles[4];
    size_t nombre;
} t_page;

static const char *const chemins_police[] = {
    "/usr/share/fonts/google-noto-vf/NotoSans[wght].ttf",
    "/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf",
    "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"
};

static const SDL_Color encre = {33, 31, 36, 255};
static const SDL_Color papier = {255, 247, 225, 255};
static const SDL_Color perle = {251, 250, 247, 255};
static SDL_Window *fenetre;
static SDL_Renderer *rendu;
static TTF_Font *police;
static TTF_Font *police_aide;
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

static int lire_dialogue(t_dialogue dialogue, struct capture_texte *texte)
{
    capture = texte;
    dialogue();
    capture = NULL;
    if (texte->erreur)
        return (fprintf(stderr, "Texte trop long pour la scène\n"), -1);
    return (0);
}

static int trouver_scene(t_dialogue dialogue)
{
    for (size_t i = 0; i < sizeof scenes / sizeof scenes[0]; ++i)
        if (scenes[i].dialogue == dialogue)
            return ((int)i);
    return (fprintf(stderr, "Dialogue sans scène associée\n"), -1);
}

void interface_fermer(void)
{
    if (police_aide)
        TTF_CloseFont(police_aide);
    if (police)
        TTF_CloseFont(police);
    police_aide = NULL;
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
    const char *chemin = NULL;

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
    for (size_t i = 0; i < sizeof chemins_police / sizeof chemins_police[0]; ++i)
    {
        chemin = chemins_police[i];
        police = TTF_OpenFont(chemin, 22);
        if (police)
            break;
    }
    if (police)
        police_aide = TTF_OpenFont(chemin, 16);
    if (!police || !police_aide)
        return (fprintf(stderr, "%s\n", TTF_GetError()),
                interface_fermer(), -1);
    return (0);
}

static SDL_Texture *charger_image(const char *image)
{
    char *base;
    char *chemin;
    size_t taille;
    SDL_Texture *texture;

    if (image[0] == '/')
        return (IMG_LoadTexture(rendu, image));
    base = SDL_GetBasePath();
    if (!base)
        return (NULL);
    taille = SDL_strlen(base) + SDL_strlen(image) + 1;
    chemin = SDL_malloc(taille);
    if (!chemin)
    {
        SDL_free(base);
        return (NULL);
    }
    SDL_snprintf(chemin, taille, "%s%s", base, image);
    texture = IMG_LoadTexture(rendu, chemin);
    SDL_free(chemin);
    SDL_free(base);
    return (texture);
}

static int cadre(t_page *page, const char *image)
{
    if (!rendu || !police)
        return (-1);
    if (image)
    {
        page->image = charger_image(image);
        if (!page->image)
            return (fprintf(stderr, "Image %s : %s\n", image, IMG_GetError()), -1);
    }
    return (0);
}

static void liberer_page(t_page *page)
{
    for (size_t i = 0; i < page->nombre; ++i)
    {
        if (page->bulles[i].emoji)
            SDL_DestroyTexture(page->bulles[i].emoji);
        SDL_DestroyTexture(page->bulles[i].texte);
    }
    if (page->image)
        SDL_DestroyTexture(page->image);
}

static SDL_Texture *creer_emoji(const char *texte, size_t longueur)
{
    if (longueur < 2 || texte[longueur - 1] != ')')
        return (NULL);
    if (texte[longueur - 2] == ':')
        return (charger_image(DOSSIER_IMAGES "/emoji-sourire.png"));
    if (texte[longueur - 2] == ';')
        return (charger_image(DOSSIER_IMAGES "/emoji-clin-oeil.png"));
    return (NULL);
}

static int ajouter_bulle(t_page *page, const char *texte, t_style style,
                         SDL_Rect zone)
{
    char contenu[4160];
    char *courant = contenu;
    SDL_Surface *surface;
    SDL_Color couleur = style == AIDE ? (SDL_Color){201, 192, 179, 255} : encre;
    TTF_Font *font = style == AIDE ? police_aide : police;
    int marge = style == AIDE ? 0 : 16;
    size_t longueur;
    int reserve;
    t_bulle *bulle;

    if (!texte || !*texte)
        return (0);
    longueur = strlen(texte);
    if (longueur >= sizeof contenu / 2 || page->nombre >= SDL_arraysize(page->bulles))
        return (-1);
    bulle = &page->bulles[page->nombre++];
    if (style == REPLIQUE || style == CHOIX)
        bulle->emoji = creer_emoji(texte, longueur);
    if (bulle->emoji)
    {
        longueur -= 2;
        while (longueur > 0 && texte[longueur - 1] == ' ')
            --longueur;
    }
    for (size_t i = 0; i < longueur; ++i)
    {
        if (texte[i] == ' ' && i + 1 < longueur && strchr("?!", texte[i + 1]))
        {
            *courant++ = '\xC2';
            *courant++ = '\xA0';
        }
        else
            *courant++ = texte[i];
    }
    *courant = '\0';
    reserve = bulle->emoji ? 34 : 0;
    surface = TTF_RenderUTF8_Blended_Wrapped(font, contenu, couleur,
                                            zone.w - 2 * marge - reserve);
    if (!surface)
        return (-1);
    bulle->texte = SDL_CreateTextureFromSurface(rendu, surface);
    bulle->largeur_texte = surface->w;
    bulle->hauteur_texte = surface->h;
    SDL_FreeSurface(surface);
    if (!bulle->texte)
        return (-1);
    bulle->style = style;
    bulle->zone = (SDL_Rect){zone.x, zone.y, zone.w,
                            bulle->hauteur_texte + 2 * marge};
    if (style == PENSEE || style == REPLIQUE || style == AIDE)
        bulle->zone.w = bulle->largeur_texte + 2 * marge + reserve;
    if (style == REPLIQUE || style == AIDE)
        bulle->zone.x += (zone.w - bulle->zone.w) / 2;
    return (0);
}

static void remplir(SDL_Rect zone, SDL_Color couleur)
{
    SDL_SetRenderDrawColor(rendu, couleur.r, couleur.g, couleur.b, couleur.a);
    SDL_RenderFillRect(rendu, &zone);
}

static void arrondi(SDL_Rect zone, SDL_Color couleur)
{
    remplir((SDL_Rect){zone.x + 8, zone.y, zone.w - 16, zone.h}, couleur);
    remplir((SDL_Rect){zone.x + 3, zone.y + 3, zone.w - 6, zone.h - 6}, couleur);
    remplir((SDL_Rect){zone.x, zone.y + 8, zone.w, zone.h - 16}, couleur);
}

static void disque(int x, int y, int rayon, SDL_Color couleur)
{
    SDL_SetRenderDrawColor(rendu, couleur.r, couleur.g, couleur.b, couleur.a);
    for (int dy = -rayon; dy <= rayon; ++dy)
    {
        int dx = rayon;
        while (dx * dx + dy * dy > rayon * rayon)
            --dx;
        SDL_RenderDrawLine(rendu, x - dx, y + dy, x + dx, y + dy);
    }
}

static void pointe(int x, int y, int decalage, SDL_Color couleur)
{
    SDL_Vertex triangle[] = {
        {{x, y + 3}, couleur, {0, 0}},
        {{x + 25, y + 3}, couleur, {0, 0}},
        {{x + decalage, y - 21}, couleur, {0, 0}}
    };

    SDL_RenderGeometry(rendu, NULL, triangle, 3, NULL, 0);
}

static int tracer_bulle(const t_bulle *bulle)
{
    SDL_Rect z = bulle->zone;
    bool aide = bulle->style == AIDE;
    int marge = aide ? 0 : 16;
    SDL_Color fond = bulle->style == CARTOUCHE ? papier : perle;
    SDL_Color ombre = {27, 22, 27, 255};
    SDL_Rect texte = {z.x + marge, z.y + marge, bulle->largeur_texte,
                      bulle->hauteur_texte};

    if (bulle->style == PENSEE)
    {
        int regard = SDL_clamp(234, z.x + 12, z.x + z.w - 16);
        disque(regard - 8, z.y - 12, 8, fond);
        disque(regard, z.y - 26, 4, fond);
    }
    if (bulle->style == REPLIQUE)
        pointe(SDL_clamp(651, z.x + 8, z.x + z.w - 32), z.y, 8, fond);
    if (bulle->style == CHOIX)
        pointe(z.x + 50, z.y, 8, fond);
    if (!aide)
    {
        arrondi((SDL_Rect){z.x + 2, z.y + 4, z.w, z.h}, ombre);
        if (bulle->style == CARTOUCHE)
        {
            remplir(z, fond);
            remplir((SDL_Rect){z.x, z.y, 4, z.h}, (SDL_Color){198, 152, 90, 255});
        }
        else
            arrondi(z, fond);
    }
    if (SDL_RenderCopy(rendu, bulle->texte, NULL, &texte) != 0)
        return (-1);
    if (bulle->emoji)
    {
        SDL_Rect emoji = {z.x + z.w - marge - 29, z.y + z.h - marge - 26, 27, 27};
        if (SDL_RenderCopy(rendu, bulle->emoji, NULL, &emoji) != 0)
            return (-1);
    }
    return (0);
}

static const char *const lettres_arcade[][7] = {
    ['A' - 'A'] = {".###.", "##.##", "##.##", "#####", "##.##", "##.##", "##.##"},
    ['C' - 'A'] = {".####", "##...", "##...", "##...", "##...", "##...", ".####"},
    ['E' - 'A'] = {"#####", "##...", "##...", "####.", "##...", "##...", "#####"},
    ['F' - 'A'] = {"#####", "##...", "##...", "####.", "##...", "##...", "##..."},
    ['I' - 'A'] = {"#####", ".###.", ".###.", ".###.", ".###.", ".###.", "#####"},
    ['L' - 'A'] = {"##...", "##...", "##...", "##...", "##...", "##...", "#####"},
    ['S' - 'A'] = {".####", "##...", "##...", ".###.", "...##", "...##", "####."},
    ['U' - 'A'] = {"##.##", "##.##", "##.##", "##.##", "##.##", "##.##", ".###."}
};

static void pixels(const char *mot, int x, int y, int taille, SDL_Color couleur)
{
    for (; *mot; ++mot, x += 6 * taille)
    {
        const char *const *lignes = lettres_arcade[*mot - 'A'];
        for (int rang = 0; rang < 7; ++rang)
            for (int col = 0; col < 5; ++col)
                if (lignes[rang][col] == '#')
                    remplir((SDL_Rect){x + col * taille, y + rang * taille,
                                       taille, taille}, couleur);
    }
}

static void tracer_titre(t_titre titre, Uint32 temps)
{
    bool succes = titre == SUCCESS;
    const char *mot = succes ? "SUCCESS" : "FAIL";
    int centre = succes ? 260 : 483;
    int taille = temps < 300 ? 4 + (int)temps * 7 / 300
                            : 11 - (int)(temps - 300) * 2 / 240;
    int largeur;
    int x;
    int y;
    SDL_Color clair = succes ? (SDL_Color){92, 196, 255, 255}
                             : (SDL_Color){255, 89, 104, 255};
    SDL_Color sombre = succes ? (SDL_Color){20, 63, 124, 255}
                              : (SDL_Color){117, 26, 45, 255};

    largeur = ((int)strlen(mot) * 6 - 1) * taille;
    x = centre - largeur / 2;
    y = 149 - 7 * taille / 2;
    remplir((SDL_Rect){x - 17, y - 14, largeur + 34, 7 * taille + 30},
            (SDL_Color){23, 24, 35, 255});
    remplir((SDL_Rect){x - 17, y - 14, 17 + taille, 3}, clair);
    remplir((SDL_Rect){x + largeur - taille, y + 7 * taille + 13,
                       17 + taille, 3}, clair);
    pixels(mot, x + 3, y + 5, taille, sombre);
    pixels(mot, x, y, taille, clair);
}

static int afficher_page(t_page *page, t_titre titre, int erreur)
{
    Uint32 depart = SDL_GetTicks();
    Uint32 temps;

    while (!erreur)
    {
        temps = SDL_GetTicks() - depart;
        SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
        SDL_RenderClear(rendu);
        if (page->image)
        {
            SDL_Rect photo = {0, 0, LARGEUR, IMAGE_H};
            erreur = SDL_RenderCopy(rendu, page->image, NULL, &photo);
            remplir((SDL_Rect){0, IMAGE_H, LARGEUR, HAUTEUR - IMAGE_H},
                    (SDL_Color){27, 23, 29, 255});
            remplir((SDL_Rect){0, IMAGE_H, LARGEUR, 2}, (SDL_Color){130, 91, 66, 255});
        }
        for (size_t i = 0; !erreur && i < page->nombre; ++i)
            erreur = tracer_bulle(&page->bulles[i]);
        if (erreur)
            break;
        if (titre != SANS_TITRE)
            tracer_titre(titre, temps < 540 ? temps : 540);
        SDL_RenderPresent(rendu);
        if (titre == SANS_TITRE || temps >= 540)
            break;
        SDL_Delay(16);
    }
    liberer_page(page);
    return (erreur);
}

int interface_afficher_choix(t_dialogue plan, t_dialogue premier,
                             t_dialogue deuxieme)
{
    t_page page = {0};
    struct capture_texte textes[2] = {0};
    char ligne[2080];
    int index = trouver_scene(plan);
    int erreur;

    if (index < 0 || lire_dialogue(premier, &textes[0])
        || lire_dialogue(deuxieme, &textes[1]))
        return (-1);
    erreur = cadre(&page, scenes[index].image);
    for (int i = 0; !erreur && i < 2; ++i)
    {
        snprintf(ligne, sizeof ligne, "%d) %.*s", i + 1,
                 (int)sizeof textes[i].texte - 1, textes[i].texte);
        erreur = ajouter_bulle(&page, ligne, CHOIX,
                               (SDL_Rect){MARGE + i * 466, 569, 446, 0});
    }
    if (!erreur)
        erreur = ajouter_bulle(&page, "1 ou 2 pour choisir", AIDE,
                               (SDL_Rect){0, 730, LARGEUR, 0});
    return (afficher_page(&page, SANS_TITRE, erreur));
}

int interface_afficher_dialogue(t_dialogue dialogue, int avec_choix)
{
    t_page page = {0};
    struct capture_texte texte = {0};
    struct capture_texte contexte = {0};
    SDL_Rect zone = {MARGE, 564, LARGEUR - MARGE * 2, 0};
    t_titre titre = SANS_TITRE;
    int index;
    int erreur;
    t_style style;

    if (avec_choix)
        return (interface_afficher_choix(dialogue, choix1_p, choix1_n));
    index = trouver_scene(dialogue);
    if (index < 0 || lire_dialogue(dialogue, &texte))
        return (-1);
    erreur = cadre(&page, scenes[index].image);
    style = scenes[index].style;
    if (style == PENSEE)
        zone = (SDL_Rect){36, 385, 385, 0};
    else if (style == REPLIQUE)
        zone = (SDL_Rect){508, 375, 412, 0};
    else if (!page.image)
        zone = (SDL_Rect){154, 328, 652, 0};
    if (!erreur && dialogue == fin_anticiper)
    {
        erreur = lire_dialogue(contexte_fin_alternative, &contexte);
        if (!erreur)
            erreur = ajouter_bulle(&page, contexte.texte, CARTOUCHE,
                                    (SDL_Rect){MARGE, 564, LARGEUR - MARGE * 2, 0});
    }
    if (!erreur)
        erreur = ajouter_bulle(&page, texte.texte, style, zone);
    if (!erreur)
        erreur = ajouter_bulle(&page, "Entrée ou Espace pour continuer", AIDE,
                               (SDL_Rect){0, 730, LARGEUR, 0});
    if (dialogue == good_ending)
        titre = SUCCESS;
    else if (dialogue == bad_ending)
        titre = FAIL;
    return (afficher_page(&page, titre, erreur));
}

int interface_afficher(const char *image, const char *texte,
                      const char *choix1, const char *choix2)
{
    t_page page = {0};
    int erreur = cadre(&page, image);
    int y = image ? 566 : 328;

    if (!erreur)
        erreur = ajouter_bulle(&page, texte, CARTOUCHE,
                               (SDL_Rect){MARGE, y, LARGEUR - MARGE * 2, 0});
    if (!erreur)
        erreur = ajouter_bulle(&page, choix1, CHOIX,
                               (SDL_Rect){MARGE, y + 76, 446, 0});
    if (!erreur)
        erreur = ajouter_bulle(&page, choix2, CHOIX,
                               (SDL_Rect){490, y + 76, 446, 0});
    return (afficher_page(&page, SANS_TITRE, erreur));
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
            evenement.key.keysym.sym == SDLK_KP_1 ||
            evenement.key.keysym.scancode == SDL_SCANCODE_1)
            return (1);
        if (evenement.key.keysym.sym == SDLK_2 ||
            evenement.key.keysym.sym == SDLK_KP_2 ||
            evenement.key.keysym.scancode == SDL_SCANCODE_2)
            return (2);
    }
    return (-1);
}
