#ifndef HISTORY_H
#define HISTORY_H

#include <limits.h>

extern char historyPath[PATH_MAX];
extern int historyOk;

void historyInit();
void historyAdd(const char *musicPath);
void showHistory(const char *val);

#endif
