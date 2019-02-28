/*
*   PROJECT BOMBERMAN
*/

#include "game.h"

int main(int argc, char **argv)
{
    // FOR REFERENCE, TODO: delete after menu implemented
    // char command[256];
    // memset(command, '\0', 256);
    // fgets(command, 256, stdin);
    // if (strcmp(command, "client\n") == 0) {
    //     client_connect();
    // } else if (strcmp(command, "server\n") == 0) {
    //     server_launch();
    // } else {
    //     printf("Wrong command, please write 'client' or 'server'");
    // }


    // init du jeu, ses variables, la SDL
    game_t *game = game_init();

    if (!game) {
        return -1;
    }

    // init variables pour la limite de fps
    Uint32 currTime, prevTime, msPerFrame;
	currTime = 0;
	prevTime = 0;
	msPerFrame = 1000/FPS;

    // init variables boucle de jeu
    SDL_Event event;
    SDL_bool play = SDL_TRUE;
    SDL_bool menu = SDL_TRUE;

    while (play)
    {
        currTime = SDL_GetTicks(); // récupère le temps actuel en ms
        if ((currTime - prevTime) > msPerFrame) { // continue si la diff de temps est supérieure à msPerFrame (16 pour 60fps)
            prevTime = currTime;

            if (menu) {
                // gestion du menu
                menu_run(game, &event, &menu, &play);
            } else {
                // gestion du jeu
                game_run(game, &event, &play);
            }
            

        } else { // sinon attend 
            SDL_Delay(msPerFrame - (currTime - prevTime));
        }
        // SDL_Delay(5); // instaure un minuscule delay obligatoire, à tester voir si utile en plus du frame_limit.
    }

    // free
    game_kill(game);
    
    return 0;
}