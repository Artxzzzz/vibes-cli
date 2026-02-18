#include "progress.h"
#include "../../../player/player.h" 

int progressThread(void* ptr) {
    Player *p = (Player*)ptr;

    int barWidth = 50;

    while (p->running && !p->quit) {
        double elapsed = Mix_GetMusicPosition(p->music);
        if (elapsed < 0) break;

        if (p->duration <= 0) {
            SDL_Delay(500);
            continue;
        }


        int pos = (int)((elapsed * barWidth) / p->duration);
        int volPercent = (p->vol * 100) / 128;

        printf("\r[");
        for (int i = 0; i < barWidth; i++) {
            printf(i < pos ? "#" : ".");
        }

        printf("] %d:%02d / %d:%02d | Vol: %d%% %s\033[K", 

            (int)elapsed/60, (int)elapsed%60, 
            (int)p->duration/60, (int)p->duration%60, 
            volPercent, p->paused ? "(PAUSED)" : "");
        
        fflush(stdout);
        SDL_Delay(500);
    }

    return 0;
}