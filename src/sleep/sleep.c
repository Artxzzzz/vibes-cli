#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "sleep.h"

#ifdef _WIN32
    void msleep(float seconds) {
        Sleep((DWORD)(seconds * 1000));
    }
            
#else
    void msleep(float seconds) {
        usleep(seconds * 1000000);
    }
#endif