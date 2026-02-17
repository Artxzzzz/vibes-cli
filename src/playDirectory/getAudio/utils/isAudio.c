#include <string.h>

#include "isAudio.h"

int isAudioFile(char *filename) {
    const char *ext = strrchr(filename, '.');
    if (!ext) return 0;
    return strcmp(ext, ".mp3") == 0 ||
           strcmp(ext, ".wav") == 0 ||
           strcmp(ext, ".ogg") == 0 ||
           strcmp(ext, ".opus") == 0 || 
           strcmp(ext, ".flac") == 0 ||
           strcmp(ext, ".mid") == 0 ||
           strcmp(ext, ".aiff") == 0;
}
