#include "flags.h"

Flag flags[] = {
    {"v", "version", "Show program version"},
    {"l", "loop", "Loop playback"},
    {"s", "sleep", "Disable delay between tracks"},
    {"h", "help", "Show this help message"},
    {"H", "history", "Show all musics played (Max limit: 100)"},
    {"V", "volume", "Set the playback volume. Use: --volume=<value> (e.g., --volume=4)"},
    {"", "no-save", "Dont save actual music"}
};

const int totalFlags = sizeof(flags) / sizeof(flags[0]);