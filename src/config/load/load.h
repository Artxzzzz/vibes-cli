#ifndef LOAD_H
#define LOAD_H

typedef struct {
    int defaultVolume;
    int showBar;
    int defaultLoop;
    int playingMessage;
    int activeHistory;

    int barMaxWidth;
    char barChar[8];
    char emptyChar[8];
} Config;

void loadConfig(Config *cfg);
int gen(Config *cfg);


#endif
