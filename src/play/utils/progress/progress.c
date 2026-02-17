#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "progress.h"

int running = 0;

int progressThread(void* ptr) {
    ThreadData* data = (ThreadData*)ptr;
    double duration = data->duration;
    Mix_Music* music = data->music;

    free(data);

    int barWidth = 50;

    while (running) {
        double elapsed = Mix_GetMusicPosition(music);

        if (elapsed < 0) break;
        if (elapsed > duration) elapsed = duration;

        int pos = (int)((elapsed * barWidth) / duration);

        int eMin = (int)elapsed / 60;
        int eSec = (int)elapsed % 60;
        int dMin = (int)duration / 60;
        int dSec = (int)duration % 60;

        printf("\r[");
        for (int i = 0; i < barWidth; i++) {
            if (i < pos) printf("#");
            else printf(".");
        }
        printf("] %d:%02d / %d:%02d", eMin, eSec, dMin, dSec);
        fflush(stdout);

        SDL_Delay(500);
    }

    printf("\n");
    return 0;
}