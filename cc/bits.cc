#include <cstdint>
#include <cstddef>

#include "bits.hh"
#include "inc/extint.hh"

// The ASSERT macro turns on run-time assertions for function arguments, such as
// asserting that shift amounts are non-negative and within the width of data
// type being operated on.
#define ASSERT 1

#if ASSERT
    #include <cassert>
#else
    #define assert(x) ((void)(0))  // no side-effects
#endif

///////////////////////////////
////    IMPLEMENTATIONS    ////
///////////////////////////////

// POPULATION
template <typename T>
int pop(T bits) {
    for (int i = 0; i < LOG<T>(); ++i)
        bits = (bits & WORD<T>(i)) + ((bits >> (1 << i)) & WORD<T>(i));

    return static_cast<int>(bits);
}

// PARITY
template <typename T>
int par(T bits) {
    for (int i = BITS<T>(); i >>= 1;)
        bits ^= bits >> i;

    return static_cast<int>(bits & 0x1);
}

// COUNT TRAILING ZEROS
template <typename T>
int ctz(T bits) {
    int n = 1;
    T mask = ALL<T>();

    for (int i = BITS<T>() >> 1; i > 1; i >>= 1) {
        mask >>= i;
        if ((bits & mask) == 0) {
            n += i;
            bits >>= i;
        }
    }

    return static_cast<int>((-(bits == 0) & BITS<T>()) | (-(bits != 0) & (n - (bits & 1))));
}

// COUNT LEADING ZEROS
template <typename T>
int clz(T bits) {
    int n = 0;
    T mask = ALL<T>() >> (BITS<T>() >> 1);

    for (int i = BITS<T>(); i >>= 1;) {
        if (bits <= mask) {
            n += i;
            bits <<= i;
        }
        mask |= mask << (i >> 1);
    }

    return static_cast<int>((-(bits == 0) & BITS<T>()) | (-(bits != 0) & n));
}

// LONGEST CHAIN OF SET BITS
template <typename T>
int mxset(T bits) {
    int k;
    for (k = 0; bits; ++k)
        bits &= (bits >> 1);

    return k;
}

// SHORTEST CHAIN OF SET BITS
template <typename T>
int mnset(T bits) {
    T dn = bits & ~(bits >> 1);
    T up = bits & ~(bits << 1);

    int k;
    for (k = 1; bits && (dn & up) == 0; ++k)
        up <<= 1;

    return k - static_cast<int>(!bits);
}

// MAXIMUM
template <typename T>
T max(T x, T y) {
    return x ^ ((x ^ y) & -(x < y));
}

// MINIMUM
template <typename T>
T min(T x, T y) {
    return y ^ ((x ^ y) & -(x < y));
}

// GREATEST COMMON DIVISOR
template <typename T>
T gcd(T x, T y) {
    while (y != 0) {
        y ^= x %= y;
        y ^= x ^= y;
    }
    return x;
}

// BINARY LOGARITHM
template <typename T>
T lb(T bits) {
    T m = ALL<T>();
    T log = 0;

    for (int i = LOG<T>(); i--;) {
        m >>= (1 << i);
        T shift = (bits > m) << i;
        bits >>= shift;
        log |= shift;
    }

    return log;
}

// IS POWER OF 2
template <typename T>
int ipow(T bits) {
    return bits && (bits & (bits - 1)) == 0;
}

// CEIL POWER OF 2
template <typename T>
T cpow(T bits) {
    bits += bits == 0;
    --bits;
    for (int i = BITS<T>(); (i >>= 1) != 0;)
        bits |= bits >> i;
    ++bits;
    return bits;
}

// FLOOR POWER OF 2
template <typename T>
T fpow(T bits) {
    for (int i = BITS<T>(); (i >>= 1) != 0;)
        bits |= bits >> i;
    return bits - (bits >> 1);
}

// ISOLATE LEAST SIGNIFICANT SET BIT
template <typename T>
T lsb(T bits) {
    return bits & -bits;
}

// ISOLATE MOST SIGNIFICANT SET BIT
template <typename T>
T msb(T bits) {
    for (int i = BITS<T>(); (i >>= 1) != 0;)
        bits |= bits >> i;
    return (bits >> 1) + (bits != 0);
}

////////////////////////////
////    PERMUTATIONS    ////
////////////////////////////

// ROTATE LEFT
template <typename T>
T rol(T bits, int rot) {
    assert(0 <= rot && rot < BITS<T>());
    return (bits << rot) | (bits >> (BITS<T>() - rot));
}

// ROTATE RIGHT
template <typename T>
T ror(T bits, int rot) {
    assert(0 <= rot && rot < BITS<T>());
    return (bits << (BITS<T>() - rot)) | (bits >> rot);
}

// DELTA SWAP
template <typename T>
T delta(T bits, T mask, int del) {
    assert(0 <= del && del < BITS<T>());
    T tmp = (bits ^ (bits >> del)) & mask;
    bits ^= tmp ^ (tmp << del);
    return bits;
}

// SWAPPING INDIVIDUAL BITS
template <typename T>
T bswap(T bits, int i, int j) {
    assert(0 <= i && i < BITS<T>());
    assert(0 <= j && j < BITS<T>());
    T tmp = ((bits >> i) ^ (bits >> j)) & 1;
    return bits ^ ((tmp << i) | (tmp << j));
}

// SWAPPING BIT RANGES
template <typename T>
T rswap(T bits, int i, int j, int len) {
    assert(0 <= len && len <= BITS<T>());
    assert(0 <= i && i < BITS<T>() && i + len <= BITS<T>());
    assert(0 <= j && j < BITS<T>() && j + len <= BITS<T>());
    assert(i + len < j || i < j + len);
    T tmp = ((bits >> i) ^ (bits >> j)) & ((ONE<T>() << len) - 1);
    return bits ^ ((tmp << i) | (tmp << j));
}

// REVERSE
template <typename T>
T rev(T bits) {
    for (int i = 0; i < LOG<T>(); ++i)
        bits = (bits & WORD<T>(i)) << (1 << i) | (bits & ~WORD<T>(i)) >> (1 << i);
    return bits;
}

// PERFECT OUTER-SHUFFLE
template <typename T>
T shuf(T bits) {
    for (int i = LOG<T>() - 1; i--;)
        bits = delta<T>(bits, SHUF<T>(i), 1 << i);
    return bits;
}

// PERFECT OUTER-UNSHUFFLE
template <typename T>
T ishuf(T bits) {
    for (int i = 0; i < LOG<T>() - 1; ++i)
        bits = delta<T>(bits, SHUF<T>(i), 1 << i);
    return bits;
}

// OMFLIP
template <typename T>
T omflip(T bits, T mask, uint8_t opts) {
    for (int i = 0; i < 2; ++i) {
        T m = (mask >> (i * (BITS<T>() >> 1))) & WORD<T>(LOG<T>() - 1);
        if (((opts >> i) & 0x1) == 0) {
            bits = delta<T>(bits, m, BITS<T>() >> 1);
            bits = shuf<T>(bits);
        } else {
            bits = ishuf<T>(bits);
            bits = delta<T>(bits, m, BITS<T>() >> 1);
        }
    }
    return bits;
}

// BUTTERFLY NETWORK
template <typename T>
T bfly(T bits, T mask) {
    for (int i = LOG<T>(); i--;)
        bits = delta<T>(bits, mask & WORD<T>(i), 1 << i);
    return bits;
}

// INVERSE-BUTTERFLY NETWORK
template <typename T>
T ibfly(T bits, T mask) {
    for (int i = 0; i < LOG<T>(); ++i)
        bits = delta<T>(bits, mask & WORD<T>(i), 1 << i);
    return bits;
}

// MATRIX TRANSPOSE
template <typename T>
T trans(T bits, int rows) {
    assert(((BITS<T>() / rows) * rows) == BITS<T>());
    int c = LOG<T>() - lb<T>(rows);
    int g = gcd<T>(LOG<T>(), c);
    int d = LOG<T>() / g - 1;

    for (int i = 0; i < g; ++i) {
        for (int j = 0, k = i, n = i + c; j < d; ++j, k = n, n += c) {
            if (n >= LOG<T>())
                n -= LOG<T>();
            if (n != k) {
                int mx = max<T>(n, k);
                int mn = k ^ n ^ mx;
                int sh = (1 << mx) - (1 << mn);
                bits = delta<T>(bits, WORD<T>(mx) & ~WORD<T>(mn), sh);
            }
        }
    }
    return bits;
}

/////////////////////////////
////    MANIPULATIONS    ////
/////////////////////////////

// // LFSR WITH MAXIMAL-LENGTH SEQUENCE
// template <typename T>
// T lfsr(T bits) {
//     bits = (bits >> 1) ^ ((-(bits & 0x1)) & FTAPS##N);
//     return bits;
// }

// // INVERSE LFSR WITH MAXIMAL-LENGTH SEQUENCE
// template <typename T>
// T ilfsr(T bits) {
//     bits = (bits << 1) ^ (-(bits >> (BITS<T>() - 1)) & RTAPS##N);
//     return bits;
// }

// BITWISE TERNARY
template <typename T>
T tern(T xbits, T ybits, T mask) {
    return (mask & (xbits ^ ybits)) ^ ybits;
}

// BINARY TO GRAY CODE
template <typename T>
T gray(T bits) {
    return bits ^ (bits >> 1);
}

// GRAY TO BINARY CODE
template <typename T>
T igray(T bits) {
    for (int i = 1; i < BITS<T>(); i <<= 1)
        bits ^= bits >> i;
    return bits;
}

// EXTRACT LEFT
template <typename T>
T extl(T bits, T mask) {
    bits &= mask;
    T m1 = T(~mask) >> 1;

    for (int i = 0; i < LOG<T>(); ++i) {
        T m = m1;
        for (int j = 1; j < BITS<T>(); j <<= 1)
            m ^= (m >> j);

        T mv = m & mask;
        mask = (mask ^ mv) | (mv << (ONE<T>() << i));

        T mt = bits & mv;
        bits = (bits ^ mt) | (mt << (ONE<T>() << i));
        m1 &= ~m;
    }

    return bits;
}

// EXTRACT RIGHT
template <typename T>
T extr(T bits, T mask) {
    bits &= mask;
    T m1 = ~mask << 1;

    for (int i = 0; i < LOG<T>(); ++i) {
        T m = m1;
        for (int j = 1; j < BITS<T>(); j <<= 1)
            m ^= (m << j);

        T mv = m & mask;
        mask = (mask ^ mv) | (mv >> (ONE<T>() << i));

        T mt = bits & mv;
        bits = (bits ^ mt) | (mt >> (ONE<T>() << i));
        m1 &= ~m;
    }

    return bits;
}

// DEPOSIT LEFT
template <typename T>
T depl(T bits, T mask) {
    T masks[LOG<T>()];
    T m0 = mask;
    T m1 = ~mask << 1;

    for (int i = 0; i < LOG<T>(); ++i) {
        T m = m1;
        for (int j = 1; j < BITS<T>(); j <<= 1)
            m ^= (m << j);

        masks[i] = m & mask;
        mask = (mask ^ masks[i]) | (masks[i] >> (ONE<T>() << i));
        m1 &= ~m;
    }

    for (int i = LOG<T>(); i--;)
        bits ^= ((bits ^ (bits << (ONE<T>() << i))) & masks[i]);

    return bits & m0;
}

// DEPOSIT RIGHT
template <typename T>
T depr(T bits, T mask) {
    T masks[LOG<T>()];
    T m0 = mask;
    T m1 = T(~mask) >> 1;

    for (int i = 0; i < LOG<T>(); ++i) {
        T m = m1;
        for (int j = 1; j < BITS<T>(); j <<= 1)
            m ^= (m >> j);

        masks[i] = m & mask;
        mask = (mask ^ masks[i]) | (masks[i] << (ONE<T>() << i));
        m1 &= ~m;
    }

    for (int i = LOG<T>(); i--;)
        bits ^= (bits ^ (bits >> (ONE<T>() << i))) & masks[i];

    return bits & m0;
}

// GROUP
template <typename T>
T grp(T bits, T mask) {
    return extr<T>(bits, mask) | extl<T>(bits, ~mask);
}

// UNGROUP
template <typename T>
T igrp(T bits, T mask) {
    return depr<T>(bits, ~mask) | depl<T>(bits, mask);
}

#define BITS_CC_TEMPLATE(T)                                 \
    template int pop<T>(T bits);                            \
    template int par<T>(T bits);                            \
    template int ctz<T>(T bits);                            \
    template int clz<T>(T bits);                            \
    template int mxset<T>(T bits);                          \
    template int mnset<T>(T bits);                          \
    template T max<T>(T x, T y);                            \
    template T min<T>(T x, T y);                            \
    template T gcd<T>(T x, T y);                            \
    template T lb<T>(T bits);                               \
    template int ipow<T>(T bits);                           \
    template T cpow<T>(T bits);                             \
    template T fpow<T>(T bits);                             \
    template T lsb<T>(T bits);                              \
    template T msb<T>(T bits);                              \
    template T rol<T>(T bits, int rot);                     \
    template T ror<T>(T bits, int rot);                     \
    template T delta<T>(T bits, T mask, int shift);         \
    template T bswap<T>(T bits, int i, int j);              \
    template T rswap<T>(T bits, int i, int j, int len);     \
    template T rev<T>(T bits);                              \
    template T shuf<T>(T bits);                             \
    template T ishuf<T>(T bits);                            \
    template T grp<T>(T bits, T mask);                      \
    template T igrp<T>(T bits, T mask);                     \
    template T omflip<T>(T bits, T mask, uint8_t ctrl);     \
    template T bfly<T>(T bits, T mask);                     \
    template T ibfly<T>(T bits, T mask);                    \
    template T trans<T>(T bits, int rows);                  \
    template T tern<T>(T xbits, T ybits, T ctrl);           \
    template T gray<T>(T bits);                             \
    template T igray<T>(T bits);                            \
    template T extl<T>(T bits, T mask);                     \
    template T extr<T>(T bits, T mask);                     \
    template T depl<T>(T bits, T mask);                     \
    template T depr<T>(T bits, T mask);
TEMPLIFY(BITS_CC_TEMPLATE)
