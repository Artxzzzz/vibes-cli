#include <stdlib.h>

#include "../parser.h"

void parseBarWidth(Config *cfg, const char *value) {
    cfg->barMaxWidth = atoi(value);
}