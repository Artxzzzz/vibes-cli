#include <limits.h>
#include <string.h>

#include "format.h"

void getFileNameWithoutExt(const char* path, char* out) {
    const char* slash = strrchr(path, '/');
    if (!slash) slash = strrchr(path, '\\');
    const char* filename = slash ? slash + 1 : path;

    strncpy(out, filename, PATH_MAX-1);
    out[PATH_MAX-1] = '\0';

    char* dot = strrchr(out, '.');
    if (dot) *dot = '\0';
}
