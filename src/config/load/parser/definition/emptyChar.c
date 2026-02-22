#include <string.h>
#include <stdio.h>

#include "../parser.h"

void parseEmptyChar(Config *cfg, const char *value) {
    if (value == NULL || value[0] == '\0') {printf("\nConfig Error: empty_char is empty.\nRunning with default.\n"); return; }

    size_t len = 1;
    unsigned char c = (unsigned char)value[0];

    if ((c & 0x80) == 0x00) len = 1;
    else if ((c & 0xE0) == 0xC0) len = 2;
    else if ((c & 0xF0) == 0xE0) len = 3;
    else if ((c & 0xF8) == 0xF0) len = 4;
    else {
        printf("\nConfig Error: invalid UTF-8.\n");
        return;
    }

    if (len >= sizeof(cfg->emptyChar))
        len = sizeof(cfg->emptyChar) - 1;

    memcpy(cfg->emptyChar, value, len);
    cfg->emptyChar[len] = '\0';
}