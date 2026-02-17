#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "config/config.h"
#include "play/play.h"
#include "playDirectory/inc.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Use: vibes <music>\n");
        return 1;
    }

    if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
        printf("Vibes %s\n", version);
        return 0;
    }

    char *folder = checkFolder(argv[1]);
    if (folder) {
        char files[100][PATH_MAX];
        int total = getAudio(folder, files, 100);
        int ok = 0;

        for (int audio = 0; audio < total; audio++) {
            char path[PATH_MAX];
            #ifdef _WIN32
                snprintf(path, sizeof(path), "%s\\%s", folder, files[audio]);
            #else
                snprintf(path, sizeof(path), "%s/%s", folder, files[audio]);
            #endif

            ok = play(path);
            if (ok != 0) {
                printf("Error to play: %s\n", path);
            }
        }

        return 0;
    }

    else {
        return play(argv[1]);
    }
}
