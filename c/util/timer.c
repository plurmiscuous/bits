#include <time.h>
#include <sys/time.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

#include "timer.h"

struct timespec timespec(void) {
    struct timespec ts;

#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    ts.tv_sec = mts.tv_sec;
    ts.tv_nsec = mts.tv_nsec;
#else
    clock_gettime(CLOCK_REALTIME, &ts);
#endif

    return ts;
}

struct timespec timer_start(void) {
    struct timespec start = timespec();
    return start;
}

long timer_end(struct timespec start) {
    struct timespec end = timespec();
    long diff = (end.tv_sec - start.tv_sec) * 1e9 + end.tv_nsec - start.tv_nsec;
    return diff;
}

long timer_diff(struct timespec start, struct timespec end) {
    long diff = (end.tv_sec - start.tv_sec) * 1e9 + end.tv_nsec - start.tv_nsec;
    return diff;
}

long time_ns(void) {
    struct timespec ts = timespec();
    return ts.tv_sec * 1e9 + ts.tv_nsec;
}

long time_us(void) {
    struct timespec ts = timespec();
    return ts.tv_sec * 1e6 + ts.tv_nsec / 1e3;
}

long time_ms(void) {
    struct timespec ts = timespec();
    return ts.tv_sec * 1e3 + ts.tv_nsec / 1e6;
}

long time_sec(void) {
    struct timespec ts = timespec();
    return ts.tv_sec;
}
