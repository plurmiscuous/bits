#ifndef _TIMER_H_
#define _TIMER_H_

#include <time.h>

typedef struct timespec timer_t;

timer_t timer_start(void);

long timer_end(timer_t start);

long timer_diff(timer_t start, timer_t end);

long time_ns(void);
long time_us(void);
long time_ms(void);
long time_sec(void);

#endif // _TIMER_H_
