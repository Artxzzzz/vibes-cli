#include <stdio.h>
#include <limits.h> 
#include "play.h"
#include "../player/player.h"

#include "utils/resolve/resolve.h"
#include "utils/format/format.h"
#include "utils/input/input.h"

int play(Player *p, char *musicPath) {

    char real[PATH_MAX];

    if (!resolvePath(musicPath, real)) {
        printf("File not found: %s\n", musicPath);
        return 1;
    }

    if (!loadPlayer(p, real)) {
        printf("Load error: %s\n", musicPath);
        return 1;
    }

    char name[PATH_MAX];
    getFileNameWithoutExt(real, name);

    printf("\nPlaying %s... Press \"q\" to exit\n", name);

    p->progressThread = SDL_CreateThread(progressThread, "Progress", p);

    if (!p->progressThread) {
        printf("Failed to create progress thread\n");
    }


    input(p);

    p->running = 0;
    SDL_WaitThread(p->progressThread, NULL);

    printf("\n");

    return 0;
}
