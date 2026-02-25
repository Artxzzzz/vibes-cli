#ifndef PARSER_H
#define PARSER_H

#include "../load.h"

// Bool
void parseShowBar(Config *cfg, const char *value);
void parseLoop(Config *cfg, const char *value);
void parseActiveHistory(Config *cfg, const char *value);
void parsePlayMsg(Config *cfg, const char *value);


// Char
void parseBarChar(Config *cfg, const char *value);
void parseEmptyChar(Config *cfg, const char *value);


// String
void parseEmptyCharColor(Config *cfg, const char *value);
void parseFullCharColor(Config *cfg, const char *value);


// Int
void parseVol(Config *cfg, const char *value);
void parseBarWidth(Config *cfg, const char *value);

typedef struct {
    const char *key;
    void (*handler)(Config *cfg, const char *value);
    
    const char *default_value;
} ConfigOption;

extern const ConfigOption options[];
extern const int sizeOpt;

#endif
