#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <limits.h>
#include "../config/config.h"

typedef struct {
    Mix_Music *music;

    double duration; // Music duration
    int vol; // Volume
    int running; // Running bool
    int paused; // Paused bool
    int quit; // Quit bool
    int loop; // Loop bool (-1 = true, 0 = false)

    Config config; // Configuration

    char currentPath[PATH_MAX]; // Music playing path
    SDL_Thread* progressThread; // Progress bar Thread
} Player;

Player *playerCreate(int loopValue, int vol, Config cfg);
void playerDestroy(Player *p);

int loadPlayer(Player *p, const char *path);

#endif
