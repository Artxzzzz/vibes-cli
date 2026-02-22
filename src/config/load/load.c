#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <sys/stat.h>

#include "load.h"
#include "../config.h"
#include "parser/parser.h"
#include "../../helpers/helpers.h"

#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(path) _mkdir(path)
    #define BAR "\\"
#else
    #include <unistd.h>

    #define MKDIR(path) mkdir(path, 0755)
    #define BAR "/"
#endif

static char *trim(char *str) {
    char *end;

    while (isspace((unsigned char)*str)) str++;

    if (*str == 0) return str;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    *(end + 1) = '\0';

    return str;
}

static void ensureDirExists(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == 0) {
        if (S_ISDIR(st.st_mode)) return;
        return;
    }
    MKDIR(path);

}

void loadConfig(Config *cfg) {
    char *home = getUser();

    if (!home) {
        return;
    }

    char configPath[PATH_MAX];
    char vibesPath[PATH_MAX];

    snprintf(configPath, sizeof(configPath), "%s" BAR "%s", home, CONFIGDIR);
    snprintf(vibesPath, sizeof(vibesPath), "%s" BAR "%s", configPath, VIBESDIR);
    ensureDirExists(configPath);
    ensureDirExists(vibesPath);

    char configFile[PATH_MAX];
    snprintf(configFile, sizeof(configFile), "%s" BAR "%s", vibesPath, CONFIGFILE);

    FILE *f = fopen(configFile, "r");

    cfg->defaultVolume = 128;
    cfg->showBar = 1;
    cfg->barMaxWidth = 50;
    cfg->defaultLoop = 0;
    cfg->playingMessage = 1;
    strncpy(cfg->barChar, "#", sizeof(cfg->barChar));
    strncpy(cfg->emptyChar, ".", sizeof(cfg->emptyChar));


    if (!f) return;

    char line[256];

    while (fgets(line, sizeof(line), f)) {
        char *trimmedLine = trim(line);

        if (trimmedLine[0] == '\0' || trimmedLine[0] == '#') {
            continue;
        }

        char *equal = strchr(line, '=');
        if (!equal) continue;

        *equal = '\0';
        char *key = trimmedLine;
        char *valuePart = equal + 1;
        
        while (isspace((unsigned char)*valuePart)) valuePart++;

        if (valuePart[0] == '#') {

            char *secondHash = strchr(valuePart + 1, '#');
            if (secondHash) *secondHash = '\0';
        } else {

            char *firstHash = strchr(valuePart, '#');
            if (firstHash) *firstHash = '\0';
        }

        trim(key);
        char *value = trim(valuePart);


        int found = 0;
        for (int i = 0; i < sizeOpt; i++) {

            if (strcmp(key, options[i].key) == 0) {
                options[i].handler(cfg, value);

                found = 1;
                break;
            }

        }

        if (!found) {
            printf("Warning: Unknown configuration key '%s'\n", key);
        }
        
    }
    fclose(f);
}

int gen(Config *cfg) {
    char *home = getUser();

    if (!home) {
        return 1;
    }

    char configPath[PATH_MAX];
    char vibesPath[PATH_MAX];

    snprintf(configPath, sizeof(configPath), "%s" BAR "%s", home, CONFIGDIR);
    snprintf(vibesPath, sizeof(vibesPath), "%s" BAR "%s", configPath, VIBESDIR);
    ensureDirExists(configPath);
    ensureDirExists(vibesPath);

    char configFile[PATH_MAX];
    snprintf(configFile, sizeof(configFile), "%s" BAR "%s", vibesPath, CONFIGFILE);

    FILE *f = fopen(configFile, "w");
    if (!f) { printf("Error to generate the config file"); return 1; }

    fprintf(f, "# Vibes config file\n\n\n");

    for (int i = 0; i < sizeOpt; i++) {
        fprintf(f, "%s=%s\n", options[i].key, options[i].default_value);
    }

    fclose(f);
    printf("Sucessfully generated config file in '%s'", configFile);

    return 0;
}