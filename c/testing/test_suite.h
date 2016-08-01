#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include "../bits.h"
#include "../inc/extint.h"
#include "../inc/N.h"
#include "../util/print.h"

#define DISPLAY_DIFF_OFF false
#define DISPLAY_DIFF_ON  true

void init_suite(bool log);
void init_test(const char* name);
void init_width();
void term_width(void);
void term_test(void);
void term_suite(void);

#define TEST_SUITE_DECLARATIONS(N)                                                                                          \
    uint##N##_t* T##N;                                                                                                      \
    uint##N##_t* P##N;                                                                                                      \
    uint##N##_t* R##N;                                                                                                      \
    void check##N##_impl(const char* fn, uint##N##_t input, uint##N##_t serial, uint##N##_t actual);                        \
    void check##N##_impl_mask(const char* fn, uint##N##_t input, uint##N##_t mask, uint##N##_t serial, uint##N##_t actual); \
    void check##N##_inv(const char* fn, const char* ifn, uint##N##_t input, uint##N##_t actual);                            \
    void check##N##_inv_mask(const char* fn, const char* ifn, uint##N##_t input, uint##N##_t mask, uint##N##_t actual);     \
    void check##N##_perm_assert(const char* fn, uint##N##_t input, uint##N##_t output);                                     \
    void check##N##_perm_assert_mask(const char* fn, uint##N##_t input, uint##N##_t mask, uint##N##_t output);
TEMPLATE_STD(TEST_SUITE_DECLARATIONS)

/*
// There are two macros that can automatically build a test function:
//     TEST_FN(fn, test)          : to test a function
//     TEST_FN_IFN(fn, ifn, test) : to test an invertible function
//
// Test macro paramters:
//     fn   : the function to test
//     ifn  : the inverse of the function fn
//     test : one of the standard tests below, or a custom one (see TEST_TRANS_PERM for example)
//
// Standard tests:
//     TEST_CALC          : for calculation functions
//     TEST_CALC_PAIR     : for calculation functions that require a pair of inputs
//     TEST_PERM          : for permutation functions
//     TEST_PERM_INV      : for invertible permutation functions
//     TEST_PERM_MASK_INV : for invertible permutation functions that require a mask
//     TEST_MANI_MASK     : for manipulation functions that require a mask
//     TEST_MANI_MASK_INV : for invertible manipulation functions that require a mask
//     TEST_INV           : for invertible functions
*/

extern size_t NT;   // the number of pre-selected test values
extern size_t NR;   // the number of random test values

// NB: Tests for functions that return 'int' (calculation functions) are storing
//     results as 'uint' and using the unsigned versions for comparisons. But
//     this is happening for both the library and naive implementations so
//     conversions ought to be consistent.

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
    uint##N##_t actual, serial;                                                                    \
    serial = serial_##func##N(test_case);                                                          \
    actual = func##N(test_case);                                                                   \
    check##N##_impl(#func, test_case, serial, actual);

#define CHECK_CALC_PAIR(N, func)                                                                   \
    uint##N##_t actual, serial;                                                                    \
    serial = serial_##func##N(test_case, test_pair);                                               \
    actual = func##N(test_case, test_pair);                                                        \
    check##N##_impl(#func, test_case, serial, actual);

#define CHECK_INV(N, func, ifunc)                                                                  \
    uint##N##_t actual, invert;                                                                    \
    actual = func##N(test_case);                                                                   \
    invert = ifunc##N(actual);                                                                     \
    check##N##_inv(#func, #ifunc, test_case, invert);

#define CHECK_PERM(N, func)                                                                        \
    uint##N##_t actual, serial;                                                                    \
    actual = func##N(test_case);                                                                   \
    check##N##_perm_assert(#func, test_case, actual);                                              \
    serial = serial_##func##N(test_case);                                                          \
    check##N##_impl(#func, test_case, serial, actual);

#define CHECK_PERM_INV(N, func, ifunc)                                                             \
    uint##N##_t actual, serial, invert;                                                            \
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
    uint##N##_t actual, serial;                                                                    \
    actual = func##N(test_case, test_mask);                                                        \
    check##N##_perm_assert_mask(#func, test_case, test_mask, actual);                              \
    serial = serial_##func##N(test_case, test_mask);                                               \
    check##N##_impl_mask(#func, test_case, test_mask, serial, actual);

#define CHECK_PERM_MASK_INV(N, func, ifunc)                                                        \
    uint##N##_t actual, serial, invert;                                                            \
    actual = func##N(test_case, test_mask);                                                        \
    check##N##_perm_assert_mask(#func, test_case, test_mask, actual);                              \
    serial = serial_##func##N(test_case, test_mask);                                               \
    check##N##_impl_mask(#func, test_case, test_mask, serial, actual);                             \
    invert = ifunc##N(actual, test_mask);                                                          \
    check##N##_perm_assert_mask(#ifunc, actual, test_mask, invert);                                \
    serial = serial_##ifunc##N(actual, test_mask);                                                 \
    check##N##_impl_mask(#ifunc, actual, test_mask, serial, invert);                               \
    check##N##_inv_mask(#func, #ifunc, test_case, test_mask, invert);

#define CHECK_MANI_INV(N, func, ifunc)                                                             \
    uint##N##_t actual, serial, invert;                                                            \
    actual = func##N(test_case);                                                                   \
    serial = serial_##func##N(test_case);                                                          \
    check##N##_impl(#func, test_case, serial, actual);                                             \
    invert = ifunc##N(actual);                                                                     \
    serial = serial_##ifunc##N(test_case);                                                         \
    check##N##_impl(#func, actual, serial, invert);                                                \
    check##N##_inv(#func, #ifunc, test_case, invert);

#define CHECK_MANI_MASK(N, func)                                                                   \
    uint##N##_t actual, serial;                                                                    \
    actual = func##N(test_case, test_mask);                                                        \
    serial = serial_##func##N(test_case, test_mask);                                               \
    check##N##_impl_mask(#func, test_case, test_mask, serial, actual);

#define CHECK_MANI_MASK_INV(N, func, ifunc)                                                        \
    uint##N##_t actual, serial;                                                                    \
    actual = func##N(test_case, test_mask);                                                        \
    serial = serial_##func##N(test_case, test_mask);                                               \
    check##N##_impl_mask(#func, test_case, test_mask, serial, actual);                             \
    invert = ifunc##N(actual, test_mask);                                                          \
    serial = serial_##ifunc##N(actual, test_mask);                                                 \
    check##N##_impl_mask(#ifunc, actual, test_mask, serial, invert);                               \
    check##N##_inv_mask(#func, #ifunc, test_case, test_mask, invert);

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

// Non-standard custom tests

#define TRANS_PERM_TEST(N, func)                                                                   \
    for (int rows = 1; rows <= N; rows <<= 1) {                                                    \
        uint##N##_t actual, serial, invert;                                                        \
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
    uint##N##_t actual, serial;                                                                    \
    for (int rot = 0; rot < N; ++rot) {                                                            \
        actual = func##N(test_case, rot);                                                          \
        check##N##_perm_assert(#func, test_case, actual);                                          \
        serial = serial_##func##N(test_case, rot);                                                 \
        check##N##_impl(#func, test_case, serial, actual);                                         \
    }
#define TEST_ROT_PERM(N, func) TEST_ALL_CASES(N, func, ROT_PERM_TEST)

#define BSWAP_PERM_TEST(N, func)                                                                   \
    uint##N##_t actual, serial;                                                                    \
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
    uint##N##_t actual, serial;                                                                    \
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

#endif // TEST_H
