#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#include "sleep/sleep.h"
#include "config/config.h"
#include "play/play.h"
#include "playDirectory/inc.h"
#include "player/player.h"
#include "help/help.h"

#define ISARG(short_opt, long_opt) \
    (strcmp(argv[arg], "-" short_opt) == 0 || \
     strcmp(argv[arg], "--" long_opt) == 0)

int main(int argc, char **argv) {
    int tosleep = 1;
    int versionBool = 0;
    int loop = 0;
    char *musicPath = NULL;

    int result = 0;

    if (argc < 2) {
        printf("Use: vibes <music>\n");
        return 1;
    }

    for (int arg = 1; arg < argc; arg++) {
        if (ISARG("v", "version")) {versionBool = 1; continue;}
        if (ISARG("s", "sleep")) {tosleep = 0; continue;}
        if (ISARG("l", "loop")) {loop = 1; continue;}
        if (ISARG("h", "help")) {help(); return 0;}

        if (argv[arg][0] == '-') {
            fprintf(stderr, "Error: unknown option: '%s'\n", argv[arg]);
            return 1;
        }

        musicPath = argv[arg];
    }

    if (versionBool) {
        printf("Vibes %s\n", version);
        return 0;
    }

    if (!musicPath) {
        fprintf(stderr, "No music file provided.\n");
        return 1;
    }

    int loopOriginal = loop;
    char *folder = checkFolder(musicPath);

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
        result = play(p, musicPath);
    }

    playerDestroy(p);
    return result;
}
