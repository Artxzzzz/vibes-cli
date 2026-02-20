#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

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

static char historyPath[512];
static int historyOk = 0;

void historyInit() {

    char *home = getUser();

    if (!home) {
        historyOk = 0;
        return;
    }

    char configPath[512];
    char vibesPath[512];

    snprintf(configPath, sizeof(configPath),
             "%s" BAR "%s",
             home, CONFIGDIR);

    snprintf(vibesPath, sizeof(vibesPath),
             "%s" BAR "%s",
             configPath, VIBESDIR);

    snprintf(historyPath, sizeof(historyPath),
             "%s" BAR "%s",
             vibesPath, CONFIGFILE);

    struct stat st = {0};

    if (stat(configPath, &st) == -1) {
        MKDIR(configPath);
    }

    if (stat(vibesPath, &st) == -1) {
        MKDIR(vibesPath);
    }

    FILE *f = fopen(historyPath, "a");
    if (!f) {
        historyOk = 0;
        return;
    }

    fclose(f);
    historyOk = 1;
}

void historyAdd(const char *musicPath) {
    if (!historyOk) return;

    FILE *f = fopen(historyPath, "a");
    if (!f) return;

    fprintf(f, "%s\n", musicPath);
    fclose(f);
}

void showHistory() {
    historyInit();

    FILE *f = fopen(historyPath, "r");
    if (!f) return;

    char *content[100];
    char buffer[256];
    int count = 0;

    while (fgets(buffer, sizeof(buffer), f)) {
        buffer[strcspn(buffer, "\n")] = 0;

        content[count] = malloc(strlen(buffer) + 1);
        strcpy(content[count], buffer);

        count++;
    }

    fclose(f);

    for (int line = 0; line < count; line++) {
        printf("%s\n", content[line]);
        free(content[line]);
    }
}