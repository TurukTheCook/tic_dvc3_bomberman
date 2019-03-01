#include "game.h"

/**
 * Affiche une erreur et kill le jeu
 * @params game_t *game [...]
*/
int print_error_sdl(game_t *game, char* message)
{
    fprintf(stderr, "%s %s\n", message, SDL_GetError());
    game_kill(game);
    return -1;
}

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

    textSurface = TTF_RenderUTF8_Solid(game->font, text, color);

    if (!textSurface) {
        return print_error_sdl(game, "Erreur: chargement de la texture du texte..");
    }

    *texture = SDL_CreateTextureFromSurface(game->renderer, textSurface);

    if (!texture) {
        return print_error_sdl(game, "Erreur: chargement de la texture du texte..");
    }

    text_width = textSurface->w;
    text_height = textSurface->h;

    rect->x = pos_x - (text_width / 2);
    rect->y = pos_y;
    rect->w = text_width;
    rect->h = text_height;

    SDL_FreeSurface(textSurface);
    return 0;
}