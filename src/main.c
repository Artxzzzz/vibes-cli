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
#include "history/history.h"
#include "checkarg/checkarg.h"

#define ISARG(short_opt, long_opt) \
    isarg(argv[arg], short_opt, long_opt, &val)


int main(int argc, char **argv) {
    int tosleep = 1;
    int historyActive = 1;
    int vol = -1;

    int versionBool = 0;
    int loop = 0;
    char *musicPath = NULL;
    

    int result = 0;

    if (argc < 2) {
        printf("Use: vibes <music>\n");
        return 1;
    }

    for (int arg = 1; arg < argc; arg++) {
        const char *val;

        if (ISARG("v", "version")) {versionBool = 1; continue;}
        if (ISARG("s", "sleep")) {tosleep = 0; continue;}
        if (ISARG("l", "loop")) {loop = 1; continue;}
        if (ISARG("h", "help")) {help(); return 0;}
        if (ISARG("H", "history")) {showHistory(val); return 0;}
        if (ISARG(NULL, "no-save")) {historyActive = 0; continue;}
        if (ISARG("V", "volume")) {
            if (val) {
                int num = atoi(val);

                if (num < 0 || num > 100) {
                    printf("Invalid volume: '%s'. Must be a number (0-100).\n", val);
                    printf("Using default volume\n");

                    num = -1;
                }

                vol = (num * 128 / 100); // For visual, small precision less but it's necessary
            }

            else {
                printf("Invalid volume.\n", val);
                printf("Using default volume\n");
            }

            continue;
        }

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

    if (historyActive) historyInit();
    int loopOriginal = loop;
    char *folder = checkFolder(musicPath);

    if (folder && loop) loop = 0;

    Player *p = playerCreate(loop, vol);
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
