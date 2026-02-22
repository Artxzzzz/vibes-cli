#include <string.h>

#include "../parser.h"

void parseActiveHistory(Config *cfg, const char *value) {
    cfg->activeHistory = (strcmp(value, "true") == 0);
}