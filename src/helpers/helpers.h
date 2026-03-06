#ifndef HELPERS_H
#define HELPERS_H

#include <stddef.h>

char *getUser();
void msleep(float seconds);

#ifdef _WIN32
char* utf16ToUtf8(const wchar_t* utf16);
void fixArgvWindows(int *argc, char ***argv);
#endif

#endif
