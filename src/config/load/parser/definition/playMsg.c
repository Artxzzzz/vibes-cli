#include <string.h>

#include "../parser.h"

void parsePlayMsg(Config *cfg, const char *value) {
    cfg->playingMessage = (strcmp(value, "true") == 0);
}