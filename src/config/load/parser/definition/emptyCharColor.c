#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "../parser.h"

void parseEmptyCharColor(Config *cfg, const char *value) {
    if (value == NULL || value[0] == '\0') {
        printf("\nConfig Error: empty_char_color is empty.\nRunning with default.\n");
        return;
    }

    char temp[16];
    strncpy(temp, value, sizeof(temp) - 1);
    temp[sizeof(temp) - 1] = '\0';

    for (int i = 0; temp[i]; i++) {
        temp[i] = tolower((unsigned char)temp[i]);
    }

    strncpy(cfg->emptyCharColor, temp, sizeof(cfg->emptyCharColor) - 1);
}