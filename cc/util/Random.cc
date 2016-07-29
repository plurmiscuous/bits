#include <cstdlib>
#include <ctime>

#include "random.hh"
#include "../inc/extint.hh"

// Customized PRNG. Based on modified Marsaglia xorshift generators.


static uint64_t state128plus[2];
static uint64_t state1024mod[16];

static uint64_t xs128plus();
static uint128_t xs1024mod();

Random::Random() {
    static bool rand_init;
    if (!rand_init) {
        srand(time(nullptr));

        // fill the state of the 128plus generator
        auto init = []() {
            return (static_cast<uint64_t>(::rand()) << 41) ^ (static_cast<uint64_t>(::rand()) << 23) ^ ::rand();
        };
        state128plus[0] = init();
        state128plus[1] = init();

        // throw away some 128plus output
        for (size_t i = 0x0; i < 0x4; ++i)
            while ((xs128plus() & 0x3) != i);

        // fill the state of the 1024mod generator using 128plus output
        for (uint8_t i = 0; i < 16; ++i)
            state1024mod[i] = xs128plus();

        // throw away some 1024mod output
        for (size_t i = 0x0; i < 0x8; ++i)
            while ((xs1024mod() & 0x7) != i);

        rand_init = true;
    }
}

template <typename T>
T Random::rand() {
    return static_cast<T>(xs1024mod());
}

static uint64_t xs128plus() {
    uint64_t s1 = state128plus[0];
    uint64_t s0 = state128plus[1];
    state128plus[0] = s0;
    s1 ^= s1 << 23;
    s1 ^= s1 >> 17;
    s0 ^= s0 >> 26;
    state128plus[1] = s0 ^ s1;
    return state128plus[1] + state128plus[0];
}

// NB: The modifications were made because 128-bit output from the standard
//     1024star function never had the highest 3 bits set. Setting the 65th bit
//     of the multiplicand and multiplier 'seems' to provide a decent
//     distribution of hex values for the highest half-octet. The modified
//     functions have not been evaluated using any standard tests.
static uint128_t xs1024mod() {
    static int p;
    uint64_t s0 = state1024mod[p];
    p = (p + 1) & 0xF;
    uint64_t s1 = state1024mod[p];
    s1 ^= s1 << 31;
    s1 ^= s1 >> 11;
    s0 ^= s0 >> 30;
    state1024mod[p] = s0 ^ s1;
    return U128(0x1, state1024mod[p]) * U128(0x1, 0x106689D45497FDB5);
}

#define RANDOM_RAND_TEMPLATE(T) template T Random::rand<T>();
TEMPLIFY(RANDOM_RAND_TEMPLATE)
