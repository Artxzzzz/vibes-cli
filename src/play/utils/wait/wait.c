#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#ifdef _WIN32
#include <conio.h>
#endif

void wait() {
    int done = 0;
    
    while (!done) {
        if (!Mix_PlayingMusic()) {
            done = 1;
            break;
        }

        #ifdef _WIN32
        if (_kbhit()) {
            _getch();
            done = 1;
        }
        #else
        struct timeval tv = {0L, 100000L};
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(0, &fds);
        if (select(1, &fds, NULL, NULL, &tv)) {
            getchar();
            done = 1;
        }
        #endif

        SDL_Delay(100);
    }
}
