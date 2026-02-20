#include <string.h>
#include <stdio.h>

int isarg(const char *arg, const char *shortOpt, const char *longOpt, const char **value) {
    if (shortOpt) {
        char buf[3];
        buf[0] = '-';
        buf[1] = shortOpt[0];
        buf[2] = '\0';

        if (strncmp(arg, buf, 2) == 0) {
            if (arg[2] == '=') {
                *value = arg + 3;
            } else {
                *value = NULL;
            }

            return 1;
        }
    }

    if (longOpt) {
        char buf[256];
        snprintf(buf, sizeof(buf), "--%s", longOpt);
        size_t len = strlen(buf);

        if (strncmp(arg, buf, len) == 0) {
            if (arg[2] == '=') {
                *value = arg + len + 1;
            } else {
                *value = NULL;
            }
            
            return 1;
        }
    }

    return 0;
}
