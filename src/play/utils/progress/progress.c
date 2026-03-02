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

const Colors COLORS[] = {
    {"black",   "\x1b[30m"},
    {"red",     "\x1b[31m"},
    {"green",   "\x1b[32m"},
    {"yellow",  "\x1b[33m"},
    {"blue",    "\x1b[34m"},
    {"magenta", "\x1b[35m"},
    {"cyan",    "\x1b[36m"},
    {"gray",    "\x1b[37m"},
    {"white",   "\x1b[0m"},
};

const int COLORSIZE = sizeof(COLORS)/sizeof(COLORS[0]);

void setColor(char *color) {
    for (int idx = 0; idx < COLORSIZE; idx++) {
        if (strcmp(COLORS[idx].name, color) == 0) {
            printf("%s", COLORS[idx].value);
            return;
        }
    }
}

int progressThread(void* ptr) {
    Player *p = (Player*)ptr;

    while (p->running && !p->quit) {
        if (!p->config.showBar) {
            SDL_Delay(500);
            continue;
        }

        double elapsed = Mix_GetMusicPosition(p->music);
        if (elapsed < 0) break;

        int termWidth = getTerminalWidth();

        if (termWidth < 10) {
            printf("\r!\033[K");
            fflush(stdout);
            SDL_Delay(500);
            continue;
        }

        int reserved = 40;

        int barWidth = termWidth - reserved;

        if (barWidth > p->config.barMaxWidth) {
            barWidth = p->config.barMaxWidth;
        }

        if (barWidth < 5) {
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
        volPercent = (volPercent + 2) / 5 * 5;

        printf("\r[");
        for (int i = 0; i < barWidth; i++) {

            char *ch;
            char *color;

            if (i < pos) {
                ch = p->config.barChar;
                color = p->config.fullCharColor;
            } else {
                ch = p->config.emptyChar;
                color = p->config.emptyCharColor;
            }
            
            setColor(color);

            printf("%s", ch);

            setColor("white");
        }

        printf("] %d:%02d / %d:%02d | Vol: %d%% %s %s\033[K", 
        (int)elapsed/60, (int)elapsed%60, 
        (int)p->duration/60, (int)p->duration%60, 
        volPercent, p->paused ? "(PAUSED)" : "",
        p->loop ? "(LOOP)" : "");
        
        fflush(stdout);
        SDL_Delay(500);
    }

    return 0;
}