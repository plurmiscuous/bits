#ifndef RANDOM_H
#define RANDOM_H

#include "../inc/extint.h"
#include "../inc/N.h"

// init_rand() must be called before any of the randN() functions
void init_rand(void);

// Returns an unsigned N-bit random integer.
#define RAND_DECL(N) uint##N##_t rand##N(void);
TEMPLATE_STD(RAND_DECL)

#endif // RANDOM_H
