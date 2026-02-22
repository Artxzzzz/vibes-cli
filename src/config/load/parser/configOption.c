#include "parser.h"

const ConfigOption options[] = {
    {"default_volume",   parseVol},
    {"show_bar",         parseShowBar},
    {"default_loop",     parseLoop},
    {"playing_message",  parsePlayMsg},
    {"bar_char",         parseBarChar},
    {"empty_char",       parseEmptyChar},
    {"bar_max_width",    parseBarWidth}
};

const int sizeOpt = sizeof(options) / sizeof(options[0]);