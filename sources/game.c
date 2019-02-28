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
    game->menuSelected = 1;
    game->playerPosition.x = (WINDOW_WIDTH / 2 - PLAYER_WIDTH);
    game->playerPosition.y = (WINDOW_HEIGHT / 2 - PLAYER_HEIGHT);
    game->playerPosition.w = PLAYER_WIDTH;
    game->playerPosition.h = PLAYER_HEIGHT;
    game->bombPosition.x = -9999;
    game->bombPosition.y = -9999;
    game->bombPosition.w = BOMB_WIDTH;
    game->bombPosition.h = BOMB_HEIGHT;
    game->menuJoinPosition.x = (WINDOW_WIDTH / 2 -150);
    game->menuJoinPosition.y = (WINDOW_HEIGHT / 3);
    game->menuJoinPosition.w = 24;
    game->menuJoinPosition.h = 24;
    game->menuHostPosition.x = (WINDOW_WIDTH / 2 -150);
    game->menuHostPosition.y = (WINDOW_HEIGHT - (WINDOW_HEIGHT / 3));
    game->menuHostPosition.w = 24;
    game->menuHostPosition.h = 24;

    //init SDL
    if (sdl_init(game) < 0) {
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

    SDL_Color white = {255, 255, 255, 0};
    SDL_Color yellow = {255, 255, 0, 0};
    get_text_and_rect(game, game->menuJoinPosition.x, game->menuJoinPosition.y, "Rejoindre une partie", yellow, &game->menuJoinTexture, &game->menuJoinPosition);
    get_text_and_rect(game, game->menuHostPosition.x, game->menuHostPosition.y, "Heberger une partie", white, &game->menuHostTexture, &game->menuHostPosition);

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

/**
 * Render le jeu
 * @params game_t *game
*/
void game_render(game_t *game)
{
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    // draw bomb only if on screen
    if (game->bombPosition.x > (-15) && game->bombPosition.x < WINDOW_WIDTH && game->bombPosition.y > (-15) && game->bombPosition.y < WINDOW_HEIGHT) {
        SDL_RenderCopy(game->renderer, game->bombTexture, NULL, &game->bombPosition);
    }

    // draw player
    SDL_RenderCopy(game->renderer, game->playerTexture, NULL, &game->playerPosition);
    
    SDL_RenderPresent(game->renderer);
}

/**
 * Render le jeu
 * @params game_t *game
*/
void game_run(game_t *game, SDL_Event *event, SDL_bool *play)
{
    while (SDL_PollEvent(event))
    {
        game_render(game);

        switch (event->type)
        {
            case SDL_KEYDOWN:
                switch (event->key.keysym.sym)
                {
                    case SDLK_z:
                    case SDLK_q:
                    case SDLK_s:
                    case SDLK_d:
                        game_move_player(game, event->key.keysym.sym);
                        break;

                    case SDLK_SPACE:
                        game_plant_bomb(game);
                        break;

                    default:
                        break;
                }
                break;

            case SDL_QUIT:
                *play = SDL_FALSE;
                break;
            
            default:
                break;
        }
    }
}

/**
 * Free les ressources du jeu et de la SDL
 * @params game_t *game, SDL_Keycode event.key.keysym.sym
*/
void game_move_player(game_t *game, SDL_Keycode direction)
{
    switch (direction)
    {
        case SDLK_z:
            if (game->playerPosition.y > 0) {
                game->playerPosition.y -= 10;
            }
            break;
        case SDLK_q:
            if (game->playerPosition.x > 0) {
                game->playerPosition.x -= 10;
            }
            break;
        case SDLK_s:
            if (game->playerPosition.y < (game->screenSize.y - game->playerPosition.h)) {
                game->playerPosition.y += 10;
            }
            break;
        case SDLK_d:
            if (game->playerPosition.x < (game->screenSize.x - game->playerPosition.w)) {
                game->playerPosition.x += 10;
            }
            break;

        default:
        break;
    }
}

/**
 * Free les ressources du jeu et de la SDL
 * @params game_t *game, SDL_Keycode event.key.keysym.sym
*/
void game_plant_bomb(game_t *game)
{
    game->bombPosition.x = game->playerPosition.x;
    game->bombPosition.y = game->playerPosition.y;
}


/**
 * Free les ressources du jeu et de la SDL
 * @params game_t *game
*/
void game_kill(game_t *game)
{
    if (game) {
        // conditionals kills
        if (game->bombTexture) {
            SDL_DestroyTexture(game->bombTexture);
        }

        if (game->playerTexture) {
            SDL_DestroyTexture(game->playerTexture);
        }
        
        if (game->renderer) {
            SDL_DestroyRenderer(game->renderer);
        }
        if (game->window) {
            SDL_DestroyWindow(game->window);
        }

        // unconditionals
        TTF_Quit();
        SDL_Quit();
        free(game);
    }
}