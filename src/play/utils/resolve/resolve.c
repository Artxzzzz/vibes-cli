#include "../playInc.h"

int resolvePath(char *input, char *output) {
    #ifdef _WIN32
        if (GetFileAttributes(input) != INVALID_FILE_ATTRIBUTES) {
            strcpy(output, input);
            return 1;
        }

        WIN32_FIND_DATA fd;
        HANDLE h;
        char pattern[MAX_PATH];

        snprintf(pattern, sizeof(pattern), "%s.*", input);
        h = FindFirstFile(pattern, &fd);

        if (h != INVALID_HANDLE_VALUE) {
            strcpy(output, fd.cFileName);
            FindClose(h);
            return 1;
        }

        return 0;

    #else
        FILE *f = fopen(input, "r");
        if (f) {
            fclose(f);
            strcpy(output, input);
            return 1;
        }

        DIR *dir = opendir(".");
        struct dirent *ent;

        while ((ent = readdir(dir)) != NULL) {
            if (strncmp(ent->d_name, input, strlen(input)) == 0 &&
                ent->d_name[strlen(input)] == '.') {
                strcpy(output, ent->d_name);
                closedir(dir);
                return 1;
            }
        }

        closedir(dir);
        return 0;

    #endif
}
