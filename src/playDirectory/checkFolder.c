#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#else
#include <limits.h>
#include <unistd.h>
#endif


char *checkFolder(char *path) {
    struct stat info;
    if (stat(path, &info) != 0 || !(info.st_mode & S_IFDIR)) {
        return NULL;
    }

    #ifdef _WIN32
        char *fullPath = _fullpath(NULL, path, _MAX_PATH);
    #else
        char *fullPath = realpath(path, NULL); 
    #endif

    return fullPath; 
}
