#include <stdio.h>
#include "input.h"

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <sys/select.h>

    static void setConio(int on) {
        static struct termios oldt, newt;
        if (on) {
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        } else {
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        }
    }

#endif

#define KEYUP    1001
#define KEYDOWN  1002
#define KEYLEFT  1003
#define KEYRIGHT 1004
#define ESC      1005

void input(Player* p) {

    static Uint32 lastSeekTime = 0;
    

    #ifndef _WIN32
        setConio(1); 
    #endif

    while (!p->quit) {
        Uint32 currentTime = SDL_GetTicks();

        if (!Mix_PlayingMusic() && !Mix_PausedMusic() && !p->paused) {
            break;
        }

        int ch = -1;

        #ifdef _WIN32
        if (_kbhit()) {
            ch = _getch();
            if (ch == 0 || ch == 224) {
                ch = _getch();
                if (ch == 72) ch = KEYUP;
                else if (ch == 80) ch = KEYDOWN;
                else if (ch == 75) ch = KEYLEFT;
                else if (ch == 77) ch = KEYRIGHT;
            } else if (ch == 27) {
                ch = ESC;
            }

            if (ch == KEYRIGHT || ch == KEYLEFT) {
                while(_kbhit()) _getch(); 
            }
        }

        #else

        struct timeval tv = {0L, 50000L};
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(0, &fds);

        if (select(1, &fds, NULL, NULL, &tv)) {
            ch = getchar();

            if (ch == 27) {

                struct timeval tv_small = {0L, 50000L};
                fd_set fds_small;
                FD_ZERO(&fds_small);
                FD_SET(0, &fds_small);

                if (select(1, &fds_small, NULL, NULL, &tv_small)) {
                    int next = getchar();
                    if (next == '[') {
                        int code = getchar();
                        if (code == 'A') ch = KEYUP;
                        else if (code == 'B') ch = KEYDOWN;
                        else if (code == 'D') ch = KEYLEFT;
                        else if (code == 'C') ch = KEYRIGHT;
                    }
                } else {
                    ch = ESC;
                }
            }
        }
        #endif

        if (ch != -1) {

            switch (ch) {
                case 'q': 
                case 'Q': 
                #ifdef _WIN32
                case ESC: 
                #endif
                    Mix_HaltMusic();

                    p->quit = 1;
                    p->running = 0;

                    printf("\n");
                    break;

                case ' ':
                    p->paused = !p->paused;

                    if (p->paused) Mix_PauseMusic();
                    else Mix_ResumeMusic();
                    break;

                case KEYUP:

                    p->vol = (p->vol + 5 > 128) ? 128 : p->vol + 5;
                    Mix_VolumeMusic(p->vol);
                    break;

                case 'L': case 'l':
                    p->loop = !p->loop;
                    break;

                case KEYDOWN:

                    p->vol = (p->vol - 5 < 0) ? 0 : p->vol - 5;
                    Mix_VolumeMusic(p->vol);
                    break;

                case KEYRIGHT:

                    if (currentTime - lastSeekTime > 150) {
                        double pos = Mix_GetMusicPosition(p->music);
                        if (pos >= 0) {

                            Mix_PauseMusic();
                            Mix_SetMusicPosition(pos + 5.0);
                            Mix_ResumeMusic();
                            lastSeekTime = currentTime;

                        }
                    }
                    break;

                case KEYLEFT:

                    if (currentTime - lastSeekTime > 150) {
                        double pos = Mix_GetMusicPosition(p->music);
                        if (pos >= 0) {
                            double newPos = (pos - 5.0 < 0) ? 0 : pos - 5.0;
                            Mix_PauseMusic();
                            Mix_RewindMusic();
                            Mix_SetMusicPosition(newPos);
                            Mix_ResumeMusic();
                            lastSeekTime = currentTime;
                        }
                    }
                    break;
            }
        }

        if (!Mix_PlayingMusic() && !Mix_PausedMusic()) {
            p->running = 0;
        }

        SDL_Delay(50);

    }

    #ifndef _WIN32
    setConio(0);
    #endif
}