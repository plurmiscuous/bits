#ifndef _RANDOM_H_
#define _RANDOM_H_

#include "../inc/extint.h"
#include "../inc/N.h"

// init_rand() must be called before any of the randN() functions
void init_rand(void);

// Returns an unsigned N-bit random integer.
#define RAND_DECL(N) uint##N##_t rand##N(void);
TEMPLATE_STD(RAND_DECL)

#endif // _RANDOM_H_
