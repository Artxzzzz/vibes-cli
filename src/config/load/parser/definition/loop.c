#include <string.h>

#include "../parser.h"

void parseLoop(Config *cfg, const char *value) {
    cfg->defaultLoop = (strcmp(value, "true") == 0);
}