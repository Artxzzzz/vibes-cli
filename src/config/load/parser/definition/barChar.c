#include <string.h>
#include <stdio.h>

#include "../parser.h"

void parseBarChar(Config *cfg, const char *value) {
    if (value == NULL || value[0] == '\0') printf("\nConfig Error: bar_char is empty.\nRunning with default.\n");

    if (value[0] != '\0') {
        strncpy(cfg->barChar, value, sizeof(cfg->barChar) - 1);
    }
}