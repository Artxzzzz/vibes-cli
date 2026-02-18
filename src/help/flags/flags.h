#ifndef FLAGS_H
#define FLAGS_H

typedef struct {
    const char *shortOpt; // short options (e.g., -v, -h)
    const char *longOpt;  // long options (e.g., --version, --help)

    const char *description; // description of flag
} Flag;

extern Flag flags[];

extern const int totalFlags;

#endif
