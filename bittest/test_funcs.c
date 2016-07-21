#include <stdio.h>
#include "../util/print.h"

#include <stdint.h>
#include <stdlib.h>

#include "test_expect.h"
#include "test_funcs.h"
#include "test_suite.h"

#include "../bits.h"
#include "../inc/N.h"

// NB: Tests for functions that return 'int' are storing results as 'uint' and
// using the unsigned versions for comparisons. But this is happening for both
// the library and naive implementations so conversions ought to be consistent.

#define TEST_COMMON(IMPL, name, func)                                          \
    TEST_FUNC_HEAD(name, func)                                                 \
        TEMPLATE_STD_TEST(IMPL, func)                                          \
    TEST_FUNC_FOOT()

#define TEST_COMMON_INV(IMPL, name, func, ifunc)                               \
    TEST_FUNC_HEAD(name, func)                                                 \
        TEMPLATE_STD_TEST_INV(IMPL, func, ifunc)                               \
    TEST_FUNC_FOOT()

#define TEST_FUNC_HEAD(name, func)                                             \
    void test_##func(void) {                                                   \
        init_test(name);

#define TEST_FUNC_FOOT()                                                       \
        term_test();                                                           \
    }

#define TEST_IMPL_HEAD(N)                                                      \
    {                                                                          \
        init_width(N);

#define TEST_IMPL_FOOT                                                         \
        term_width();                                                          \
    }

#define FOREACH_TEST_CASE(N)                                                   \
    for (size_t ti = 0; ti < NT; ++ti) {                                       \
        test_case = T##N[ti];

#define FOREACH_PAIR_CASE(N)                                                   \
    for (size_t tj = 0; tj < NT; ++tj) {                                       \
        test_pair = T##N[tj];

#define FOREACH_POWER_CASE(N)                                                  \
    for (size_t tk = 0; tk < N; ++tk) {                                        \
        test_case = P##N[tk];

#define FOREACH_TEST_MASK(N)                                                   \
    for (size_t tm = 0; tm < NT; ++tm) {                                       \
        test_mask = T##N[tm];

#define FOREACH_RAND_CASE(N)                                                   \
    for (size_t tr = 0; tr < NR; ++tr) {                                       \
        test_case = R##N[tr];

#define END_FOREACH }

#define CHECK_CALC(N, func)                                                    \
    expect = expect_##func##N(test_case);                                      \
    actual = func##N(test_case);                                               \
    check##N##_impl(#func, test_case, expect, actual);

#define CHECK_CALC_PAIR(N, func)                                               \
    expect = expect_##func##N(test_case, test_pair);                           \
    actual = func##N(test_case, test_pair);                                    \
    check##N##_impl(#func, test_case, expect, actual);

#define CHECK_PERM(N, func)                                                    \
    expect = expect_##func##N(test_case);                                      \
    check##N##_perm_assert(#func, test_case, expect);                          \
    actual = func##N(test_case);                                               \
    check##N##_impl(#func, test_case, expect, actual);

#define CHECK_PERM_INV(N, func, ifunc)                                         \
    expect = expect_##ifunc##N(actual);                                        \
    check##N##_perm_assert(#ifunc, actual, expect);                            \
    invert = ifunc##N(actual);                                                 \
    check##N##_impl(#ifunc, test_case, expect, invert);                        \
    check##N##_inv(#func, #ifunc, test_case, invert);

#define CHECK_PERM_MASK(N, func)                                               \
    expect = expect_##func##N(test_case, test_mask);                           \
    check##N##_perm_assert(#func, test_case, expect);                          \
    actual = func##N(test_case, test_mask);                                    \
    check##N##_impl(#func, test_case, expect, actual);

#define CHECK_PERM_MASK_INV(N, func, ifunc)                                    \
    expect = expect_##ifunc##N(actual, test_mask);                             \
    check##N##_perm_assert(#ifunc, actual, expect);                            \
    invert = ifunc##N(actual, test_mask);                                      \
    check##N##_impl(#ifunc, test_case, expect, invert);                        \
    check##N##_inv(#func, #ifunc, test_case, invert);

#define CHECK_MANI_MASK(N, func)                                               \
    actual = func##N(test_case, test_mask);                                    \
    expect = expect_##func##N(test_case, test_mask);                           \
    check##N##_impl(#func, test_case, expect, actual);

#define CHECK_MANI_MASK_INV(N, func, ifunc)                                    \
    invert = ifunc##N(actual, test_mask);                                      \
    expect = expect_##ifunc##N(actual, test_mask);                             \
    check##N##_impl(#ifunc, test_case, expect, invert);                        \
    check##N##_inv(#func, #ifunc, test_case, invert);

#define TEST_CALC_IMPL(N, func)                                                \
    TEST_IMPL_HEAD(N)                                                          \
        uint##N##_t test_case, expect, actual;                                 \
        FOREACH_TEST_CASE(N)                                                   \
            CHECK_CALC(N, func)                                                \
        END_FOREACH                                                            \
        FOREACH_POWER_CASE(N)                                                  \
            CHECK_CALC(N, func)                                                \
        END_FOREACH                                                            \
        FOREACH_RAND_CASE(N)                                                   \
            CHECK_CALC(N, func)                                                \
        END_FOREACH                                                            \
    TEST_IMPL_FOOT

#define TEST_CALC(func)                                                        \
    TEST_COMMON(TEST_CALC_IMPL, #func, func)

#define TEST_CALC_PAIR_IMPL(N, func)                                           \
    TEST_IMPL_HEAD(N)                                                          \
        uint##N##_t test_case, test_pair, expect, actual;                      \
        FOREACH_TEST_CASE(N)                                                   \
            FOREACH_PAIR_CASE(N)                                               \
                CHECK_CALC_PAIR(N, func)                                       \
            END_FOREACH                                                        \
        END_FOREACH                                                            \
        FOREACH_POWER_CASE(N)                                                  \
            FOREACH_PAIR_CASE(N)                                               \
                CHECK_CALC_PAIR(N, func)                                       \
            END_FOREACH                                                        \
        END_FOREACH                                                            \
        FOREACH_RAND_CASE(N)                                                   \
            FOREACH_PAIR_CASE(N)                                               \
                CHECK_CALC_PAIR(N, func)                                       \
            END_FOREACH                                                        \
        END_FOREACH                                                            \
    TEST_IMPL_FOOT

#define TEST_CALC_PAIR(func)                                                   \
    TEST_COMMON(TEST_CALC_PAIR_IMPL, #func, func)

#define TEST_PERM_IMPL(N, func)                                                \
    TEST_IMPL_HEAD(N)                                                          \
        uint##N##_t test_case, expect, actual;                                 \
        FOREACH_TEST_CASE(N)                                                   \
            CHECK_PERM(N, func)                                                \
        END_FOREACH                                                            \
        FOREACH_POWER_CASE(N)                                                  \
            CHECK_PERM(N, func)                                                \
        END_FOREACH                                                            \
        FOREACH_RAND_CASE(N)                                                   \
            CHECK_PERM(N, func)                                                \
        END_FOREACH                                                            \
    TEST_IMPL_FOOT

#define TEST_PERM(func)                                                        \
    TEST_COMMON(TEST_PERM_IMPL, #func, func)

#define TEST_PERM_INV_IMPL(N, func, ifunc)                                     \
    TEST_IMPL_HEAD(N)                                                          \
        uint##N##_t test_case, expect, actual, invert;                         \
        FOREACH_TEST_CASE(N)                                                   \
            CHECK_PERM(N, func)                                                \
            CHECK_PERM_INV(N, func, ifunc)                                     \
        END_FOREACH                                                            \
        FOREACH_POWER_CASE(N)                                                  \
            CHECK_PERM(N, func)                                                \
            CHECK_PERM_INV(N, func, ifunc)                                     \
        END_FOREACH                                                            \
        FOREACH_RAND_CASE(N)                                                   \
            CHECK_PERM(N, func)                                                \
            CHECK_PERM_INV(N, func, ifunc)                                     \
        END_FOREACH                                                            \
    TEST_IMPL_FOOT

#define TEST_PERM_INV(func, ifunc)                                             \
    TEST_COMMON_INV(TEST_PERM_INV_IMPL, #func, func, ifunc)

#define TEST_PERM_MASK_INV_IMPL(N, func, ifunc)                                \
    TEST_IMPL_HEAD(N)                                                          \
        uint##N##_t test_case, test_mask, expect, actual, invert;              \
        FOREACH_TEST_CASE(N)                                                   \
            FOREACH_TEST_MASK(N)                                               \
                CHECK_PERM_MASK(N, func)                                       \
                CHECK_PERM_MASK_INV(N, func, ifunc)                            \
            END_FOREACH                                                        \
        END_FOREACH                                                            \
        FOREACH_POWER_CASE(N)                                                  \
            FOREACH_TEST_MASK(N)                                               \
                CHECK_PERM_MASK(N, func)                                       \
                CHECK_PERM_MASK_INV(N, func, ifunc)                            \
            END_FOREACH                                                        \
        END_FOREACH                                                            \
        FOREACH_RAND_CASE(N)                                                   \
            FOREACH_TEST_MASK(N)                                               \
                CHECK_PERM_MASK(N, func)                                       \
                CHECK_PERM_MASK_INV(N, func, ifunc)                            \
            END_FOREACH                                                        \
        END_FOREACH                                                            \
    TEST_IMPL_FOOT

#define TEST_PERM_MASK_INV(func, ifunc)                                        \
    TEST_COMMON_INV(TEST_PERM_MASK_INV_IMPL, #func, func, ifunc)

#define TEST_MANI_MASK_IMPL(N, func)                                           \
    TEST_IMPL_HEAD(N)                                                          \
        uint##N##_t test_case, test_mask, actual, expect;                      \
        FOREACH_TEST_CASE(N)                                                   \
            FOREACH_TEST_MASK(N)                                               \
                CHECK_MANI_MASK(N, func)                                       \
            END_FOREACH                                                        \
        END_FOREACH                                                            \
        FOREACH_POWER_CASE(N)                                                  \
            FOREACH_TEST_MASK(N)                                               \
                CHECK_MANI_MASK(N, func)                                       \
            END_FOREACH                                                        \
        END_FOREACH                                                            \
        FOREACH_RAND_CASE(N)                                                   \
            FOREACH_TEST_MASK(N)                                               \
                CHECK_MANI_MASK(N, func)                                       \
            END_FOREACH                                                        \
        END_FOREACH                                                            \
    TEST_IMPL_FOOT

#define TEST_MANI_MASK(func)                                                   \
    TEST_COMMON(TEST_MANI_MASK_IMPL, #func, func)

#define TEST_MANI_MASK_INV_IMPL(N, func, ifunc)                                \
    TEST_IMPL_HEAD(N)                                                          \
        uint##N##_t test_case, test_mask, expect, actual, invert;              \
        FOREACH_TEST_CASE(N)                                                   \
            FOREACH_TEST_MASK(N)                                               \
                CHECK_MANI_MASK(N, func)                                       \
                CHECK_MANI_MASK_INV(N, func, ifunc)                            \
            END_FOREACH                                                        \
        END_FOREACH                                                            \
        FOREACH_POWER_CASE(N)                                                  \
            FOREACH_TEST_MASK(N)                                               \
                CHECK_MANI_MASK(N, func)                                       \
                CHECK_MANI_MASK_INV(N, func, ifunc)                            \
            END_FOREACH                                                        \
        END_FOREACH                                                            \
        FOREACH_RAND_CASE(N)                                                   \
            FOREACH_TEST_MASK(N)                                               \
                CHECK_MANI_MASK(N, func)                                       \
                CHECK_MANI_MASK_INV(N, func, ifunc)                            \
            END_FOREACH                                                        \
        END_FOREACH                                                            \
    TEST_IMPL_FOOT

#define TEST_MANI_MASK_INV(func, ifunc)                                                            \
    TEST_COMMON_INV(TEST_MANI_MASK_INV_IMPL, #func, func, ifunc)

#define TEST_ALL_CASES(N, func, TESTS)                                                             \
    TEST_IMPL_HEAD(N)                                                                              \
        {                                                                                          \
            uint##N##_t test_case, expect, actual;                                                 \
            FOREACH_TEST_CASE(N)                                                                   \
                TESTS(N, func)                                                                     \
            END_FOREACH                                                                            \
        } {                                                                                        \
            uint##N##_t test_case, expect, actual;                                                 \
            FOREACH_POWER_CASE(N)                                                                  \
                TESTS(N, func)                                                                     \
            END_FOREACH                                                                            \
        } {                                                                                        \
            uint##N##_t test_case, expect, actual;                                                 \
            FOREACH_RAND_CASE(N)                                                                   \
                TESTS(N, func)                                                                     \
            END_FOREACH                                                                            \
        }                                                                                          \
    TEST_IMPL_FOOT

#define TEST_CUSTOM(func, IMPL)                                                                    \
    TEST_FUNC_HEAD(#func, func)                                                                    \
        TEMPLATE_STD_TEST(IMPL, func)                                                              \
    TEST_FUNC_FOOT()

#define TEST_TRANS_PERM_TESTS(N, func)                                                             \
    for (int rows = 1; rows <= N; rows <<= 1) {                                                    \
        uint##N##_t invert;                                                                        \
        expect = expect_##func##N(test_case, rows);                                                \
        check##N##_perm_assert(#func, test_case, expect);                                          \
        actual = func##N(test_case, rows);                                                         \
        check##N##_impl(#func, test_case, expect, actual);                                         \
                                                                                                   \
        expect = expect_##func##N(actual, N / rows);                                               \
        check##N##_perm_assert(#func, actual, expect);                                             \
        invert = func##N(actual, N / rows);                                                        \
        check##N##_impl(#func, test_case, expect, invert);                                         \
        check##N##_inv(#func, #func, test_case, invert);                                           \
    }
#define TEST_TRANS_PERM(N, func) TEST_ALL_CASES(N, func, TEST_TRANS_PERM_TESTS)

#define TEST_OMFLIP_PERM_TESTS(N, func)                                                            \
    const uint##N##_t flip_mask = NEG##N >> (BITS##N >> 1);                                        \
    uint##N##_t test_mask, mirror_mask, invert;                                                    \
    FOREACH_TEST_MASK(N)                                                                           \
        for (uint8_t ctrl = 0; ctrl < 4; ++ctrl) {                                                 \
            mirror_mask = (test_mask & flip_mask) | ((test_mask & flip_mask) << (BITS##N >> 1));   \
            actual = omflip##N(test_case, mirror_mask, ctrl);                                      \
            check##N##_perm_assert("omflip", test_case, actual);                                   \
                                                                                                   \
            expect = expect_omflip##N(test_case, mirror_mask, ctrl);                               \
            check##N##_impl("omflip", test_case, expect, actual);                                  \
                                                                                                   \
            invert = omflip##N(actual, mirror_mask, ~ctrl);                                        \
            check##N##_perm_assert("omflip", actual, invert);                                      \
            check##N##_inv("omflip", "omflip", test_case, invert);                                 \
        }                                                                                          \
    END_FOREACH
#define TEST_OMFLIP_PERM(N, func) TEST_ALL_CASES(N, func, TEST_OMFLIP_PERM_TESTS)

#define TEST_ROT_PERM_TESTS(N, func)                                                               \
    for (int rot = 0; rot < N; ++rot) {                                                            \
        expect = expect_##func##N(test_case, rot);                                                 \
        check##N##_perm_assert(#func, test_case, expect);                                          \
        actual = func##N(test_case, rot);                                                          \
        check##N##_impl(#func, test_case, expect, actual);                                         \
    }
#define TEST_ROT_PERM(N, func) TEST_ALL_CASES(N, func, TEST_ROT_PERM_TESTS)

#define TEST_RSWAP_PERM_TESTS(N, func)                                                             \
    for (int bi = 0; bi < N; ++bi) {                                                               \
        for (int bj = bi; bj < N; ++bj) {                                                          \
            int max = (bj - bi) < (BITS##N - bj + 1) ? (bj  - bi) : (BITS##N - bj + 1);            \
            for (int bk = 1; bk < max; ++bk) {                                                     \
                expect = expect_##func##N(test_case, bi, bj, bk);                                  \
                check##N##_perm_assert(#func, test_case, expect);                                  \
                actual = func##N(test_case, bi, bj, bk);                                           \
                check##N##_impl(#func, test_case, expect, actual);                                 \
            }                                                                                      \
        }                                                                                          \
    }
#define TEST_RSWAP_PERM(N, func) TEST_ALL_CASES(N, func, TEST_RSWAP_PERM_TESTS)

#define TEST_BSWAP_PERM_TESTS(N, func)                                                             \
    for (int bi = 0; bi < N; ++bi) {                                                               \
        for (int bj = bi; bj < N; ++bj) {                                                          \
            expect = expect_##func##N(test_case, bi, bj);                                          \
            check##N##_perm_assert(#func, test_case, expect);                                      \
            actual = func##N(test_case, bi, bj);                                                   \
            check##N##_impl(#func, test_case, expect, actual);                                     \
        }                                                                                          \
    }
#define TEST_BSWAP_PERM(N, func) TEST_ALL_CASES(N, func, TEST_BSWAP_PERM_TESTS)

TEST_CALC(pop)
TEST_CALC(par)
TEST_CALC(ctz)
TEST_CALC(clz)
TEST_CALC(mxset)
TEST_CALC(mnset)
TEST_CALC(lb)
TEST_CALC(ipow)
TEST_CALC(cpow)
TEST_CALC(fpow)
TEST_CALC(lsb)
TEST_CALC(msb)
TEST_CALC_PAIR(max)
TEST_CALC_PAIR(min)
TEST_CALC_PAIR(gcd)
TEST_PERM_INV(rev, rev)
TEST_PERM_INV(shuf, ishuf)
TEST_PERM_MASK_INV(bfly, ibfly)
TEST_MANI_MASK(extr)
TEST_MANI_MASK(depl)
TEST_MANI_MASK(extl)
TEST_MANI_MASK(depr)
TEST_PERM_MASK_INV(grp, igrp)
TEST_CUSTOM(trans, TEST_TRANS_PERM)
TEST_CUSTOM(omflip, TEST_OMFLIP_PERM)
TEST_CUSTOM(rol, TEST_ROT_PERM)
TEST_CUSTOM(ror, TEST_ROT_PERM)
TEST_CUSTOM(bswap, TEST_BSWAP_PERM)
TEST_CUSTOM(rswap, TEST_RSWAP_PERM)
