#ifndef PROGRESS_H
#define PROGRESS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int progressThread(void* ptr);

typedef struct {
    const char *name;
    const char *value;
} Colors;

extern const Colors COLORS[];
extern const int COLORSIZE;

#endif
