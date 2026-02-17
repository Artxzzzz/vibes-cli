#ifndef THREAD_H
#define THREAD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

void progressBar(double duration, Mix_Music* music);
void stopProgress();

#endif
