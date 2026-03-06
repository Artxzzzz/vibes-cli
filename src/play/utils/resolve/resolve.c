#include "resolve.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <dirent.h>
    #include <strings.h>
#endif

#include <stdio.h>
#include <string.h>

int resolvePath(char *input, char *output) {
    #ifdef _WIN32
        wchar_t wInput[MAX_PATH];
        MultiByteToWideChar(CP_UTF8, 0, input, -1, wInput, MAX_PATH);

        WIN32_FIND_DATAW fd;
        HANDLE h;

        h = FindFirstFileW(wInput, &fd);

        if (h == INVALID_HANDLE_VALUE) {
            wchar_t wPattern[MAX_PATH];

            swprintf(wPattern, MAX_PATH, L"%ls.*", wInput);
            h = FindFirstFileW(wPattern, &fd);
        }

        if (h != INVALID_HANDLE_VALUE) {
            char *lastSlash = strrchr(input, '\\');
            if (!lastSlash) lastSlash = strrchr(input, '/');

            char fileNameUTF8[MAX_PATH];
            WideCharToMultiByte(CP_UTF8, 0, fd.cFileName, -1, fileNameUTF8, MAX_PATH, NULL, NULL);

            if (lastSlash) {
                size_t dirLen = (lastSlash - input) + 1;
                char dir[PATH_MAX];
                strncpy(dir, input, dirLen);
                dir[dirLen] = '\0';

                snprintf(output, PATH_MAX, "%s%s", dir, fileNameUTF8);

            } else {
                snprintf(output, PATH_MAX, "%s", fileNameUTF8);
            }

            FindClose(h);
            return 1;
        }

        return 0;

    #else
        FILE *f = fopen(input, "r");

        if (f) {
            fclose(f);
            snprintf(output, PATH_MAX, "%s", input);
            return 1;
        }


        DIR *dir = opendir(".");
        if (!dir) return 0;

        struct dirent *ent;
        size_t inputLen = strlen(input);

        while ((ent = readdir(dir)) != NULL) {

            if (strncasecmp(ent->d_name, input, inputLen) == 0 &&
                (ent->d_name[inputLen] == '.' || ent->d_name[inputLen] == '\0')) {

                snprintf(output, PATH_MAX, "%s", ent->d_name);
                closedir(dir);

                return 1;
            }
        }

        closedir(dir);
        return 0;

    #endif
}
