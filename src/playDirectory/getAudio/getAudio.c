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
#include "../../helpers/helpers.h"

int getAudio(const char *folderPath, char files[][PATH_MAX], int maxFiles) {
    int count = 0;
#ifdef _WIN32
    WIN32_FIND_DATAW findFileData;
    HANDLE hFind;
    wchar_t wSearchPath[PATH_MAX];

    wchar_t wFolderPath[PATH_MAX];
    MultiByteToWideChar(CP_UTF8, 0, folderPath, -1, wFolderPath, PATH_MAX);
    
    swprintf(wSearchPath, PATH_MAX, L"%ls\\*", wFolderPath);

    hFind = FindFirstFileW(wSearchPath, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Error to open the directory: %s\n", folderPath);
        return 0;
    }

    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            char fileNameUTF8[PATH_MAX];
            WideCharToMultiByte(CP_UTF8, 0, findFileData.cFileName, -1, fileNameUTF8, PATH_MAX, NULL, NULL);

            if (isAudioFile(fileNameUTF8)) {
                strncpy(files[count], fileNameUTF8, PATH_MAX-1);
                files[count][PATH_MAX-1] = '\0';
                count++;
                if (count >= maxFiles) break;
            }
        }
    } while (FindNextFileW(hFind, &findFileData) != 0);

    FindClose(hFind);
#else
    DIR *d = opendir(folderPath);
    if (!d) {
        printf("Error to open the directory: %s\n", folderPath);
        return 0;
    }

    struct dirent *dir;
    while ((dir = readdir(d)) != NULL) {
        struct stat st;
        char full[PATH_MAX];

        snprintf(full, sizeof(full), "%s/%s", folderPath, dir->d_name);

        if (stat(full, &st) == 0 &&
            S_ISREG(st.st_mode) &&
            isAudioFile(dir->d_name)) {

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
