#include <stdio.h>
#include "../util/print.h"

#include <stdint.h>
#include <stdlib.h>

#include "test_funcs.h"
#include "serial.h"
#include "test_suite.h"

#include "../bits.h"
#include "../inc/N.h"

extern size_t NR;
extern size_t NT;

// NB: Tests for functions that return 'int' are storing results as 'uint' and
// using the unsigned versions for comparisons. But this is happening for both
// the library and naive implementations so conversions ought to be consistent.

#define TEST_FN(func, IMPL)                                                                        \
    TEST_FUNC_HEAD(#func, func)                                                                    \
        TEMPLATE_STD_TEST(IMPL, func)                                                              \
    TEST_FUNC_FOOT()

#define TEST_FN_IFN(func, ifunc, IMPL)                                                             \
    TEST_FUNC_HEAD(#func, func)                                                                    \
        TEMPLATE_STD_TEST_INV(IMPL, func, ifunc)                                                   \
    TEST_FUNC_FOOT()

#define TEST_ALL_CASES(N, func, TESTS)                                                             \
    TEST_IMPL_HEAD(N)                                                                              \
        uint##N##_t test_case;                                                                     \
        {                                                                                          \
            FOREACH_TEST_CASE(N)                                                                   \
                TESTS(N, func)                                                                     \
            END_FOREACH                                                                            \
        } {                                                                                        \
            FOREACH_POWER_CASE(N)                                                                  \
                TESTS(N, func)                                                                     \
            END_FOREACH                                                                            \
        } {                                                                                        \
            FOREACH_RAND_CASE(N)                                                                   \
                TESTS(N, func)                                                                     \
            END_FOREACH                                                                            \
        }                                                                                          \
    TEST_IMPL_FOOT()

#define TEST_ALL_CASES_INV(N, func, ifunc, TESTS)                                                  \
    TEST_IMPL_HEAD(N)                                                                              \
        uint##N##_t test_case;                                                                     \
        {                                                                                          \
            FOREACH_TEST_CASE(N)                                                                   \
                TESTS(N, func, ifunc)                                                              \
            END_FOREACH                                                                            \
        } {                                                                                        \
            FOREACH_POWER_CASE(N)                                                                  \
                TESTS(N, func, ifunc)                                                              \
            END_FOREACH                                                                            \
        } {                                                                                        \
            FOREACH_RAND_CASE(N)                                                                   \
                TESTS(N, func, ifunc)                                                              \
            END_FOREACH                                                                            \
        }                                                                                          \
    TEST_IMPL_FOOT()

#define TEST_FUNC_HEAD(name, func)                                                                 \
    void test_##func(void) {                                                                       \
        init_test(name);

#define TEST_FUNC_FOOT()                                                                           \
        term_test();                                                                               \
    }

#define TEST_IMPL_HEAD(N)                                                                          \
    {                                                                                              \
        init_width(N);

#define TEST_IMPL_FOOT()                                                                           \
        term_width();                                                                              \
    }

#define FOREACH_TEST_CASE(N)                                                                       \
    for (size_t ti = 0; ti < NT; ++ti) {                                                           \
        test_case = T##N[ti];

#define FOREACH_PAIR_CASE(N)                                                                       \
    uint##N##_t test_pair;                                                                         \
    for (size_t tj = 0; tj < NT; ++tj) {                                                           \
        test_pair = T##N[tj];

#define FOREACH_POWER_CASE(N)                                                                      \
    for (size_t tk = 0; tk < N; ++tk) {                                                            \
        test_case = P##N[tk];

#define FOREACH_TEST_MASK(N)                                                                       \
    uint##N##_t test_mask;                                                                         \
    for (size_t tm = 0; tm < NT; ++tm) {                                                           \
        test_mask = T##N[tm];

#define FOREACH_RAND_CASE(N)                                                                       \
    for (size_t tr = 0; tr < NR; ++tr) {                                                           \
        test_case = R##N[tr];

#define END_FOREACH }

#define CHECK_CALC(N, func)                                                                        \
    uint##N##_t serial, actual;                                                                    \
    serial = serial_##func##N(test_case);                                                          \
    actual = func##N(test_case);                                                                   \
    check##N##_impl(#func, test_case, serial, actual);

#define CHECK_CALC_PAIR(N, func)                                                                   \
    uint##N##_t serial, actual;                                                                    \
    serial = serial_##func##N(test_case, test_pair);                                               \
    actual = func##N(test_case, test_pair);                                                        \
    check##N##_impl(#func, test_case, serial, actual);

#define CHECK_INV(N, func, ifunc)                                                                  \
    uint##N##_t actual, invert;                                                                    \
    actual = func##N(test_case);                                                                   \
    invert = ifunc##N(actual);                                                                     \
    check##N##_inv(#func, #ifunc, test_case, invert);

#define CHECK_PERM(N, func)                                                                        \
    uint##N##_t serial, actual;                                                                    \
    actual = func##N(test_case);                                                                   \
    check##N##_perm_assert(#func, test_case, actual);                                              \
    serial = serial_##func##N(test_case);                                                          \
    check##N##_impl(#func, test_case, serial, actual);

#define CHECK_PERM_INV(N, func, ifunc)                                                             \
    uint##N##_t serial, actual, invert;                                                            \
    actual = func##N(test_case);                                                                   \
    check##N##_perm_assert(#func, test_case, actual);                                              \
    serial = serial_##func##N(test_case);                                                          \
    check##N##_impl(#func, test_case, serial, actual);                                             \
    invert = ifunc##N(actual);                                                                     \
    check##N##_perm_assert(#ifunc, actual, invert);                                                \
    serial = serial_##ifunc##N(actual);                                                            \
    check##N##_impl(#ifunc, actual, serial, invert);                                               \
    check##N##_inv(#func, #ifunc, test_case, invert);

#define CHECK_PERM_MASK(N, func)                                                                   \
    uint##N##_t serial, actual;                                                                    \
    actual = func##N(test_case, test_mask);                                                        \
    check##N##_perm_assert(#func, test_case, actual);                                              \
    serial = serial_##func##N(test_case, test_mask);                                               \
    check##N##_impl(#func, test_case, serial, actual);

#define CHECK_PERM_MASK_INV(N, func, ifunc)                                                        \
    uint##N##_t serial, actual, invert;                                                            \
    actual = func##N(test_case, test_mask);                                                        \
    check##N##_perm_assert(#func, test_case, actual);                                              \
    serial = serial_##func##N(test_case, test_mask);                                               \
    check##N##_impl(#func, test_case, serial, actual);                                             \
    invert = ifunc##N(actual, test_mask);                                                          \
    check##N##_perm_assert(#ifunc, actual, invert);                                                \
    serial = serial_##ifunc##N(actual, test_mask);                                                 \
    check##N##_impl(#ifunc, actual, serial, invert);                                               \
    check##N##_inv(#func, #ifunc, test_case, invert);

#define CHECK_MANI_INV(N, func, ifunc)                                                             \
    uint##N##_t serial, actual, invert;                                                            \
    actual = func##N(test_case);                                                                   \
    serial = serial_##func##N(test_case);                                                          \
    check##N##_impl(#func, test_case, serial, actual);                                             \
    invert = ifunc##N(actual);                                                                     \
    serial = serial_##ifunc##N(test_case);                                                         \
    check##N##_impl(#func, actual, serial, invert);                                                \
    check##N##_inv(#func, #ifunc, test_case, invert);

#define CHECK_MANI_MASK(N, func)                                                                   \
    uint##N##_t serial, actual;                                                                    \
    actual = func##N(test_case, test_mask);                                                        \
    serial = serial_##func##N(test_case, test_mask);                                               \
    check##N##_impl(#func, test_case, serial, actual);

#define CHECK_MANI_MASK_INV(N, func, ifunc)                                                        \
    uint##N##_t serial, actual;                                                                    \
    actual = func##N(test_case, test_mask);                                                        \
    serial = serial_##func##N(test_case, test_mask);                                               \
    check##N##_impl(#func, test_case, serial, actual);                                             \
    invert = ifunc##N(actual, test_mask);                                                          \
    serial = serial_##ifunc##N(actual, test_mask);                                                 \
    check##N##_impl(#ifunc, actual, serial, invert);                                               \
    check##N##_inv(#func, #ifunc, test_case, invert);

#define CALC_TEST(N, func) CHECK_CALC(N, func)
#define TEST_CALC(N, func) TEST_ALL_CASES(N, func, CALC_TEST)

#define CALC_PAIR_TEST(N, func)                                                                    \
    FOREACH_PAIR_CASE(N)                                                                           \
        CHECK_CALC_PAIR(N, func)                                                                   \
    END_FOREACH
#define TEST_CALC_PAIR(N, func) TEST_ALL_CASES(N, func, CALC_PAIR_TEST)

#define INV_TEST(N, func, ifunc) CHECK_INV(N, func, ifunc)
#define TEST_INV(N, func, ifunc) TEST_ALL_CASES_INV(N, func, ifunc, INV_TEST)

#define PERM_TEST(N, func) CHECK_PERM(N, func)
#define TEST_PERM(N, func) TEST_ALL_CASES(N, func, PERM_TEST)

#define PERM_INV_TEST(N, func, ifunc) CHECK_PERM_INV(N, func, ifunc)
#define TEST_PERM_INV(N, func, ifunc) TEST_ALL_CASES_INV(N, func, ifunc, PERM_INV_TEST)

#define PERM_MASK_INV_TEST(N, func, ifunc)                                                         \
    FOREACH_TEST_MASK(N)                                                                           \
        CHECK_PERM_MASK_INV(N, func, ifunc)                                                        \
    END_FOREACH
#define TEST_PERM_MASK_INV(N, func, ifunc) TEST_ALL_CASES_INV(N, func, ifunc, PERM_MASK_INV_TEST)

#define MANI_MASK_TEST(N, func)                                                                    \
    FOREACH_TEST_MASK(N)                                                                           \
        CHECK_MANI_MASK(N, func)                                                                   \
    END_FOREACH
#define TEST_MANI_MASK(N, func) TEST_ALL_CASES(N, func, MANI_MASK_TEST)

#define MANI_MASK_INV_TEST(N, func, ifunc)                                                         \
    FOREACH_TEST_MASK(N)                                                                           \
        CHECK_MANI_MASK_INV(N, func, ifunc)                                                        \
    END_FOREACH
#define TEST_MANI_MASK_INV(func, ifunc) TEST_ALL_CASES_INV(N, func, ifunc, MANI_MASK_INV_TEST)

#define TRANS_PERM_TEST(N, func)                                                                   \
    for (int rows = 1; rows <= N; rows <<= 1) {                                                    \
        uint##N##_t serial, actual, invert;                                                        \
        actual = func##N(test_case, rows);                                                         \
        check##N##_perm_assert(#func, test_case, actual);                                          \
        serial = serial_##func##N(test_case, rows);                                                \
        check##N##_impl(#func, test_case, serial, actual);                                         \
        invert = func##N(actual, N / rows);                                                        \
        check##N##_perm_assert(#func, actual, invert);                                             \
        serial = serial_##func##N(actual, N / rows);                                               \
        check##N##_impl(#func, actual, serial, invert);                                            \
        check##N##_inv(#func, #func, test_case, invert);                                           \
    }
#define TEST_TRANS_PERM(N, func) TEST_ALL_CASES(N, func, TRANS_PERM_TEST)

#define OMFLIP_PERM_TEST(N, func)                                                                  \
    const uint##N##_t flip_mask = NEG##N >> (BITS##N >> 1);                                        \
    uint##N##_t mirror_mask, invert, actual, serial;                                               \
    FOREACH_TEST_MASK(N)                                                                           \
        for (uint8_t ctrl = 0; ctrl < 4; ++ctrl) {                                                 \
            mirror_mask = (test_mask & flip_mask) | ((test_mask & flip_mask) << (BITS##N >> 1));   \
            actual = omflip##N(test_case, mirror_mask, ctrl);                                      \
            check##N##_perm_assert(#func, test_case, actual);                                      \
            serial = serial_omflip##N(test_case, mirror_mask, ctrl);                               \
            check##N##_impl(#func, test_case, serial, actual);                                     \
            invert = omflip##N(actual, mirror_mask, ~ctrl);                                        \
            check##N##_perm_assert(#func, actual, invert);                                         \
            check##N##_inv(#func, #func, test_case, invert);                                       \
        }                                                                                          \
    END_FOREACH
#define TEST_OMFLIP_PERM(N, func) TEST_ALL_CASES(N, func, OMFLIP_PERM_TEST)

#define ROT_PERM_TEST(N, func)                                                                     \
    uint##N##_t serial, actual;                                                                    \
    for (int rot = 0; rot < N; ++rot) {                                                            \
        actual = func##N(test_case, rot);                                                          \
        check##N##_perm_assert(#func, test_case, actual);                                          \
        serial = serial_##func##N(test_case, rot);                                                 \
        check##N##_impl(#func, test_case, serial, actual);                                         \
    }
#define TEST_ROT_PERM(N, func) TEST_ALL_CASES(N, func, ROT_PERM_TEST)

#define BSWAP_PERM_TEST(N, func)                                                                   \
    uint##N##_t serial, actual;                                                                    \
    for (int bi = 0; bi < N; ++bi) {                                                               \
        for (int bj = bi; bj < N; ++bj) {                                                          \
            actual = func##N(test_case, bi, bj);                                                   \
            check##N##_perm_assert(#func, test_case, actual);                                      \
            serial = serial_##func##N(test_case, bi, bj);                                          \
            check##N##_impl(#func, test_case, serial, actual);                                     \
        }                                                                                          \
    }
#define TEST_BSWAP_PERM(N, func) TEST_ALL_CASES(N, func, BSWAP_PERM_TEST)

#define RSWAP_PERM_TEST(N, func)                                                                   \
    uint##N##_t serial, actual;                                                                    \
    for (int bi = 0; bi < N; ++bi) {                                                               \
        for (int bj = bi; bj < N; ++bj) {                                                          \
            int max = (bj - bi) < (BITS##N - bj + 1) ? (bj  - bi) : (BITS##N - bj + 1);            \
            for (int bk = 1; bk < max; ++bk) {                                                     \
                actual = func##N(test_case, bi, bj, bk);                                           \
                check##N##_perm_assert(#func, test_case, actual);                                  \
                serial = serial_##func##N(test_case, bi, bj, bk);                                  \
                check##N##_impl(#func, test_case, serial, actual);                                 \
            }                                                                                      \
        }                                                                                          \
    }
#define TEST_RSWAP_PERM(N, func) TEST_ALL_CASES(N, func, RSWAP_PERM_TEST)

TEST_FN(pop, TEST_CALC)
TEST_FN(par, TEST_CALC)
TEST_FN(ctz, TEST_CALC)
TEST_FN(clz, TEST_CALC)
TEST_FN(mxset, TEST_CALC)
TEST_FN(mnset, TEST_CALC)
TEST_FN(lb, TEST_CALC)
TEST_FN(ipow, TEST_CALC)
TEST_FN(cpow, TEST_CALC)
TEST_FN(fpow, TEST_CALC)
TEST_FN(lsb, TEST_CALC)
TEST_FN(msb, TEST_CALC)

TEST_FN(max, TEST_CALC_PAIR)
TEST_FN(min, TEST_CALC_PAIR)
TEST_FN(gcd, TEST_CALC_PAIR)

TEST_FN_IFN(rev, rev, TEST_PERM_INV)
TEST_FN_IFN(shuf, ishuf, TEST_PERM_INV)
TEST_FN_IFN(bfly, ibfly, TEST_PERM_MASK_INV)

TEST_FN(extr, TEST_MANI_MASK)
TEST_FN(depl, TEST_MANI_MASK)
TEST_FN(extl, TEST_MANI_MASK)
TEST_FN(depr, TEST_MANI_MASK)

TEST_FN_IFN(gray, igray, TEST_INV)
TEST_FN_IFN(lfsr, ilfsr, TEST_INV)
TEST_FN_IFN(grp, igrp, TEST_PERM_MASK_INV)

TEST_FN(trans, TEST_TRANS_PERM)
TEST_FN(omflip, TEST_OMFLIP_PERM)
TEST_FN(rol, TEST_ROT_PERM)
TEST_FN(ror, TEST_ROT_PERM)
TEST_FN(bswap, TEST_BSWAP_PERM)
TEST_FN(rswap, TEST_RSWAP_PERM)
