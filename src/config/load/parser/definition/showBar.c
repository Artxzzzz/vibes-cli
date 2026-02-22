#include <string.h>

#include "../parser.h"

void parseShowBar(Config *cfg, const char *value) {
    cfg->showBar = strcmp(value, "true") == 0;
}