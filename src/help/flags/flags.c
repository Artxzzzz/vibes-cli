#include "flags.h"

Flag flags[] = {
    {"v", "version", "Show program version"},
    {"l", "loop", "Loop playback"},
    {"s", "sleep", "Disable delay between tracks"},
    {"h", "help", "Show this help message"}
};

const int totalFlags = sizeof(flags) / sizeof(flags[0]);