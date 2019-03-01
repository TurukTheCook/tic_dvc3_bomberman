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
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define PLAYER_WIDTH 89
#define PLAYER_HEIGHT 97
#define BOMB_WIDTH 43
#define BOMB_HEIGHT 50

typedef struct {
    SDL_Point screenSize;
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    SDL_Texture *playerTexture;
    SDL_Texture *bombTexture;
    SDL_Texture *menuJoinTexture;
    SDL_Texture *menuHostTexture;
    SDL_Texture *splashScreenTexture;
    char *menuJoinText;
    char *menuHostText;
    int menuSelected;
    SDL_Rect playerPosition;
    SDL_Rect bombPosition;
    SDL_Rect menuJoinPosition;
    SDL_Rect menuHostPosition;
    SDL_Rect splashScreenPosition;
    int menuJoinWidth;
    int menuHostWidth;
} game_t;

// fonctions d'init
int sdl_init(game_t *game);
game_t *game_init(void);
int splash_init(game_t *game);
int menu_init(game_t *game);
int player_init(game_t *game);
int bomb_init(game_t *game);

// menu
void welcome_run(game_t *game, SDL_Event *event, SDL_bool *welcome); //splashscreen
int get_text_and_rect(game_t *game, int pos_x, int pos_y, char *text, SDL_Color color, SDL_Texture **texture, SDL_Rect *rect);
void menu_run(game_t *game, SDL_Event *event, SDL_bool *menu, SDL_bool *play);
void menu_render(game_t *game);
void menu_change(game_t *game, SDL_Keycode direction);
void menu_choose(game_t *game, SDL_bool *menu);

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