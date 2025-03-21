#include "sleep.h"

void ms_sleep(int ms) {
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = ms * 1000;

    select(0, NULL, NULL, NULL, &tv);
}