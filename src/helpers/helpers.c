#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#include <shellapi.h>
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

#ifdef _WIN32
char* utf16ToUtf8(const wchar_t* utf16) {
    int len = WideCharToMultiByte(CP_UTF8, 0, utf16, -1, NULL, 0, NULL, NULL);
    char* utf8 = malloc(len);
    WideCharToMultiByte(CP_UTF8, 0, utf16, -1, utf8, len, NULL, NULL);
    return utf8;
}

void fixArgvWindows(int *argc, char ***argv) {
    LPWSTR *wargv = CommandLineToArgvW(GetCommandLineW(), argc);
    if (wargv) {
        *argv = malloc((*argc) * sizeof(char *));
        for (int i = 0; i < *argc; i++) {
            (*argv)[i] = utf16ToUtf8(wargv[i]);
        }
        LocalFree(wargv);
    }
}

#endif