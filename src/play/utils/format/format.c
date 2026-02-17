#include <limits.h>
#include <string.h>

#include "format.h"

char* getFileNameWithoutExt(const char* path) {
    const char* slash = strrchr(path, '/');
    if (!slash) slash = strrchr(path, '\\');
    const char* filename = slash ? slash + 1 : path;

    static char name[PATH_MAX];
    strncpy(name, filename, PATH_MAX);
    name[PATH_MAX-1] = '\0';

    char* dot = strrchr(name, '.');
    if (dot) *dot = '\0';

    return name;
}