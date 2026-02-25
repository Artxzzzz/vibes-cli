#include "parser.h"

const ConfigOption options[] = {
    {"default_volume",   parseVol, "100"},
    {"show_bar",         parseShowBar, "true"},
    {"default_loop",     parseLoop, "false"},
    {"playing_message",  parsePlayMsg, "true"},
    {"bar_char",         parseBarChar, "#"},
    {"empty_char",       parseEmptyChar, "."},
    {"bar_max_width",    parseBarWidth, "50"},
    {"active_history",   parseActiveHistory, "true"},
    {"empty_char_color", parseEmptyCharColor, "white"},
    {"bar_char_color",   parseFullCharColor, "white"}
};

const int sizeOpt = sizeof(options) / sizeof(options[0]);