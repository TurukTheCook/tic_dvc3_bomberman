#include "game.h"

/**
 * Render l'ecran d'accueil
 * @params game_t *game
*/
void welcome_run(game_t *game, SDL_Event *event, SDL_bool *welcome)
{
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    // draw text
    SDL_RenderCopy(game->renderer, game->splashScreenTexture, NULL, &game->splashScreenPosition);
    
    SDL_RenderPresent(game->renderer);

    SDL_Delay(3000);
    *welcome = SDL_FALSE;
}

/**
 * Render le jeu
 * @params game_t *game
*/
void menu_run(game_t *game, SDL_Event *event, SDL_bool *menu, SDL_bool *play)
{
    while (SDL_PollEvent(event))
    {
        menu_render(game);

        switch (event->type)
        {
            case SDL_KEYDOWN:
                switch (event->key.keysym.sym)
                {
                    case SDLK_UP:
                    case SDLK_DOWN:
                        menu_change(game, event->key.keysym.sym);
                        break;

                    case SDLK_SPACE:
                    case SDLK_KP_ENTER:
                        menu_choose(game, menu);
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
 * Render le menu
 * @params game_t *game
*/
void menu_render(game_t *game)
{
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    // draw text
    SDL_RenderCopy(game->renderer, game->menuJoinTexture, NULL, &game->menuJoinPosition);
    SDL_RenderCopy(game->renderer, game->menuHostTexture, NULL, &game->menuHostPosition);
    
    SDL_RenderPresent(game->renderer);
}

void menu_change(game_t *game, SDL_Keycode direction)
{
    SDL_Color white = {255, 255, 255, 0};
    SDL_Color crimson = {220, 20, 60, 0};

    // needed to center text
    int menuJoinTextureWidth, menuJoinTextureHeight;
    int menuHostTextureWidth, menuHostTextureHeight;
    SDL_QueryTexture(game->menuJoinTexture, NULL, NULL, &menuJoinTextureWidth, &menuJoinTextureHeight);
    SDL_QueryTexture(game->menuHostTexture, NULL, NULL, &menuHostTextureWidth, &menuHostTextureHeight);

    switch (direction)
    {
        case SDLK_UP:
            game->menuSelected = 1;
            SDL_DestroyTexture(game->menuJoinTexture);
            SDL_DestroyTexture(game->menuHostTexture);
            get_text_and_rect(game, game->menuJoinPosition.x + (menuJoinTextureWidth / 2), game->menuJoinPosition.y, game->menuJoinText, crimson, &game->menuJoinTexture, &game->menuJoinPosition);
            get_text_and_rect(game, game->menuHostPosition.x + (menuHostTextureWidth / 2), game->menuHostPosition.y, game->menuHostText, white, &game->menuHostTexture, &game->menuHostPosition);
            break;
        case SDLK_DOWN:
            game->menuSelected = 2;
            SDL_DestroyTexture(game->menuJoinTexture);
            SDL_DestroyTexture(game->menuHostTexture);
            get_text_and_rect(game, game->menuJoinPosition.x + (menuJoinTextureWidth / 2), game->menuJoinPosition.y, game->menuJoinText, white, &game->menuJoinTexture, &game->menuJoinPosition);
            get_text_and_rect(game, game->menuHostPosition.x + (menuHostTextureWidth / 2), game->menuHostPosition.y, game->menuHostText, crimson, &game->menuHostTexture, &game->menuHostPosition);
            break;

        default:
        break;
    }
}

void menu_choose(game_t *game, SDL_bool *menu)
{
    // *menu = SDL_FALSE; // not for now TODO: implement later
    if (game->menuSelected == 1) {
        client_connect();
    } else if (game->menuSelected == 2) {
        server_launch();
    }
}