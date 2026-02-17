#ifndef PROGRESS_H
#define PROGRESS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "thread/thread.h"

int progressThread(void* ptr);

typedef struct {
    double duration;
    Mix_Music* music;
} ThreadData;

extern int running;

#endif
