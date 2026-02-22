#include <string.h>
#include <stdio.h>

#include "../parser.h"

void parseEmptyChar(Config *cfg, const char *value) {
    if (value == NULL || value[0] == '\0') printf("\nConfig Error: empty_char is empty.\nRunning with default.\n");

    if (value[0] != '\0') {
        strncpy(cfg->emptyChar, value, sizeof(cfg->emptyChar) - 1);
    }
}