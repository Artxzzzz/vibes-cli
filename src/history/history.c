#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(path) _mkdir(path)
    #define BAR "\\"
#else
    #include <unistd.h>
    #define MKDIR(path) mkdir(path, 0755)
    #define BAR "/"
#endif

#include "history.h"
#include "util/getUser.h"
#include "../config/config.h"

int historyOk = 0;
char historyPath[PATH_MAX];

static void ensureDirExists(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) MKDIR(path);
}


void historyInit() {
    char *home = getUser();

    if (!home) {
        historyOk = 0;
        return;
    }

    char configPath[PATH_MAX];
    char vibesPath[PATH_MAX];

    snprintf(configPath, sizeof(configPath), "%s" BAR "%s", home, CONFIGDIR);
    snprintf(vibesPath, sizeof(vibesPath), "%s" BAR "%s", configPath, VIBESDIR);
    ensureDirExists(configPath);
    ensureDirExists(vibesPath);

    snprintf(historyPath, sizeof(historyPath), "%s" BAR "%s", vibesPath, CONFIGFILE);

    FILE *f = fopen(historyPath, "a");

    if (!f) {
        perror("Failed to open history file");
        historyOk = 0;
        return;
    }


    fclose(f);
    historyOk = 1;
}