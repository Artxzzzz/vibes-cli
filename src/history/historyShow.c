#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "history.h"

void showHistory(const char *val) {
    historyInit();
    int linesShow = 0;
    
    FILE *f = fopen(historyPath, "r");
    if (!f) return;

    char *content[100];
    char buffer[256];
    int count = 0;

    while (fgets(buffer, sizeof(buffer), f)) {
        buffer[strcspn(buffer, "\n")] = 0;

        content[count] = malloc(strlen(buffer) + 1);
        strcpy(content[count], buffer);

        count++;
    }

    fclose(f);

    if (val) {
        linesShow = atoi(val);

        if (linesShow <= 0 || linesShow > count) {
            printf("Invalid history line. Must be a number (0-%d).\n", count);
            printf("Showing all...\n");

            linesShow = count;
        }

        count = linesShow;
    }

    for (int line = 0; line < count; line++) {
        printf("%s\n", content[line]);
        free(content[line]);
    }
}