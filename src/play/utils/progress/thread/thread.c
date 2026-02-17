#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "thread.h"
#include "../progress.h"

void progressBar(double duration, Mix_Music* music) {
    running = 1;

    ThreadData* data = malloc(sizeof(ThreadData));
    if (!data) {
        printf("Failed to allocate memory\n");
        return;
    }
    data->duration = duration;
    data->music = music;

    SDL_Thread* thread = SDL_CreateThread(progressThread, "ProgressThread", data);
    
    if (!thread) {
        printf("Failed to start progress thread: %s\n", SDL_GetError());
        free(data);
    } else {
        SDL_DetachThread(thread);
    }
}

void stopProgress() {
    running = 0;
}