#include <stdint.h>
#include <stdlib.h>

#include "random.h"
#include "../inc/extint.h"
#include "../inc/template.h"

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
// implementation; w/o this bit, the highest 3 bits (usually 4 bits) of rand128
// are not set
static const uint128_t mult = u128(0x1, 0x106689D45497FDB5);

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
    // highest 4 bits of rand128's output
    return u128(0x1, state_1024star[p]) * mult;
}

#define RAND_IMPL(N)                                \
    uint##N##_t rand##N(void) {                     \
        return (uint##N##_t) xorshift1024star();    \
    }
TEMPLATE_STD(RAND_IMPL)

void init_rand(void) {
    state_64[0] = ((uint64_t) rand() << 41) ^ ((uint64_t) rand() << 23) ^ rand();
    state_64[1] = ((uint64_t) rand() << 41) ^ ((uint64_t) rand() << 23) ^ rand();

    for (size_t i = 0x0; i < 0x4; ++i)
        while ((xorshift128plus() & 0x3) != i);

    for (uint8_t i = 0; i < 16; ++i)
        state_1024star[i] = xorshift128plus();

    for (size_t i = 0x0; i < 0x4; ++i)
        while ((xorshift128plus() & 0x3) != i);
}
