#include "game.h"

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

        // textures
        if (game->bombTexture) {
            SDL_DestroyTexture(game->bombTexture);
        }
        if (game->playerTexture) {
            SDL_DestroyTexture(game->playerTexture);
        }
        if (game->menuJoinTexture) {
            SDL_DestroyTexture(game->menuJoinTexture);
        }
        if (game->menuHostTexture) {
            SDL_DestroyTexture(game->menuHostTexture);
        }
        
        // renderer & window
        if (game->renderer) {
            SDL_DestroyRenderer(game->renderer);
        }
        if (game->window) {
            SDL_DestroyWindow(game->window);
        }

        // unconditionals kills
        TTF_Quit();
        SDL_Quit();
        free(game);
    }
}