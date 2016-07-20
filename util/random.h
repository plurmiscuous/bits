#ifndef _RANDOM_H_
#define _RANDOM_H_

#include "../inc/extint.h"
#include "../inc/N.h"

void init_rand(void);

#define RAND_DECL(N) uint##N##_t rand##N(void);
TEMPLATE_STD(RAND_DECL)

#endif // _RANDOM_H_
