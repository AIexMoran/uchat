#include "server.h"

long long mx_get_time() {
    struct timeval time;
    long long milisec;

    gettimeofday(&time, 0);
    milisec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return milisec;
}
