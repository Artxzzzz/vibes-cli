#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../parser.h"

void parseVol(Config *cfg, const char *value) {
    int percent = atoi(value);

    if (percent >= 0 && percent <= 100) {
        int vol = (percent * 128) / 100;
        cfg->defaultVolume = vol;

        return;
    }
    
    printf("Config Error: Invalid Volume '%d'. Use (0-100)\n", percent);
}