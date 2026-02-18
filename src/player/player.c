#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Player* playerCreate(int loopValue) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) return NULL;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_Quit();
        return NULL;
    }

    Player *p = malloc(sizeof(Player));
    
    if (!p) {
        Mix_CloseAudio();
        SDL_Quit();
        return NULL;
    }


    p->music = NULL;
    p->duration = 0;
    p->vol = MIX_MAX_VOLUME; // 128
    p->running = 0;
    p->paused = 0;
    p->quit = 0;
    p->loop = -loopValue;

    p->progressThread = NULL;
    memset(p->currentPath, 0, PATH_MAX);

    return p;
}

int loadPlayer(Player *p, const char *path) {
    if (p->music) {
        Mix_FreeMusic(p->music);
        p->music = NULL;
    }

    p->music = Mix_LoadMUS(path);
    if (!p->music) return 0;

    strncpy(p->currentPath, path, PATH_MAX);
    p->duration = Mix_MusicDuration(p->music);
    
    p->running = 1;
    p->paused = 0;
    
    Mix_VolumeMusic(p->vol);
    Mix_PlayMusic(p->music, p->loop);
    
    return 1;
}

void playerDestroy(Player *p) {
    if (!p) return;
    if (p->music) Mix_FreeMusic(p->music);
    
    Mix_CloseAudio();
    SDL_Quit();
    free(p);
}