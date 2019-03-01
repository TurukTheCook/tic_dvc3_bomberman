#include "game.h"

/**
 * Fonction d'init du jeu et de la SDL
 * @return game_t *game
*/
game_t *game_init(void)
{
    // init du pointeur du jeu
    game_t *game = NULL;
    game = malloc(sizeof(game_t));

    // init des propriétés du jeu
    game->screenSize.x = WINDOW_WIDTH;
    game->screenSize.y = WINDOW_HEIGHT;
    game->window = NULL;
    game->renderer = NULL;
    game->font = NULL;
    game->playerTexture = NULL;
    game->bombTexture = NULL;
    game->menuJoinTexture = NULL;
    game->menuHostTexture = NULL;
    game->splashScreenTexture = NULL;
    game->menuJoinText = NULL;
    game->menuHostText = NULL;
    game->menuSelected = 1;
    game->playerPosition.x = (WINDOW_WIDTH / 2 - PLAYER_WIDTH);
    game->playerPosition.y = (WINDOW_HEIGHT / 2 - PLAYER_HEIGHT);
    game->playerPosition.w = PLAYER_WIDTH;
    game->playerPosition.h = PLAYER_HEIGHT;
    game->bombPosition.x = -9999;
    game->bombPosition.y = -9999;
    game->bombPosition.w = BOMB_WIDTH;
    game->bombPosition.h = BOMB_HEIGHT;
    game->menuJoinPosition.x = (WINDOW_WIDTH / 2);
    game->menuJoinPosition.y = (WINDOW_HEIGHT / 3);
    game->menuJoinPosition.w = 0;
    game->menuJoinPosition.h = 24;
    game->menuHostPosition.x = (WINDOW_WIDTH / 2);
    game->menuHostPosition.y = (WINDOW_HEIGHT - (WINDOW_HEIGHT / 3));
    game->menuHostPosition.w = 0;
    game->menuHostPosition.h = 24;
    game->splashScreenPosition.x = 0;
    game->splashScreenPosition.y = 0;
    game->splashScreenPosition.w = WINDOW_WIDTH;
    game->splashScreenPosition.h = WINDOW_HEIGHT;

    //init SDL
    if (sdl_init(game) < 0) {
        return NULL;
    }

    //init splashScreen
    if (splash_init(game) < 0) {
        return NULL;
    }

    //init menu
    if (menu_init(game) < 0) {
        return NULL;
    }

    //player texture load
    if (player_init(game) < 0) {
        return NULL;
    }

    //bomb texture load
    if (bomb_init(game) < 0) {
        return NULL;
    }

    return game;
}

/**
 * Init de la SDL, window & renderer
 * @params game_t *game
*/
int sdl_init(game_t *game)
{
    // init de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return print_error_sdl(game, "Erreur: SDL_Init video..");
    }

    // création de la fenêtre
    game->window = SDL_CreateWindow(
        "Bomberman",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        game->screenSize.x, game->screenSize.y,
        SDL_WINDOW_SHOWN
    );

    if (!game->window) { // gestion d'erreur
        return print_error_sdl(game, "Erreur: création de la fenêtre SDL...");
    }

    // création du renderer
    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);

    if (!game->renderer) { // gestion d'erreur
        return print_error_sdl(game, "Erreur: création du renderer SDL..");
    }

    return 0;
}

/**
 * Init du splashScreen
 * @params game_t *game
*/
int splash_init(game_t *game)
{
    SDL_Surface *splashScreenSurface;
    splashScreenSurface = IMG_Load("./assets/splashScreen.jpg");

    if (!splashScreenSurface) {
        return print_error_sdl(game, "Erreur: chargement de la texture du splashScreen..");
    }

    game->splashScreenTexture = SDL_CreateTextureFromSurface(game->renderer, splashScreenSurface);

    if (!game->splashScreenTexture) {
        return print_error_sdl(game, "Erreur: chargement de la texture du splashScreen..");
    }

    SDL_FreeSurface(splashScreenSurface);

    return 0;
}

/**
 * Init du menu
 * @params game_t *game
*/
int menu_init(game_t *game)
{
    // init du texte
    if(TTF_Init() < 0) {
        return print_error_sdl(game, "Erreur: initialisation du texte..");
    }

    game->font = TTF_OpenFont("OpenSans-Regular.ttf", 24);

    if (!game->font) {
        return print_error_sdl(game, "Erreur: récupération de la police de texte..");
    }

    game->menuJoinText = "Rejoindre une partie";
    game->menuHostText = "Héberger une partie";

    SDL_Color white = {255, 255, 255, 0};
    SDL_Color crimson = {220, 20, 60, 0};
    get_text_and_rect(game, game->menuJoinPosition.x, game->menuJoinPosition.y, game->menuJoinText, crimson, &game->menuJoinTexture, &game->menuJoinPosition);
    get_text_and_rect(game, game->menuHostPosition.x, game->menuHostPosition.y, game->menuHostText, white, &game->menuHostTexture, &game->menuHostPosition);

    return 0;
}

/**
 * Init de la texture du joueur
 * @params game_t *game
*/
int player_init(game_t *game)
{
    SDL_Surface *playerSurface;
    playerSurface = IMG_Load("./assets/player.png");

    if (!playerSurface) {
        return print_error_sdl(game, "Erreur: chargement de la texture du joueur..");
    }

    game->playerTexture = SDL_CreateTextureFromSurface(game->renderer, playerSurface);

    if (!game->playerTexture) {
        return print_error_sdl(game, "Erreur: chargement de la texture du joueur..");
    }

    SDL_FreeSurface(playerSurface);

    return 0;
}

/**
 * Init de la texture de la bombe
 * @params game_t *game
*/
int bomb_init(game_t *game)
{
    SDL_Surface *bombSurface;
    bombSurface = IMG_Load("./assets/bomb.png");

    if (!bombSurface) {
        return print_error_sdl(game, "Erreur: chargement de la texture de la bombe..");
    }

    game->bombTexture = SDL_CreateTextureFromSurface(game->renderer, bombSurface);

    if (!game->bombTexture) {
        return print_error_sdl(game, "Erreur: chargement de la texture de la bombe..");
    }

    SDL_FreeSurface(bombSurface);

    return 0;
}