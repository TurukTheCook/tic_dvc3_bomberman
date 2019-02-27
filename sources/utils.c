#include "game.h"

int print_error_sdl(game_t *game, char* message)
{
    fprintf(stderr, "%s %s\n", message, SDL_GetError());
    game_kill(game);
    return -1;
}