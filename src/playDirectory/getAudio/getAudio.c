#include <stdio.h>
#include <string.h>
#include <limits.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#endif

#include "utils/isAudio.h"

int getAudio(const char *folderPath, char files[][PATH_MAX], int maxFiles) {
    int count = 0;

#ifdef _WIN32
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;
    char searchPath[PATH_MAX];

    snprintf(searchPath, sizeof(searchPath), "%s\\*", folderPath);
    hFind = FindFirstFile(searchPath, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Erro ao abrir o diretório: %s\n", folderPath);
        return 0;
    }

    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            if (isAudioFile(findFileData.cFileName)) {
                strncpy(files[count], findFileData.cFileName, PATH_MAX-1);
                files[count][PATH_MAX-1] = '\0';
                count++;
                if (count >= maxFiles) break;
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);

#else
    DIR *d = opendir(folderPath);
    if (!d) {
        printf("Erro ao abrir o diretório: %s\n", folderPath);
        return 0;
    }

    struct dirent *dir;
    while ((dir = readdir(d)) != NULL) {
        if (dir->d_type == DT_REG && isAudioFile(dir->d_name)) {
            strncpy(files[count], dir->d_name, PATH_MAX-1);
            files[count][PATH_MAX-1] = '\0';
            count++;
            if (count >= maxFiles) break;
        }
    }

    closedir(d);
#endif

    return count;
}
