#ifndef GAME_H
#define GAME_H

// standard
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>

// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// MACROS
#define SERVER_PORT 1407
#define FPS 60
#define BACKLOG 5

typedef struct {
    SDL_Point screenSize;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *playerTexture;
    SDL_Texture *bombTexture;
    SDL_Rect playerPosition;
    SDL_Rect bombPosition;
} game_t;

// fonctions d'init
int sdl_init(game_t *game);
game_t *game_init(void);
int player_init(game_t *game);
int bomb_init(game_t *game);

// fonctions serveur / client
int read_client(int client);
int server_launch(void);
int client_connect(void);

// fonctions intermédiaires
void game_render(game_t *game);
void game_run(game_t *game, SDL_Event *event, SDL_bool *play);
void game_move_player(game_t *game, SDL_Keycode direction);
void game_plant_bomb(game_t *game);

// fonctions de fin / erreur
void game_kill(game_t *game);
int print_error_sdl(game_t *game, char* message);

#endif // GAME_H