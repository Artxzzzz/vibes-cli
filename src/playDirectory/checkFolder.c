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

#include "../helpers/helpers.h"

char *checkFolder(char *path) {
    #ifdef _WIN32
        wchar_t wPath[PATH_MAX];
        MultiByteToWideChar(CP_UTF8, 0, path, -1, wPath, PATH_MAX);

        struct _stat64i32 info;
        if (_wstat(wPath, &info) != 0 || !(info.st_mode & S_IFDIR)) {
            return NULL;
        }

        wchar_t *wFullPath = _wfullpath(NULL, wPath, _MAX_PATH);
        if (!wFullPath) return NULL;

        char *fullPath = utf16ToUtf8(wFullPath);
        free(wFullPath);
        return fullPath;
    #else
        struct stat info;
        char *fullPath = realpath(path, NULL); 
    #endif

    return fullPath; 
}
