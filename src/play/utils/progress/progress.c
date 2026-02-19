#include "progress.h"
#include "../../../player/player.h" 

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

static int getTerminalWidth() {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
#else
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) return 80;
    return w.ws_col;
#endif
}

int progressThread(void* ptr) {
    Player *p = (Player*)ptr;

    while (p->running && !p->quit) {
        double elapsed = Mix_GetMusicPosition(p->music);
        if (elapsed < 0) break;

        int termWidth = getTerminalWidth();

        if (termWidth < 10) {
            printf("\r!\033[K");
            fflush(stdout);
            SDL_Delay(500);
            continue;
        }

        int reserved = 50;
        int barWidth = termWidth - reserved;

        if (barWidth > 50) barWidth = 50;
        if (barWidth < 10) {
            printf("\rToo small\033[K");
            fflush(stdout);
            SDL_Delay(500);
            
            continue;
        }

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