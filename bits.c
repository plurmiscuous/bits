#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "bits.h"
#include "inc/extint.h"
#include "inc/N.h"

#if ASSERT
    #include <assert.h>
#else
    #define assert(x) ((void)(0))  // no side-effects
#endif

// SAFE NO-BRANCH XOR-SWAP (NB: Haven't re-tested after adding the & operators)
// #define SWAP(a, b) ((&(a) ^ &(b)) && ((b) ^= (a) ^= (b), (a) ^= (b)))

////////////////////////////
////    CALCULATIONS    ////
////////////////////////////

// POPULATION
//     int popN(uint bits) {
//         for (int i = 0; i < LOG; ++i)
//             bits = (bits & WORD[i]) + ((bits >> (1 << i)) & WORD[i]);
//         return bits;
//     }
#define POP_IMPL(N)                                                                                \
    int pop##N(uint##N##_t bits) {                                                                 \
        for (int i = 0; i < LOG##N; ++i)                                                           \
            bits = (bits & WORD##N[i]) + ((bits >> (1 << i)) & WORD##N[i]);                        \
        return bits;                                                                               \
    }
TEMPLATE_STD(POP_IMPL)

// PARITY
//     int parN(uint bits) {
//         for (int i = 1; i < BITS; i <<= 1)
//             bits ^= bits >> i;
//         return bits & 0x1;
//     }
#define PAR_IMPL(N)                                                                                \
    int par##N(uint##N##_t bits) {                                                                 \
        for (int i = BITS##N; (i >>= 1) != 0;)                                                     \
            bits ^= bits >> i;                                                                     \
        return bits & 0x1;                                                                         \
    }
TEMPLATE_STD(PAR_IMPL)

// COUNT TRAILING ZEROS
//     int ctzN(uint bits) {
//         if (bits == 0)
//             return BITS;
//
//         int n = 1;
//         uint mask = NEG;
//         for (int i = BITS >> 1; i > 1; i >>= 1) {
//             mask >>= i;
//             if ((bits & mask) == 0) {
//                 n += i;
//                 bits >>= i;
//             }
//         }
//         return n - (bits & 1);
//     }
#define CTZ_IMPL(N)                                                                                \
    int ctz##N(uint##N##_t bits) {                                                                 \
        int n = 1;                                                                                 \
        uint##N##_t mask = NEG##N;                                                                 \
        for (int i = BITS##N >> 1; i > 1; i >>= 1) {                                               \
            mask >>= i;                                                                            \
            if ((bits & mask) == 0) {                                                              \
                n += i;                                                                            \
                bits >>= i;                                                                        \
            }                                                                                      \
        }                                                                                          \
        return (-(bits == 0) & BITS##N) | (-(bits != 0) & (n - (bits & 1)));                       \
    }
TEMPLATE_STD(CTZ_IMPL)

// COUNT LEADING ZEROS
//     int clzN(uint bits) {
//         if (bits == 0)
//             return BITS;
//
//         int n = 0;
//         uint mask = NEG >> (BITS >> 1);
//         for (int i = BITS >> 1; i > 0; i >>= 1) {
//             if (bits <= mask) {
//                 n += i;
//                 bits <<= i;
//             }
//             mask |= mask << (i >> 1);
//         }
//         return n;
//     }
#define CLZ_IMPL(N)                                                                                \
    int clz##N(uint##N##_t bits) {                                                                 \
        int n = 0;                                                                                 \
        uint##N##_t mask = NEG##N >> (BITS##N >> 1);                                               \
        for (int i = BITS##N; (i >>= 1) != 0;) {                                                   \
            if (bits <= mask) {                                                                    \
                n += i;                                                                            \
                bits <<= i;                                                                        \
            }                                                                                      \
            mask |= mask << (i >> 1);                                                              \
        }                                                                                          \
        return (-(bits == 0) & BITS##N) | (-(bits != 0) & n);                                      \
    }
TEMPLATE_STD(CLZ_IMPL)

// LONGEST CHAIN OF SET BITS
//     int mxsetN(uint bits) {
//         int k;
//         for (k = 0; bits != 0; ++k)
//             bits &= (bits >> 1);
//         return k;
//     }
#define MXSET_IMPL(N)                                                                              \
    int mxset##N(uint##N##_t bits) {                                                               \
        int k;                                                                                     \
        for (k = 0; bits != 0; ++k)                                                                \
            bits &= (bits >> 1);                                                                   \
        return k;                                                                                  \
    }
TEMPLATE_STD(MXSET_IMPL)

// SHORTEST CHAIN OF SET BITS
//     int mnsetN(uint bits) {
//         uint dn = bits & ~(bits >> 1);
//         uint up = bits & ~(bits << 1);
//         int k;
//         for (k = 1; bits && (dn & up) == 0; ++k)
//             up <<= 1;
//         return k - !bits;
//     }
#define MNSET_IMPL(N)                                                                              \
    int mnset##N(uint##N##_t bits) {                                                               \
        uint##N##_t dn = bits & ~(bits >> 1);                                                      \
        uint##N##_t up = bits & ~(bits << 1);                                                      \
        int k;                                                                                     \
        for (k = 1; bits && (dn & up) == 0; ++k)                                                   \
            up <<= 1;                                                                              \
        return k - !bits;                                                                          \
    }
TEMPLATE_STD(MNSET_IMPL)

// MAXIMUM
//     uint maxN(uint x, uint y) {
//         return x ^ ((x ^ y) & -(x < y));
//     }
#define MAX_IMPL(N)                                                                                \
    uint##N##_t max##N(uint##N##_t x, uint##N##_t y) {                                             \
        return x ^ ((x ^ y) & -(x < y));                                                           \
    }
TEMPLATE_STD(MAX_IMPL)

// MINIMUM
//     uint maxN(uint x, uint y) {
//         return y ^ ((x ^ y) & -(x < y));
//     }
#define MIN_IMPL(N)                                                                                \
    uint##N##_t min##N(uint##N##_t x, uint##N##_t y) {                                             \
        return y ^ ((x ^ y) & -(x < y));                                                           \
    }
TEMPLATE_STD(MIN_IMPL)

// GREATEST COMMON DIVISOR
//     uint gcdN(uint a, uint b) {
//         while (b != 0) {
//             b ^= (a %= b);
//             b ^= (a ^= b);
//         }
//         return a;
//     }
#define GCD_IMPL(N)                                                                                \
    uint##N##_t gcd##N(uint##N##_t x, uint##N##_t y) {                                             \
        while (y != 0) {                                                                           \
            y ^= x %= y;                                                                           \
            y ^= x ^= y;                                                                           \
        }                                                                                          \
        return x;                                                                                  \
    }
TEMPLATE_STD(GCD_IMPL)

// BINARY LOGARITHM
#define LB_IMPL(N)                                                                                 \
    uint##N##_t lb##N(uint##N##_t bits) {                                                          \
        uint##N##_t m = NEG##N;                                                                    \
        uint##N##_t log = 0;                                                                       \
                                                                                                   \
        for (int i = LOG##N; i-- != 0;) {                                                          \
            m >>= (1 << i);                                                                        \
            uint##N##_t shift = (bits > m) << i;                                                   \
            bits >>= shift;                                                                        \
            log |= shift;                                                                          \
        }                                                                                          \
                                                                                                   \
        return log;                                                                                \
    }
TEMPLATE_STD(LB_IMPL)

// IS POWER OF 2
#define IPOW_IMPL(N)                                                                               \
    int ipow##N(uint##N##_t bits) {                                                                \
        return bits && (bits & (bits - 1)) == 0;                                                   \
    }
TEMPLATE_STD(IPOW_IMPL)

// CEIL POWER OF 2
#define CPOW_IMPL(N)                                                                               \
    uint##N##_t cpow##N(uint##N##_t bits) {                                                        \
        bits += bits == 0;                                                                         \
        --bits;                                                                                    \
        for (int i = BITS##N; (i >>= 1) != 0;)                                                     \
            bits |= bits >> i;                                                                     \
        ++bits;                                                                                    \
        return bits;                                                                               \
    }
TEMPLATE_STD(CPOW_IMPL)

// FLOOR POWER OF 2
#define FPOW_IMPL(N)                                                                               \
    uint##N##_t fpow##N(uint##N##_t bits) {                                                        \
        for (int i = BITS##N; (i >>= 1) != 0;)                                                     \
            bits |= bits >> i;                                                                     \
        return bits - (bits >> 1);                                                                 \
    }
TEMPLATE_STD(FPOW_IMPL)

// ISOLATE LEAST SIGNIFICANT SET BIT
#define LSB_IMPL(N)                                                                                \
    uint##N##_t lsb##N(uint##N##_t bits) {                                                         \
        return bits & -bits;                                                                       \
    }
TEMPLATE_STD(LSB_IMPL)

// ISOLATE MOST SIGNIFICANT SET BIT
#define MSB_IMPL(N)                                                                                \
    uint##N##_t msb##N(uint##N##_t bits) {                                                         \
        for (int i = BITS##N; (i >>= 1) != 0;)                                                     \
            bits |= bits >> i;                                                                     \
        return (bits >> 1) + (bits != 0);                                                          \
    }
TEMPLATE_STD(MSB_IMPL)

////////////////////////////
////    PERMUTATIONS    ////
////////////////////////////

// ROTATE LEFT
//     uint rolN(uint bits, int rot) {
//         return (bits << rot) | (bits >> (BITS - rot));
//     }
#define ROL_IMPL(N)                                         \
    uint##N##_t rol##N(uint##N##_t bits, int rot) {         \
        assert(0 <= rot && rot < BITS##N);                  \
        return (bits << rot) | (bits >> (BITS##N - rot));   \
    }
TEMPLATE_STD(ROL_IMPL)

// ROTATE RIGHT
//     uint rorN(uint bits, int rot) {
//         return (bits << (BITS - rot)) | (bits >> rot);
//     }
#define ROR_IMPL(N)                                         \
    uint##N##_t ror##N(uint##N##_t bits, int rot) {         \
        assert(0 <= rot && rot < BITS##N);                  \
        return (bits << (BITS##N - rot)) | (bits >> rot);   \
    }
TEMPLATE_STD(ROR_IMPL)

// DELTA SWAP
//     uint deltaN(uint bits, uint mask, int shift) {
//         uint tmp = (bits ^ (bits >> shift)) & mask;
//         return bits ^ tmp ^ (tmp << shift);;
//     }
#define DELTA_IMPL(N)                                                       \
    uint##N##_t delta##N(uint##N##_t bits, uint##N##_t mask, int delta) {   \
        assert(0 <= delta && delta < BITS##N);                              \
        uint##N##_t tmp = (bits ^ (bits >> delta)) & mask;                  \
        bits ^= tmp ^ (tmp << delta);                                       \
        return bits;                                                        \
    }
TEMPLATE_STD(DELTA_IMPL)

// SWAPPING INDIVIDUAL BITS
    // uint bswpN(uint bits, int i, int j) {
    //     uint tmp = ((bits >> i) ^ (bits >> j)) & 1;
    //     return bits ^ ((tmp << i) | (tmp << j));
    // }
#define BSWAP_IMPL(N)                                       \
    uint##N##_t bswap##N(uint##N##_t bits, int i, int j) {  \
        assert(0 <= i && i < BITS##N);                      \
        assert(0 <= j && j < BITS##N);                      \
        uint##N##_t tmp = ((bits >> i) ^ (bits >> j)) & 1;  \
        return bits ^ ((tmp << i) | (tmp << j));            \
    }
TEMPLATE_STD(BSWAP_IMPL)

// SWAPPING BIT RANGES
//     uint rswpN(uint bits, int i, int j, int len) {
//         uint tmp = ((bits >> i) ^ (bits >> j)) & ((ONE << len) - 1);
//         return bits ^ ((tmp << i) | (tmp << j));
//     }
#define RSWAP_IMPL(N)                                                           \
    uint##N##_t rswap##N(uint##N##_t bits, int i, int j, int len) {             \
        assert(i < BITS##N && i + len <= BITS##N);                              \
        assert(j < BITS##N && j + len <= BITS##N);                              \
        uint##N##_t tmp = ((bits >> i) ^ (bits >> j)) & ((ONE##N << len) - 1);  \
        return bits ^ ((tmp << i) | (tmp << j));                                \
    }
TEMPLATE_STD(RSWAP_IMPL)

// REVERSE
//     uint revN(uint bits) {
//         for (int i = 0; i < LOG; ++i)
//             bits = (bits & WORD[i]) << (1 << i) | (bits & ~WORD[i]) >> (1 << i);
//         return bits;
//     }
#define REV_IMPL(N)                                                                     \
    uint##N##_t rev##N(uint##N##_t bits) {                                              \
        for (int i = 0; i < LOG##N; ++i)                                                \
            bits = (bits & WORD##N[i]) << (1 << i) | (bits & ~WORD##N[i]) >> (1 << i);  \
        return bits;                                                                    \
    }
TEMPLATE_STD(REV_IMPL)

// PERFECT OUTER-SHUFFLE
//     uint shufN(uint bits, int size) {
//         for (int i = LOG - 2; i >= size; --i)
//             bits = deltaN(bits, SHUF[i], 1 << i);
//         return bits;
//     }
#define SHUF_IMPL(N)                                    \
    uint##N##_t shuf##N(uint##N##_t bits) {             \
        for (int i = LOG##N - 1; i-- != 0;)             \
            bits = delta##N(bits, SHUF##N[i], 1 << i);  \
        return bits;                                    \
    }
TEMPLATE_STD(SHUF_IMPL)

// PERFECT OUTER-UNSHUFFLE
//     uint ishufN(uint bits, int size) {
//         for (int i = size; i < LOG - 1; ++i)
//             bits = deltaN(bits, SHUF[i], 1 << i);
//         return bits;
//     }
#define ISHUF_IMPL(N)                                   \
    uint##N##_t ishuf##N(uint##N##_t bits) {            \
        for (int i = 0; i < LOG##N - 1; ++i)            \
            bits = delta##N(bits, SHUF##N[i], 1 << i);  \
        return bits;                                    \
    }
TEMPLATE_STD(ISHUF_IMPL)

// OMFLIP
//     uint omflipN(uint bits, uint mask, uint8_t opts) {
//         for (int i = 0; i < 2; ++i) {
//             uint m = (mask >> (i * (BITS >> 1))) & 0xFFFF;
//             if (((opts >> i) & 0x1) == 0) {
//                 bits = deltaN(bits, m, BITS >> 1);
//                 bits = shufN(bits, 0);
//             } else {
//                 bits = ishufN(bits, 0);
//                 bits = deltaN(bits, m, BITS >> 1);
//             }
//         }
//         return bits;
//     }
#define OMFLIP_IMPL(N)                                                            \
    uint##N##_t omflip##N(uint##N##_t bits, uint##N##_t mask, uint8_t opts) {     \
        for (int i = 0; i < 2; ++i) {                                             \
            uint##N##_t m = (mask >> (i * (BITS##N >> 1))) & WORD##N[LOG##N - 1]; \
            if (((opts >> i) & 0x1) == 0) {                                       \
                bits = delta##N(bits, m, BITS##N >> 1);                           \
                bits = shuf##N(bits);                                             \
            } else {                                                              \
                bits = ishuf##N(bits);                                            \
                bits = delta##N(bits, m, BITS##N >> 1);                           \
            }                                                                     \
        }                                                                         \
        return bits;                                                              \
    }
TEMPLATE_STD(OMFLIP_IMPL)

// BUTTERFLY NETWORK
//     uint bflyN(uint bits, uint mask) {
//         for (int i = LOG; i-- != 0;)
//             bits = deltaN(bits, mask & WORD[i], 1 << i);
//         return bits;
//     }
#define BFLY_IMPL(N)                                            \
    uint##N##_t bfly##N(uint##N##_t bits, uint##N##_t mask) {   \
        for (int i = LOG##N; i-- != 0;)                         \
            bits = delta##N(bits, mask & WORD##N[i], 1 << i);   \
        return bits;                                            \
    }
TEMPLATE_STD(BFLY_IMPL)

// INVERSE-BUTTERFLY NETWORK
//     uint ibflyN(uint bits, uint mask) {
//         for (int i = 0; i < LOG; ++i)
//             bits = deltaN(bits, mask & WORD[i], 1 << i);
//         return bits;
//     }
#define IBFLY_IMPL(N)                                           \
    uint##N##_t ibfly##N(uint##N##_t bits, uint##N##_t mask) {  \
        for (int i = 0; i < LOG##N; ++i)                        \
            bits = delta##N(bits, mask & WORD##N[i], 1 << i);   \
        return bits;                                            \
    }
TEMPLATE_STD(IBFLY_IMPL)

// BENES NETWORK
//     uint benesN(uint bits, uint mask, int log1, int log2) {
//         bits = deltaN(bits, mask & WORD[log1], 1 << log1);
//         bits = deltaN(bits, mask & WORD[log2], 1 << log2);
//         return bits;
//     }
#define BENES_IMPL(N)                                                               \
    uint##N##_t benes##N(uint##N##_t bits, uint##N##_t mask, int log1, int log2) {  \
        assert(0 <= log1 && log1 < LOG##N);                                         \
        assert(0 <= log2 && log2 < LOG##N);                                         \
        bits = delta##N(bits, mask & WORD##N[log1], 1 << log1);                     \
        bits = delta##N(bits, mask & WORD##N[log2], 1 << log2);                     \
        return bits;                                                                \
    }
TEMPLATE_STD(BENES_IMPL)

// MATRIX TRANSPOSE
//     uint transN(uint bits, int rows) {
//         int c = LOG - lbN(rows);
//         int g = gcdN(LOG, c);
//         int d = LOG / g - 1;
//
//         for (int i = 0; i < g; ++i) {
//             for (int j = 0, k = i, n = i + c; j < d; ++j, k = n, n += c) {
//                 if (n >= LOG)
//                     n -= LOG;
//                 if (n != k) {
//                     int mx = maxN(n, k);
//                     int mn = k ^ n ^ mx;
//                     int sh = (1 << mx) - (1 << mn);
//                     bits = deltaN(bits, WORD[mx] & ~WORD[mn], sh);
//                 }
//             }
//         }
//         return bits;
//     }
#define TRANS_IMPL(N)                                                                              \
    uint##N##_t trans##N(uint##N##_t bits, int rows) {                                             \
        assert(((N / rows) * rows) == N);                                                          \
        int c = LOG##N - lb##N(rows);                                                              \
        int g = gcd##N(LOG##N, c);                                                                 \
        int d = LOG##N / g - 1;                                                                    \
                                                                                                   \
        for (int i = 0; i < g; ++i) {                                                              \
            for (int j = 0, k = i, n = i + c; j < d; ++j, k = n, n += c) {                         \
                if (n >= LOG##N)                                                                   \
                    n -= LOG##N;                                                                   \
                if (n != k) {                                                                      \
                    int mx = max##N(n, k);                                                         \
                    int mn = k ^ n ^ mx;                                                           \
                    int sh = (1 << mx) - (1 << mn);                                                \
                    bits = delta##N(bits, WORD##N[mx] & ~WORD##N[mn], sh);                         \
                }                                                                                  \
            }                                                                                      \
        }                                                                                          \
        return bits;                                                                               \
    }
TEMPLATE_STD(TRANS_IMPL)

/////////////////////////////
////    MANIPULATIONS    ////
/////////////////////////////

// LFSR WITH MAXIMAL-LENGTH SEQUENCE
//     uint lfsrN(uint bits) {
//         bits = (bits >> 1) ^ ((-(bits & 0x1)) & FTAPSN);
//         return bits;
//     }
#define LFSR_IMPL(N)                                        \
    uint##N##_t lfsr##N(uint##N##_t bits) {                 \
        bits = (bits >> 1) ^ ((-(bits & 0x1)) & FTAPS##N);  \
        return bits;                                        \
    }
TEMPLATE_STD(LFSR_IMPL)

// INVERSE LFSR WITH MAXIMAL-LENGTH SEQUENCE
//     uint ilfsrN(uint bits) {
//         bits = (bits << 1) ^ (-(bits >> (BITS - 1)) & RTAPSN);
//         return bits;
//     }
#define ILFSR_IMPL(N)                                               \
    uint##N##_t ilfsr##N(uint##N##_t bits) {                        \
        bits = (bits << 1) ^ (-(bits >> (BITS##N - 1)) & RTAPS##N); \
        return bits;                                                \
    }
TEMPLATE_STD(ILFSR_IMPL)

// BITWISE TERNARY
//     uint ternN(uint xbits, uint ybits, uint mask) {
//         return (mask & (xbits ^ ybits)) ^ ybits;
//     }
#define TERN_IMPL(N)                                                                \
    uint##N##_t tern##N(uint##N##_t xbits, uint##N##_t ybits, uint##N##_t mask) {   \
        return (mask & (xbits ^ ybits)) ^ ybits;                                    \
    }
TEMPLATE_STD(TERN_IMPL)

// BINARY TO GRAY CODE
//     uint grayN(uint bits) {
//         return bits ^ (bits >> 1);
//     }
#define GRAY_IMPL(N)                        \
    uint##N##_t gray##N(uint##N##_t bits) { \
        return bits ^ (bits >> 1);          \
    }
TEMPLATE_STD(GRAY_IMPL)

// GRAY TO BINARY CODE
//     uint igrayN(uint bits) {
//         for (int i = 1; i < BITS; i <<= 1)
//             bits ^= bits >> i;
//         return bits;
//     }
#define IGRAY_IMPL(N)                           \
    uint##N##_t igray##N(uint##N##_t bits) {    \
        for (int i = 1; i < BITS##N; i <<= 1)   \
            bits ^= bits >> i;                  \
        return bits;                            \
    }
TEMPLATE_STD(IGRAY_IMPL)

// EXTRACT LEFT
//     uint extlN(uint bits, uint mask) {
//         bits &= mask;
//         uint m1 = ~mask >> 1;
//
//         for (int i = 0; i < LOG; ++i) {
//             uint m = m1;
//             for (int j = 1; j < BITS; j <<= 1)
//                 m ^= (m >> j);
//
//             uint mv = m & mask;
//             mask = (mask ^ mv) | (mv << (1 << i));
//
//             uint mt = bits & mv;
//             bits = (bits ^ mt) | (mt << (1 << i));
//             m1 &= ~m;
//         }
//
//         return bits;
//     }
#define EXTL_IMPL(N)                                            \
    uint##N##_t extl##N(uint##N##_t bits, uint##N##_t mask) {   \
        bits &= mask;                                           \
        uint##N##_t m1 = (uint##N##_t) ~mask >> 1;              \
                                                                \
        for (int i = 0; i < LOG##N; ++i) {                      \
            uint##N##_t m = m1;                                 \
            for (int j = 1; j < BITS##N; j <<= 1)               \
                m ^= (m >> j);                                  \
                                                                \
            uint##N##_t mv = m & mask;                          \
            mask = (mask ^ mv) | (mv << (ONE##N << i));         \
                                                                \
            uint##N##_t mt = bits & mv;                         \
            bits = (bits ^ mt) | (mt << (ONE##N << i));         \
            m1 &= ~m;                                           \
        }                                                       \
                                                                \
        return bits;                                            \
    }
TEMPLATE_STD(EXTL_IMPL)

// EXTRACT RIGHT
//     uint extrN(uint bits, uint mask) {
//         bits &= mask;
//         uint m1 = ~mask << 1;
//
//         for (int i = 0; i < LOG; ++i) {
//             uint m = m1;
//             for (int j = 1; j < BITS; j <<= 1)
//                 m ^= (m << j);
//
//             uint mv = m & mask;
//             mask = (mask ^ mv) | (mv >> (1 << i));
//
//             uint mt = bits & mv;
//             bits = (bits ^ mt) | (mt >> (1 << i));
//             m1 &= ~m;
//         }
//
//         return bits;
//     }
#define EXTR_IMPL(N)                                            \
    uint##N##_t extr##N(uint##N##_t bits, uint##N##_t mask) {   \
        bits &= mask;                                           \
        uint##N##_t m1 = ~mask << 1;                            \
                                                                \
        for (int i = 0; i < LOG##N; ++i) {                      \
            uint##N##_t m = m1;                                 \
            for (int j = 1; j < BITS##N; j <<= 1)               \
                m ^= (m << j);                                  \
                                                                \
            uint##N##_t mv = m & mask;                          \
            mask = (mask ^ mv) | (mv >> (ONE##N << i));         \
                                                                \
            uint##N##_t mt = bits & mv;                         \
            bits = (bits ^ mt) | (mt >> (ONE##N << i));         \
            m1 &= ~m;                                           \
        }                                                       \
                                                                \
        return bits;                                            \
    }
TEMPLATE_STD(EXTR_IMPL)

// DEPOSIT LEFT
//     uint deplN(uint bits, uint mask) {
//         uint masks[LOG];
//         uint m0 = mask;
//         uint m1 = ~mask << 1;
//
//         for (int i = 0; i < LOG; ++i) {
//             uint m = m1;
//             for (int j = 1; j < BITS; j <<= 1)
//                 m ^= (m << j);
//
//             masks[i] = m & mask;
//             mask = (mask ^ masks[i]) | (masks[i] >> (1 << i));
//             m1 &= ~m;
//         }
//
//         for (int i = LOG - 1; i >= 0; --i)
//             bits = (bits & ~masks[i]) | ((bits << (1 << i)) & masks[i]);
//
//         return bits & m0;
//     }
#define DEPL_IMPL(N)                                                            \
    uint##N##_t depl##N(uint##N##_t bits, uint##N##_t mask) {                   \
        uint##N##_t masks[LOG##N];                                              \
        uint##N##_t m0 = mask;                                                  \
        uint##N##_t m1 = ~mask << 1;                                            \
                                                                                \
        for (int i = 0; i < LOG##N; ++i) {                                      \
            uint##N##_t m = m1;                                                 \
            for (int j = 1; j < BITS##N; j <<= 1)                               \
                m ^= (m << j);                                                  \
                                                                                \
            masks[i] = m & mask;                                                \
            mask = (mask ^ masks[i]) | (masks[i] >> (ONE##N << i));             \
            m1 &= ~m;                                                           \
        }                                                                       \
                                                                                \
        for (int i = LOG##N; i-- != 0;)                                          \
            bits ^= ((bits ^ (bits << (ONE##N << i))) & masks[i]);              \
                                                                                \
        return bits & m0;                                                       \
    }
TEMPLATE_STD(DEPL_IMPL)

// DEPOSIT RIGHT
//     uint deprN(uint bits, uint mask) {
//         uint masks[LOG];
//         uint m0 = mask;
//         uint m1 = ~mask >> 1;
//
//         for (int i = 0; i < LOG; ++i) {
//             uint m = m1;
//             for (int j = 1; j < BITS; j <<= 1)
//                 m ^= (m >> j);
//
//             masks[i] = m & mask;
//             mask = (mask ^ masks[i]) | (masks[i] << (1 << i));
//             m1 &= ~m;
//         }
//
//         for (int i = LOG - 1; i >= 0; --i)
//             bits = (bits & ~masks[i]) | ((bits >> (1 << i)) & masks[i]);
//
//         return bits & m0;
//     }
#define DEPR_IMPL(N)                                                            \
    uint##N##_t depr##N(uint##N##_t bits, uint##N##_t mask) {                   \
        uint##N##_t masks[LOG##N];                                              \
        uint##N##_t m0 = mask;                                                  \
        uint##N##_t m1 = (uint##N##_t) ~mask >> 1;                              \
                                                                                \
        for (int i = 0; i < LOG##N; ++i) {                                      \
            uint##N##_t m = m1;                                                 \
            for (int j = 1; j < BITS##N; j <<= 1)                               \
                m ^= (m >> j);                                                  \
                                                                                \
            masks[i] = m & mask;                                                \
            mask = (mask ^ masks[i]) | (masks[i] << (ONE##N << i));             \
            m1 &= ~m;                                                           \
        }                                                                       \
                                                                                \
        for (int i = LOG##N; i-- != 0;)                                          \
            bits ^= (bits ^ (bits >> (ONE##N << i))) & masks[i];                \
                                                                                \
        return bits & m0;                                                       \
    }
TEMPLATE_STD(DEPR_IMPL)

// GROUP
//     uint grpN(uint bits, uint mask) {
//         return extrN(bits, mask) | extlN(bits, ~mask);
//     }
#define GRP_IMPL(N)                                             \
    uint##N##_t grp##N(uint##N##_t bits, uint##N##_t mask) {    \
        return extr##N(bits, mask) | extl##N(bits, ~mask);      \
    }
TEMPLATE_STD(GRP_IMPL)

// UNGROUP
//     uint igrpN(uint bits, uint mask) {
//         return deprN(bits, ~mask) | deplN(bits, mask);
//     }
#define IGRP_IMPL(N)                                            \
    uint##N##_t igrp##N(uint##N##_t bits, uint##N##_t mask) {   \
        return depr##N(bits, ~mask) | depl##N(bits, mask);      \
    }
TEMPLATE_STD(IGRP_IMPL)
