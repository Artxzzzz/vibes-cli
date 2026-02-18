#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "sleep/sleep.h"
#include "config/config.h"
#include "play/play.h"
#include "playDirectory/inc.h"
#include "player/player.h"

int main(int argc, char **argv) {
    int tosleep = 1;
    int versionBool = 0;
    int loop = 0;

    int result = 0;

    if (argc < 2) {
        printf("Use: vibes <music>\n");
        return 1;
    }

    for (int arg = 1; arg < argc; arg++) {
        if (strcmp(argv[arg], "-v") == 0 || strcmp(argv[arg], "--version") == 0) versionBool = 1;
        if (strcmp(argv[arg], "-s") == 0 || strcmp(argv[arg], "--sleep") == 0) tosleep = 0;
        if (strcmp(argv[arg], "-l") == 0 || strcmp(argv[arg], "--loop") == 0) loop = 1;
    }

    if (versionBool) {
        printf("Vibes %s\n", version);
        return 0;
    }

    int loopOriginal = loop;
    char *folder = checkFolder(argv[1]);

    if (folder && loop) loop = 0;

    Player *p = playerCreate(loop);
    if (!p) return 1;
    loop = loopOriginal;
    
    if (folder) {
        char files[100][PATH_MAX];
        int total = getAudio(folder, files, 100);
        
        do {
            for (int audio = 0; audio < total; audio++) {
                char path[PATH_MAX * 2];
                
                #ifdef _WIN32
                    snprintf(path, sizeof(path), "%s\\%s", folder, files[audio]);
                #else
                    snprintf(path, sizeof(path), "%s/%s", folder, files[audio]);
                #endif

                play(p, path);

                if (p->quit) break;

                if (tosleep) msleep(.25);
            }
        } while(loop && !p->quit);

        result = 0;
        free(folder);
    }

    else {
        result = play(p, argv[1]);
    }

    playerDestroy(p);
    return result;
}
