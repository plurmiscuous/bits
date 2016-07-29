#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "random.h"
#include "../inc/extint.h"
#include "../inc/N.h"

// Customized PRNG. Based on modified Marsaglia xorshift generators.
//
// NB: The modifications were made because 128-bit output from the standard
//     1024star function never had the highest 3 bits set. Setting the 65th bit
//     of the state and multiplier 'seems' to provide a decent distribution of
//     hex values for the highest half-octet. The modified functions have not
//     been evaluated using any standard tests.

static uint64_t state_64[2];

static uint64_t xorshift128plus(void) {
    uint64_t s1 = state_64[0];
    uint64_t s0 = state_64[1];
    state_64[0] = s0;
    s1 ^= s1 << 23;
    s1 ^= s1 >> 17;
    s0 ^= s0 >> 26;
    state_64[1] = s0 ^ s1;
    return state_64[1] + state_64[0];
}

static uint64_t state_1024star[16];
static int p;

// the 65th bit of the multiplier is set, which is not in the original
// implementation; w/o this bit, the highest 3 bits (usually 4 bits) of
// rand128() are not set
static const uint128_t mult = U128(0x1, 0x106689D45497FDB5);

static uint128_t xorshift1024star(void) {
    uint64_t s0 = state_1024star[p];
    p = (p + 1) & 0xF;
    uint64_t s1 = state_1024star[p];
    s1 ^= s1 << 31;
    s1 ^= s1 >> 11;
    s0 ^= s0 >> 30;
    state_1024star[p] = s0 ^ s1;
    // the 65th bit of the multiplicand is set, which is not in the original
    // implementation; this is to provide a higher variety of hex values in the
    // highest 4 bits of rand128()'s output
    return U128(0x1, state_1024star[p]) * mult;
}

#define RAND_IMPL(N)                                \
    uint##N##_t rand##N(void) {                     \
        return (uint##N##_t) xorshift1024star();    \
    }
TEMPLATE_STD(RAND_IMPL)

void init_rand(void) {
    srand(time(NULL));

    // fill the state of the 128plus generator
    state_64[0] = ((uint64_t) rand() << 41) ^ ((uint64_t) rand() << 23) ^ rand();
    state_64[1] = ((uint64_t) rand() << 41) ^ ((uint64_t) rand() << 23) ^ rand();

    // throw away some 128plus output
    for (size_t i = 0x0; i < 0x4; ++i)
        while ((xorshift128plus() & 0x3) != i);

    // fill the state of the 1024plus generator using 128plus output
    for (uint8_t i = 0; i < 16; ++i)
        state_1024star[i] = xorshift128plus();

    // throw away some 1024plus output
    for (size_t i = 0x0; i < 0x4; ++i)
        while ((xorshift1024star() & 0x3) != i);
}
