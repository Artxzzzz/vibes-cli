#include <stdio.h>

#include "help.h"
#include "flags/flags.h"

static void line(int size) {
    for (int length = 0; length < size; length++) {
        printf("-");
    }
}

#define bold "\x1b[1m"
#define unbold "\x1b[0m"
#define barWidth 31

void help() {
    printf("Usage: vibes <music | directory> [options]\n\n");
    
    line(barWidth);

    printf("\n%sOptions:%s\n", bold, unbold);

    for (int flag = 0; flag < totalFlags; flag++) {
        if (flags[flag].shortOpt[0] == '\0') {
            printf("  --%s%-19s%s %s\n",
                bold,
                flags[flag].longOpt,
                unbold,
                flags[flag].description
            );
        } else {
            printf("  -%s%s%s, --%s%-15s%s %s\n",
            bold,
            flags[flag].shortOpt,
            unbold,
            bold,
            flags[flag].longOpt,
            unbold,
            flags[flag].description);
        }
    }

    line(barWidth);

    printf("\n%sControls during playback:%s\n", bold, unbold);

    printf("  %s%-22s%sPause/Resume\n", bold, "Space", unbold);
    printf("  %s%-22s%sQuit\n", bold, "Q", unbold);
    printf("  %s%-22s%sVolume / Seek\n", bold, "Arrows", unbold);
}