#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "../parser.h"

void parseFullCharColor(Config *cfg, const char *value) {
    if (value == NULL || value[0] == '\0') {
        printf("\nConfig Error: bar_char_color is empty.\nRunning with default.\n");
        return;
    }

    char temp[8];
    strncpy(temp, value, sizeof(temp) - 1);
    temp[sizeof(temp) - 1] = '\0';

    for (int i = 0; temp[i]; i++) {
        temp[i] = tolower((unsigned char)temp[i]);
    }

    strncpy(cfg->fullCharColor, temp, sizeof(cfg->fullCharColor) - 1);
}