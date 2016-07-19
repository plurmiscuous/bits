#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "test_expect.h"

#include "../bits.h"
#include "../inc/extint.h"
#include "../inc/template.h"
#include "../util/print.h"

#define EXPECT_POP_IMPL(N)                                                                         \
    int expect_pop##N(uint##N##_t bits) {                                                          \
        int set = 0;                                                                               \
        for (set = 0; bits; bits >>= 1)                                                            \
            set += bits & 1;                                                                       \
        return set;                                                                                \
    }
TEMPLATE_STD(EXPECT_POP_IMPL)

#define EXPECT_PAR_IMPL(N)                                                                         \
    int expect_par##N(uint##N##_t bits) {                                                          \
        int parity = 0;                                                                            \
        while (bits) {                                                                             \
            parity = !parity;                                                                      \
            bits = bits & (bits - 1);                                                              \
        }                                                                                          \
        return parity;                                                                             \
    }
TEMPLATE_STD(EXPECT_PAR_IMPL)

#define EXPECT_CTZ_IMPL(N)                                                                         \
    int expect_ctz##N(uint##N##_t bits) {                                                          \
        if (!bits)                                                                                 \
            return BITS##N;                                                                        \
                                                                                                   \
        int n = 0;                                                                                 \
        uint##N##_t mask = 1;                                                                      \
        while ((bits & mask) == 0) {                                                               \
            n++;                                                                                   \
            mask <<= 1;                                                                            \
        }                                                                                          \
        return n;                                                                                  \
    }
TEMPLATE_STD(EXPECT_CTZ_IMPL)

#define EXPECT_CLZ_IMPL(N)                                                                         \
    int expect_clz##N(uint##N##_t bits) {                                                          \
        if (!bits)                                                                                 \
            return BITS##N;                                                                        \
                                                                                                   \
        int n = 0;                                                                                 \
        uint##N##_t mask = (uint##N##_t) 1 << (BITS##N - 1);                                       \
        while ((bits & mask) == 0) {                                                               \
            n++;                                                                                   \
            mask >>= 1;                                                                            \
        }                                                                                          \
        return n;                                                                                  \
    }
TEMPLATE_STD(EXPECT_CLZ_IMPL)

#define EXPECT_MXSET_IMPL(N)                                                                       \
    int expect_mxset##N(uint##N##_t bits) {                                                        \
        int set = 0;                                                                               \
        int max = 0;                                                                               \
                                                                                                   \
        while (bits) {                                                                             \
            if (bits & 0x1)                                                                        \
                ++set;                                                                             \
            else {                                                                                 \
                if (set > max)                                                                     \
                    max = set;                                                                     \
                set = 0;                                                                           \
            }                                                                                      \
            bits >>= 1;                                                                            \
        }                                                                                          \
                                                                                                   \
        if (set > max)                                                                             \
            max = set;                                                                             \
                                                                                                   \
        return max;                                                                                \
    }
TEMPLATE_STD(EXPECT_MXSET_IMPL)

#define EXPECT_MNSET_IMPL(N)                                                                       \
    int expect_mnset##N(uint##N##_t bits) {                                                        \
        int set = 0;                                                                               \
        int min = 0;                                                                               \
                                                                                                   \
        while (bits) {                                                                             \
            if (bits & 0x1)                                                                        \
                ++set;                                                                             \
            else {                                                                                 \
                if (!min || (set && set < min))                                                    \
                    min = set;                                                                     \
                set = 0;                                                                           \
            }                                                                                      \
            bits >>= 1;                                                                            \
        }                                                                                          \
                                                                                                   \
        if (!min || (set && set < min))                                                            \
            min = set;                                                                             \
                                                                                                   \
        return min;                                                                                \
    }
TEMPLATE_STD(EXPECT_MNSET_IMPL)

#define EXPECT_MAX_IMPL(N)                                                                         \
    uint##N##_t expect_max##N(uint##N##_t x, uint##N##_t y) {                                      \
        return x > y ? x : y;                                                                      \
    }
TEMPLATE_STD(EXPECT_MAX_IMPL)

#define EXPECT_MIN_IMPL(N)                                                                         \
    uint##N##_t expect_min##N(uint##N##_t x, uint##N##_t y) {                                      \
        return x < y ? x : y;                                                                      \
    }
TEMPLATE_STD(EXPECT_MIN_IMPL)

#define EXPECT_GCD_IMPL(N)                                                                         \
    uint##N##_t expect_gcd##N(uint##N##_t x, uint##N##_t y) {                                      \
        while (x != 0) {                                                                           \
            uint##N##_t tmp = x;                                                                   \
            x = y % x;                                                                             \
            y = tmp;                                                                               \
        }                                                                                          \
        return y;                                                                                  \
    }
TEMPLATE_STD(EXPECT_GCD_IMPL)

#define EXPECT_LB_IMPL(N)                                                                          \
    uint##N##_t expect_lb##N(uint##N##_t bits) {                                                   \
        int log = 0;                                                                               \
        while (bits >>= 1)                                                                         \
            ++log;                                                                                 \
        return log;                                                                                \
    }
TEMPLATE_STD(EXPECT_LB_IMPL)

#define EXPECT_IPOW_IMPL(N)                                                                        \
    int expect_ipow##N(uint##N##_t bits) {                                                         \
        uint##N##_t b0 = bits;                                                                     \
        for (int i = 1; i < BITS##N; i <<= 1)                                                      \
            bits |= bits >> i;                                                                     \
        bits = (bits >> 1) + 1;                                                                    \
        return bits == b0;                                                                         \
    }
TEMPLATE_STD(EXPECT_IPOW_IMPL)

#define EXPECT_CPOW_IMPL(N)                                                                        \
    uint##N##_t expect_cpow##N(uint##N##_t bits) {                                                 \
        if (!bits)                                                                                 \
            return 1;                                                                              \
                                                                                                   \
        uint##N##_t b0 = bits;                                                                     \
        for (int i = 1; i < BITS##N; i <<= 1)                                                      \
            bits |= bits >> i;                                                                     \
        bits = (bits >> 1) + 1;                                                                    \
        return bits == b0 ? b0 : (bits << 1);                                                      \
    }
TEMPLATE_STD(EXPECT_CPOW_IMPL)

#define EXPECT_FPOW_IMPL(N)                                                                        \
    uint##N##_t expect_fpow##N(uint##N##_t bits) {                                                 \
        for (int i = 1; i < BITS##N; i <<= 1)                                                      \
            bits |= bits >> i;                                                                     \
        bits = (bits >> 1) + (bits != 0);                                                          \
        return bits;                                                                               \
    }
TEMPLATE_STD(EXPECT_FPOW_IMPL)

#define EXPECT_LSB_IMPL(N)                                                                         \
    uint##N##_t expect_lsb##N(uint##N##_t bits) {                                                  \
        if (!bits)                                                                                 \
            return bits;                                                                           \
                                                                                                   \
        int i = 0;                                                                                 \
        while ((bits & 0x1) == 0) {                                                                \
            ++i;                                                                                   \
            bits >>= 1;                                                                            \
        }                                                                                          \
        return ONE##N << i;                                                                        \
    }
TEMPLATE_STD(EXPECT_LSB_IMPL)

#define EXPECT_MSB_IMPL(N)                                                                         \
    uint##N##_t expect_msb##N(uint##N##_t bits) {                                                  \
        if (!bits)                                                                                 \
            return bits;                                                                           \
                                                                                                   \
        int i = 0;                                                                                 \
        while (bits >>= 1)                                                                         \
            ++i;                                                                                   \
        return ONE##N << i;                                                                        \
    }
TEMPLATE_STD(EXPECT_MSB_IMPL)

#define EXPECT_REV_IMPL(N)                                                                         \
    uint##N##_t expect_rev##N(uint##N##_t bits) {                                                  \
        uint##N##_t rev = 0;                                                                       \
        for (size_t i = 0; i < BITS##N - 1; ++i, rev <<= 1, bits >>= 1)                            \
            rev |= bits & 1;                                                                       \
        rev |= bits & 1;                                                                           \
        return rev;                                                                                \
    }
TEMPLATE_STD(EXPECT_REV_IMPL)

#define EXPECT_SHUF_IMPL(N)                                                                        \
    uint##N##_t expect_shuf##N(uint##N##_t bits) {                                                 \
        uint##N##_t lo = bits & UNIT##N[0];                                                        \
        uint##N##_t hi = (bits >> (BITS##N / 2)) & UNIT##N[0];                                     \
        uint##N##_t shuf = 0;                                                                      \
        for (size_t i = 0; i < BITS##N / 2; ++i)                                                   \
            shuf |= (lo & 1ULL << i) << i | (hi & 1ULL << i) << (i + 1);                           \
        return shuf;                                                                               \
    }
TEMPLATE_STD(EXPECT_SHUF_IMPL)

#define EXPECT_ISHUF_IMPL(N)                                                                       \
    uint##N##_t expect_ishuf##N(uint##N##_t bits) {                                                \
        uint##N##_t one = 1;                                                                       \
        uint##N##_t lo = bits & UNIT##N[1];                                                        \
        uint##N##_t hi = bits & ~UNIT##N[1];                                                       \
        uint##N##_t ishuf = 0;                                                                     \
        for (size_t i = 0; i < BITS##N / 2; ++i)                                                   \
            ishuf |= ((hi & one << (2 * i + 1)) << (BITS##N / 2 - 1 - i))                          \
                    | ((lo & one << (2 * i)) >> i);                                                \
        return ishuf;                                                                              \
    }
TEMPLATE_STD(EXPECT_ISHUF_IMPL)

#define EXPECT_GRP_IMPL(N)                                                                         \
    uint##N##_t expect_grp##N(uint##N##_t bits, uint##N##_t mask) {                                \
        uint##N##_t grp = 0;                                                                       \
        int k = 0;                                                                                 \
                                                                                                   \
        uint##N##_t b1 = bits;                                                                     \
        uint##N##_t m1 = mask;                                                                     \
        for (int i = 0; i < BITS##N; ++i, b1 >>= 1, m1 >>= 1)                                      \
            if ((m1 & 0x1) == 1)                                                                   \
                grp |= (b1 & 0x1) << k++;                                                          \
                                                                                                   \
        uint##N##_t b0 = bits;                                                                     \
        uint##N##_t m0 = mask;                                                                     \
        for (int i = 0; i < BITS##N; ++i, b0 >>= 1, m0 >>= 1)                                      \
            if ((m0 & 0x1) == 0)                                                                   \
                grp |= (b0 & 0x1) << k++;                                                          \
                                                                                                   \
        return grp;                                                                                \
    }
TEMPLATE_STD(EXPECT_GRP_IMPL)

#define EXPECT_IGRP_IMPL(N)                                                                        \
    uint##N##_t expect_igrp##N(uint##N##_t bits, uint##N##_t mask) {                               \
        uint##N##_t igrp = 0;                                                                      \
                                                                                                   \
        uint##N##_t m1 = mask;                                                                     \
        for (int i = 0; i < BITS##N; ++i) {                                                        \
            if ((m1 & 0x1) == 1) {                                                                 \
                igrp |= (bits & 0x1) << i;                                                         \
                bits >>= 1;                                                                        \
            }                                                                                      \
            m1 >>= 1;                                                                              \
        }                                                                                          \
                                                                                                   \
        uint##N##_t m0 = mask;                                                                     \
        for (int i = 0; i < BITS##N; ++i) {                                                        \
            if ((m0 & 0x1) == 0) {                                                                 \
                igrp |= (bits & 0x1) << i;                                                         \
                bits >>= 1;                                                                        \
            }                                                                                      \
            m0 >>= 1;                                                                              \
        }                                                                                          \
                                                                                                   \
        return igrp;                                                                               \
    }
TEMPLATE_STD(EXPECT_IGRP_IMPL)

#define EXPECT_OMFLIP_IMPL(N)                                                                      \
    uint##N##_t expect_omflip##N(uint##N##_t bits, uint##N##_t mask, uint8_t opts) {               \
        uint##N##_t omflip = 0;                                                                    \
        for (int i = 0; i < 2; ++i) {                                                              \
            uint##N##_t tmp = 0;                                                                   \
            if (((opts >> i) & 0x1) == 0) {                                                        \
                for (int j = 0; j < BITS##N / 2; ++j) {                                            \
                    tmp |= ((bits >> j) & 0x1) << (2 * j);                                         \
                    tmp |= ((bits >> (j + BITS##N / 2)) & 0x1) << (2 * j + 1);                     \
                    if (mask >> j & 0x1)                                                           \
                        tmp = bswap##N(tmp, 2 * j, 2 * j + 1);                                     \
                }                                                                                  \
            } else {                                                                               \
                for (int j = 0; j < BITS##N / 2; ++j) {                                            \
                    tmp |= ((bits >> 2 * j) & 0x1) << j;                                           \
                    tmp |= ((bits >> (2 * j + 1)) & 0x1) << (j + BITS##N / 2);                     \
                    if (mask >> (j + i * BITS##N / 2) & 0x1)                                       \
                        tmp = bswap##N(tmp, j, j + BITS##N / 2);                                   \
                }                                                                                  \
            }                                                                                      \
            omflip = bits = tmp;                                                                   \
        }                                                                                          \
        return omflip;                                                                             \
    }
TEMPLATE_STD(EXPECT_OMFLIP_IMPL)

#define EXPECT_BFLY_IMPL(N)                                                                        \
    uint##N##_t expect_bfly##N(uint##N##_t bits, uint##N##_t mask) {                               \
        for (int d = BITS##N / 2; d > 0; d /= 2)                                                   \
            for (int k = 0; k < BITS##N; k += (d << 1))                                            \
                for (int j = 0; j < d; ++j)                                                        \
                    if (mask >> (k + j) & 0x1)                                                     \
                        bits = bswap##N(bits, k + j, k + j + d);                                   \
        return bits;                                                                               \
    }
TEMPLATE_STD(EXPECT_BFLY_IMPL)

#define EXPECT_IBFLY_IMPL(N)                                                                       \
    uint##N##_t expect_ibfly##N(uint##N##_t bits, uint##N##_t mask) {                              \
        for (int d = 1; d <= BITS##N / 2; d *= 2)                                                  \
            for (int k = BITS##N - (d << 1); k >= 0; k -= (d << 1))                                \
                for (int j = d - 1; j >= 0; --j)                                                   \
                    if (mask >> (k + j) & 0x1)                                                     \
                        bits = bswap##N(bits, k + j, k + j + d);                                   \
        return bits;                                                                               \
    }
TEMPLATE_STD(EXPECT_IBFLY_IMPL)

#define EXPECT_BENES_IMPL(N)                                                                       \
    uint##N##_t expect_benes##N(uint##N##_t bits, uint##N##_t mask, int log1, int log2) {          \
        int d = 1 << log1;                                                                         \
        for (int k = 0; k < BITS##N; k += (d << 1))                                                \
            for (int j = 0; j < d; ++j)                                                            \
                if (mask >> (k + j) & 0x1)                                                         \
                    bits = bswap##N(bits, k + j, k + j + d);                                       \
        d = 1 << log2;                                                                             \
        for (int k = 0; k < BITS##N; k += (d << 1))                                                \
            for (int j = 0; j < d; ++j)                                                            \
                if (mask >> (k + j) & 0x1)                                                         \
                    bits = bswap##N(bits, k + j, k + j + d);                                       \
        return bits;                                                                               \
    }
TEMPLATE_STD(EXPECT_BENES_IMPL)

#define EXPECT_EXTR_IMPL(N)                                                                        \
    uint##N##_t expect_extr##N(uint##N##_t bits, uint##N##_t mask) {                               \
        uint##N##_t res = 0;                                                                       \
        int k = 0;                                                                                 \
                                                                                                   \
        for (int i = 0; i < BITS##N; ++i)                                                          \
            if (mask >> i & 0x1)                                                                   \
                res |= (bits >> i & 0x1) << k++;                                                   \
                                                                                                   \
        return res;                                                                                \
    }
TEMPLATE_STD(EXPECT_EXTR_IMPL)

#define EXPECT_EXTL_IMPL(N)                                                                        \
    uint##N##_t expect_extl##N(uint##N##_t bits, uint##N##_t mask) {                               \
        uint##N##_t res = 0;                                                                       \
        int k = BITS##N;                                                                           \
        for (int i = BITS##N; i-- > 0;)                                                            \
            if (mask >> i & 0x1)                                                                   \
                res |= (bits >> i & 0x1) << --k;                                                   \
        return res;                                                                                \
    }
TEMPLATE_STD(EXPECT_EXTL_IMPL)

#define EXPECT_DEPR_IMPL(N)                                                                        \
    uint##N##_t expect_depr##N(uint##N##_t bits, uint##N##_t mask) {                               \
        uint##N##_t res = 0;                                                                       \
        int k = BITS##N;                                                                           \
                                                                                                   \
        for (int i = BITS##N; i-- > 0;)                                                            \
            if (mask >> i & 0x1)                                                                   \
                res |= (bits >> --k & 0x1) << i;                                                   \
                                                                                                   \
        return res;                                                                                \
    }
TEMPLATE_STD(EXPECT_DEPR_IMPL)

#define EXPECT_DEPL_IMPL(N)                                                                        \
    uint##N##_t expect_depl##N(uint##N##_t bits, uint##N##_t mask) {                               \
        uint##N##_t res = 0;                                                                       \
        int k = 0;                                                                                 \
                                                                                                   \
        for (int i = 0; i < BITS##N; ++i)                                                          \
            if (mask >> i & 0x1)                                                                   \
                res |= (bits >> k++ & 0x1) << i;                                                   \
                                                                                                   \
        return res;                                                                                \
    }
TEMPLATE_STD(EXPECT_DEPL_IMPL)

#define EXPECT_TRANS_IMPL(N)                                                    \
    uint##N##_t expect_trans##N(uint##N##_t bits, int rows) {                   \
        int cols = N / rows;                                                    \
        for(int i = 0; i < rows * cols; i++) {                                  \
            int j = i;                                                          \
            do                                                                  \
                j = (j % rows) * cols + (j / rows);                             \
            while(j < i);                                                       \
            bits = bswap##N(bits, i, j);                                        \
        }                                                                       \
        return bits;                                                            \
    }
TEMPLATE_STD(EXPECT_TRANS_IMPL)
