#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>

#include "test_expect.h"
#include "test_funcs.h"
#include "test_suite.h"

#include "../bits.h"
#include "../inc/extint.h"
#include "../inc/N.h"
#include "../util/print.h"
#include "../util/random.h"


static void alloc_test_values(void) {
    #define ALLOC_TEST_VALUES_IMPL(N)                           \
        {                                                       \
            T##N = malloc(sizeof(uint##N##_t) * NT);            \
            for (size_t i = 0; i < NT; ++i)                     \
                T##N[i] = (uint##N##_t) VALUES[i];              \
                                                                \
            P##N = malloc(sizeof(uint##N##_t) * N);             \
            uint##N##_t pow = ONE##N;                           \
            for (int i = 0; i < N; ++i, pow <<= 1)              \
                P##N[i] = pow;                                  \
                                                                \
            R##N = malloc(sizeof(uint##N##_t) * NR);            \
            for (size_t i = 0; i < NR; ++i)                     \
                R##N[i] = rand##N();                            \
        }
    TEMPLATE_STD(ALLOC_TEST_VALUES_IMPL)
}

static void free_test_values(void) {
    #define FREE_TEST_VALUES_IMPL(N)    \
        {                               \
            free(T##N); T##N = NULL;    \
            free(P##N); P##N = NULL;    \
            free(R##N); R##N = NULL;    \
        }
    TEMPLATE_STD(FREE_TEST_VALUES_IMPL)
}

static bool suite_init;

static void init_suite_check(void) {
    if (!suite_init) {
        printf("error: test suite has not been initialized via init_suite()\n");
        exit(-1);
    }
}

static void no_init_suite_check(void) {
    if (suite_init) {
        printf("error: test suite has been initialized; call term_suite() first\n");
        exit(-1);
    }
}

static bool test_init;

static void init_test_check(void) {
    if (!test_init) {
        printf("error: test has not been initialized via init_test()\n");
        exit(-1);
    }
}

static void no_init_test_check(void) {
    if (test_init) {
        printf("error: test has been initialized; call term_test() first\n");
        exit(-1);
    }
}

static long long suite_errors;
static long long prev_test_errors;
static long long prev_width_errors;
static void error(void) {
    ++suite_errors;
}
static long long test_counter;
static void test_count() {
    ++test_counter;
}

static char* test_name; // remove this if never used outside init_test()
static int print_diff;

static bool rand_init;

void init_suite(int output_diff) {
    if (!rand_init) {
        init_rand();
        rand_init = true;
    }

    setbuf(stdout, NULL);

    no_init_suite_check();
    alloc_test_values();
    suite_init = true;

    print_diff = output_diff;
    suite_errors = prev_test_errors = prev_width_errors = test_counter = 0;
    test_name = NULL;
    test_init = 0;

    #define WIDTHS_FMT(N) " %3d   "
    #define WIDTHS_INT(N) , N
    printf("testing libbits\n");
    printf("             " TEMPLATE_STD(WIDTHS_FMT) "\n" TEMPLATE_STD(WIDTHS_INT));
    #define BORDER_HYPHENS(N) "-------"
    printf("          +-" TEMPLATE_STD(BORDER_HYPHENS) "-+\n");
}

void init_test(const char* name) {
    init_suite_check();
    no_init_test_check();
    test_init = true;
    prev_test_errors = suite_errors;

    test_name = (char*) name;
    printf("%8s  | ", test_name);
}

void init_width() {
    prev_width_errors = suite_errors;
}

void term_width() {
    int nerrors = suite_errors - prev_width_errors;
    printf(" %s ", !nerrors ? "  .  " : "ERROR");
    prev_width_errors = 0;
}

void term_test(void) {
    init_test_check();
    test_init = false;

    int nerrors = suite_errors - prev_test_errors;
    printf(" |");
    if (nerrors)
        printf("  %d errors", nerrors);
    printf("\n");
    prev_test_errors = 0;
    test_name = NULL;

}

void term_suite(void) {
    init_suite_check();
    no_init_test_check();
    free_test_values();
    suite_init = false;

    printf("          +-" TEMPLATE_STD(BORDER_HYPHENS) "-+\n");
    printf("             tests: %lld\n", test_counter);
    printf("            errors: %lld\n", suite_errors);

    print_diff = suite_errors = 0;
}

#define TEST_IMPL(N)                                                                                                   \
    void check##N##_impl(const char* fn, uint##N##_t input, uint##N##_t expected, uint##N##_t actual) {                \
        init_test_check();                                                                                             \
        test_count();                                                                                                  \
                                                                                                                       \
        if (expected != actual) {                                                                                      \
            if (print_diff) {                                                                                          \
                printf("\t\terror: %s%d() did not produce the expected output\n", fn, N);                              \
                printf("\t\t\tinput:    " FMT##N "\n", print##N(input));                                               \
                printf("\t\t\texpected: " FMT##N "\n", print##N(expected));                                            \
                printf("\t\t\tactual:   " FMT##N "\n", print##N(actual));                                              \
            }                                                                                                          \
            error();                                                                                                   \
        }                                                                                                              \
    }                                                                                                                  \
                                                                                                                       \
    void check##N##_inv(const char* fn, const char* ifn, uint##N##_t input, uint##N##_t actual) {                      \
        init_test_check();                                                                                             \
        test_count();                                                                                                  \
                                                                                                                       \
        if (input != actual) {                                                                                         \
            if (print_diff) {                                                                                          \
                printf("\t\terror: %s%d() did not invert %s%d()\n", ifn, N, fn, N);                                    \
                printf("\t\t\tinput:  " FMT##N "\n", print##N(input));                                                 \
                printf("\t\t\toutput: " FMT##N "\n", print##N(actual));                                                \
            }                                                                                                          \
            error();                                                                                                   \
        }                                                                                                              \
    }                                                                                                                  \
                                                                                                                       \
    void check##N##_perm_assert(const char* fn, uint##N##_t input, uint##N##_t output) {                               \
        init_test_check();                                                                                             \
        test_count();                                                                                                  \
                                                                                                                       \
        int ipop = expect_pop##N(input);                                                                               \
        int opop = expect_pop##N(output);                                                                              \
        if(ipop != opop) {                                                                                             \
            if (print_diff) {                                                                                          \
                printf("\t\terror: permutation %s%d() does not preserve set bit count\n", fn, N);                      \
                printf("\t\t\tinput:           " FMT##N "\n", print##N(input));                                        \
                printf("\t\t\tinput bits set:  %d\n", ipop);                                                           \
                printf("\t\t\toutput:          " FMT##N "\n", print##N(output));                                       \
                printf("\t\t\toutput bits set: %d\n", opop);                                                           \
            }                                                                                                          \
            error();                                                                                                   \
        }                                                                                                              \
    }
TEMPLATE_STD(TEST_IMPL)
