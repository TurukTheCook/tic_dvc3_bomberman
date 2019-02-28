#include "game.h"

/**
 * Créer du texte
 * @params game_t *game [...]
*/
int get_text_and_rect(game_t *game, int pos_x, int pos_y, char *text, SDL_Color color, SDL_Texture **texture, SDL_Rect *rect)
{
    int text_width;
    int text_height;
    SDL_Surface *textSurface;
    // SDL_Color textColor = {255, 255, 255, 0};

    textSurface = TTF_RenderText_Solid(game->font, text, color);

    if (!textSurface) {
        return print_error_sdl(game, "Erreur: chargement de la texture du texte..");
    }

    *texture = SDL_CreateTextureFromSurface(game->renderer, textSurface);

    if (!texture) {
        return print_error_sdl(game, "Erreur: chargement de la texture du texte..");
    }

    text_width = textSurface->w;
    text_height = textSurface->h;

    rect->x = pos_x;
    rect->y = pos_y;
    rect->w = text_width;
    rect->h = text_height;

    SDL_FreeSurface(textSurface);
    return 0;
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
    SDL_Color yellow = {255, 255, 0, 0};

    switch (direction)
    {
        case SDLK_UP:
            game->menuSelected = 1;
            SDL_DestroyTexture(game->menuJoinTexture);
            SDL_DestroyTexture(game->menuHostTexture);
            get_text_and_rect(game, game->menuJoinPosition.x, game->menuJoinPosition.y, "Rejoindre une partie", yellow, &game->menuJoinTexture, &game->menuJoinPosition);
            get_text_and_rect(game, game->menuHostPosition.x, game->menuHostPosition.y, "Heberger une partie", white, &game->menuHostTexture, &game->menuHostPosition);
            break;
        case SDLK_DOWN:
            game->menuSelected = 2;
            SDL_DestroyTexture(game->menuJoinTexture);
            SDL_DestroyTexture(game->menuHostTexture);
            get_text_and_rect(game, game->menuJoinPosition.x, game->menuJoinPosition.y, "Rejoindre une partie", white, &game->menuJoinTexture, &game->menuJoinPosition);
            get_text_and_rect(game, game->menuHostPosition.x, game->menuHostPosition.y, "Heberger une partie", yellow, &game->menuHostTexture, &game->menuHostPosition);
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