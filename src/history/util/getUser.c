#include <stdio.h>
#include <stdlib.h>

char *getUser() {
    char *homeEnv = getenv("HOME");

    if (!homeEnv) homeEnv = getenv("USERPROFILE");

    if (!homeEnv) {printf("Error to get user path"); return NULL;}

    return homeEnv;
}