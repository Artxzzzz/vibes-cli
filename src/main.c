#include <stdio.h>

#include "play/play.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Use: vibes <music>\n");
        return 1;
    }

    return play(argv[1]);
}
