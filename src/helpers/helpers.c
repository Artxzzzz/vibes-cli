#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "helpers.h"


char *getUser() {
    char *homeEnv = getenv("HOME");

    if (!homeEnv) homeEnv = getenv("USERPROFILE");

    if (!homeEnv) {printf("Error to get user path"); return NULL;}

    return homeEnv;
}

void msleep(float seconds) {
    #ifdef _WIN32
        Sleep((DWORD)(seconds * 1000));  
    #else
        usleep(seconds * 1000000);
    #endif
}