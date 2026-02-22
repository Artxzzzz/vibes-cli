#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "history.h"

void showHistory(const char *val) {
    historyInit();
    
    FILE *f = fopen(historyPath, "r");
    if (!f) return;

    char **content = NULL;
    char buffer[1024];
    int count = 0;
    int cap = 15;

    content = malloc(sizeof(char*) * cap);
    if (!content) {
        fclose(f);
        return;
    }

    while (fgets(buffer, sizeof(buffer), f)) {
        buffer[strcspn(buffer, "\n")] = 0;

        if (count >= cap) {
            cap *= 2;
            char **temp = realloc(content, sizeof(char*) * cap);
            if (!temp) {
                fprintf(stderr, "Memory error to load the history\n");
                break; 
            }
            content = temp;
        }

        content[count] = malloc(strlen(buffer) + 1);
        
        if (content[count]) {
            strcpy(content[count], buffer);
            count++;
        }
    }

    fclose(f);

    int linesShow = count;
    if (val) {
        int request = atoi(val);
        if (request > 0 && request <= count) {
            linesShow = request;
        } else if (request > count) {
            printf("Warning: The historic only have %d enters.\n", count);
        } else {
            printf("Invalid lines number, showing all...\n");
        }
    }

    int startAt = count - linesShow;

    for (int i = 0; i < count; i++) {
        if (i >= startAt) {
            printf("%s\n", content[i]);
        }
        free(content[i]);
    }

    free(content);
}