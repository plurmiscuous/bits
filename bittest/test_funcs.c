#include <stdio.h>
#include "../util/print.h"

#include <stdint.h>
#include <stdlib.h>

#include "test_expect.h"
#include "test_funcs.h"
#include "test_suite.h"

#include "../bits.h"
#include "../inc/template.h"

// NB: Tests for functions that return 'int' are storing results as 'uint' and
// using the unsigned versions for comparisons. But this is happening for both
// the library and naive implementations so conversions ought to be consistent.

#define TEMPLATE_STD_TEST(TEST, func)                                          \
    TEST(  8, func)                                                            \
    TEST( 16, func)                                                            \
    TEST( 32, func)                                                            \
    TEST( 64, func)                                                            \
    TEST(128, func)                                                            \

#define TEMPLATE_STD_TEST_INV(TEST, func, ifunc)                               \
    TEST(  8, func, ifunc)                                                     \
    TEST( 16, func, ifunc)                                                     \
    TEST( 32, func, ifunc)                                                     \
    TEST( 64, func, ifunc)                                                     \
    TEST(128, func, ifunc)                                                     \

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

#define TEST_IMPL_FOOT()                                                       \
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
    TEST_IMPL_FOOT()

#define TEST_CALC(name, func)                                                  \
    TEST_COMMON(TEST_CALC_IMPL, name, func)

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
    TEST_IMPL_FOOT()

#define TEST_CALC_PAIR(name, func)                                             \
    TEST_COMMON(TEST_CALC_PAIR_IMPL, name, func)

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
    TEST_IMPL_FOOT()

#define TEST_PERM_INV(name, func, ifunc)                                       \
    TEST_COMMON_INV(TEST_PERM_INV_IMPL, name, func, ifunc)

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
    TEST_IMPL_FOOT()

#define TEST_PERM_MASK_INV(name, func, ifunc)                                  \
    TEST_COMMON_INV(TEST_PERM_MASK_INV_IMPL, name, func, ifunc)

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
    TEST_IMPL_FOOT()

#define TEST_MANI_MASK(name, func)                                             \
    TEST_COMMON(TEST_MANI_MASK_IMPL, name, func)

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
    TEST_IMPL_FOOT()

#define TEST_MANI_MASK_INV(name, func, ifunc)                                  \
    TEST_COMMON_INV(TEST_MANI_MASK_INV_IMPL, name, func, ifunc)

#define TEST_PERM_CUSTOM(name, func, IMPL)                                          \
    TEST_FUNC_HEAD(name, func)                                                 \
        TEMPLATE_STD_TEST(IMPL, func)                                          \
    TEST_FUNC_FOOT()

#define TEST_TRANS_IMPL(N, func)                                               \
    TEST_IMPL_HEAD(N)                                                          \
        uint##N##_t test_case, expect, actual, invert;                         \
        FOREACH_TEST_CASE(N)                                                   \
            for (int rows = 1; rows <= N; rows <<= 1) {                        \
                expect = expect_##func##N(test_case, rows);                    \
                check##N##_perm_assert(#func, test_case, expect);              \
                actual = func##N(test_case, rows);                             \
                check##N##_impl(#func, test_case, expect, actual);             \
                                                                               \
                expect = expect_##func##N(actual, N / rows);                   \
                check##N##_perm_assert(#func, actual, expect);                 \
                invert = func##N(actual, N / rows);                            \
                check##N##_impl(#func, test_case, expect, invert);             \
                check##N##_inv(#func, #func, test_case, invert);               \
            }                                                                  \
        END_FOREACH                                                            \
        FOREACH_POWER_CASE(N)                                                  \
            for (int rows = 1; rows <= N; rows <<= 1) {                        \
                expect = expect_##func##N(test_case, rows);                    \
                check##N##_perm_assert(#func, test_case, expect);              \
                actual = func##N(test_case, rows);                             \
                check##N##_impl(#func, test_case, expect, actual);             \
                                                                               \
                expect = expect_##func##N(actual, N / rows);                   \
                check##N##_perm_assert(#func, actual, expect);                 \
                invert = func##N(actual, N / rows);                            \
                check##N##_impl(#func, test_case, expect, invert);             \
                check##N##_inv(#func, #func, test_case, invert);               \
            }                                                                  \
        END_FOREACH                                                            \
        FOREACH_RAND_CASE(N)                                                   \
            for (int rows = 1; rows <= N; rows <<= 1) {                        \
                expect = expect_##func##N(test_case, rows);                    \
                check##N##_perm_assert(#func, test_case, expect);              \
                actual = func##N(test_case, rows);                             \
                check##N##_impl(#func, test_case, expect, actual);             \
                                                                               \
                expect = expect_##func##N(actual, N / rows);                   \
                check##N##_perm_assert(#func, actual, expect);                 \
                invert = func##N(actual, N / rows);                            \
                check##N##_impl(#func, test_case, expect, invert);             \
                check##N##_inv(#func, #func, test_case, invert);               \
            }                                                                  \
        END_FOREACH                                                            \
    TEST_IMPL_FOOT()

TEST_CALC("pop", pop)
TEST_CALC("par", par)
TEST_CALC("ctz", ctz)
TEST_CALC("clz", clz)
TEST_CALC("mxset", mxset)
TEST_CALC("mnset", mnset)
TEST_CALC("lb", lb)
TEST_CALC("ipow", ipow)
TEST_CALC("cpow", cpow)
TEST_CALC("fpow", fpow)
TEST_CALC("lsb", lsb)
TEST_CALC("msb", msb)
TEST_CALC_PAIR("max", max)
TEST_CALC_PAIR("min", min)
TEST_CALC_PAIR("gcd", gcd)
TEST_PERM_INV("rev", rev, rev)
TEST_PERM_INV("shuf", shuf, ishuf)
TEST_PERM_MASK_INV("bfly", bfly, ibfly)
TEST_MANI_MASK("extr", extr)
TEST_MANI_MASK("depl", depl)
TEST_MANI_MASK("extl", extl)
TEST_MANI_MASK("depr", depr)
TEST_PERM_MASK_INV("grp", grp, igrp)
TEST_PERM_CUSTOM("trans", trans, TEST_TRANS_IMPL)
