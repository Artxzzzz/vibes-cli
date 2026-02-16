#include <stdio.h>
#include <string.h>

#include "config/config.h"
#include "play/play.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Use: vibes <music>\n");
        return 1;
    }

    if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
        printf("Vibes %s\n", version);
        return 0;
    }

    return play(argv[1]);
}
