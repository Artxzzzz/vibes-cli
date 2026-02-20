#include <stdio.h>
#include "history.h"

void historyAdd(const char *musicPath) {
    if (!historyOk) return;

    FILE *f = fopen(historyPath, "a");
    if (!f) return;

    if (fprintf(f, "%s\n", musicPath) < 0) {
        perror("Failed to write to history");
    }

    fclose(f);
}