#include <cstdlib>
#include <ctime>

#include "random.hh"
#include "../inc/extint.hh"

static bool rand_init;
static uint64_t state128plus_[2];
static uint64_t state1024mod_[16];

static uint64_t xs128plus();
static uint128_t xs1024mod();

Random::Random() {
    if (!rand_init) {
        srand(time(nullptr));

        auto init = []() {
            return (static_cast<uint64_t>(::rand()) << 41) ^ (static_cast<uint64_t>(::rand()) << 23) ^ ::rand();
        };
        state128plus_[0] = init();
        state128plus_[1] = init();

        for (size_t i = 0x0; i < 0x4; ++i)
            while ((xs128plus() & 0x3) != i);

        for (uint8_t i = 0; i < 16; ++i)
            state1024mod_[i] = xs128plus();

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
    uint64_t s1 = state128plus_[0];
    uint64_t s0 = state128plus_[1];
    state128plus_[0] = s0;
    s1 ^= s1 << 23;
    s1 ^= s1 >> 17;
    s0 ^= s0 >> 26;
    state128plus_[1] = s0 ^ s1;
    return state128plus_[1] + state128plus_[0];
}

static uint128_t xs1024mod() {
    static int p_;
    uint64_t s0 = state1024mod_[p_];
    p_ = (p_ + 1) & 0xF;
    uint64_t s1 = state1024mod_[p_];
    s1 ^= s1 << 31;
    s1 ^= s1 >> 11;
    s0 ^= s0 >> 30;
    state1024mod_[p_] = s0 ^ s1;
    // the 65th bit of the multiplicand is set, which is not in the original
    // implementation; this is to provide a higher variety of hex values in the
    // highest 4 bits of rand128()'s output
    return U128(0x1, state1024mod_[p_]) * U128(0x1, 0x106689D45497FDB5);
}

#define RANDOM_RAND_TEMPLATE(T) template T Random::rand<T>();
TEMPLIFY(RANDOM_RAND_TEMPLATE)
