#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

#include "test_serial.h"
#include "test_suite.h"

#include "../bits.h"
#include "../inc/extint.h"
#include "../inc/N.h"
#include "../util/print.h"
#include "../util/random.h"

size_t NR = (uintmax_t) 1 << 7;

extern int errno;

static const uint128_t VALUES[] = {
    U128(0x0000000000000000, 0x0000000000000000),
    U128(0x1111111111111111, 0x1111111111111111),
    U128(0x2222222222222222, 0x2222222222222222),
    U128(0x3333333333333333, 0x3333333333333333),
    U128(0x4444444444444444, 0x4444444444444444),
    U128(0x5555555555555555, 0x5555555555555555),
    U128(0x6666666666666666, 0x6666666666666666),
    U128(0x7777777777777777, 0x7777777777777777),
    U128(0x8888888888888888, 0x8888888888888888),
    U128(0x9999999999999999, 0x9999999999999999),
    U128(0xAAAAAAAAAAAAAAAA, 0xAAAAAAAAAAAAAAAA),
    U128(0xBBBBBBBBBBBBBBBB, 0xBBBBBBBBBBBBBBBB),
    U128(0xCCCCCCCCCCCCCCCC, 0xCCCCCCCCCCCCCCCC),
    U128(0xDDDDDDDDDDDDDDDD, 0xDDDDDDDDDDDDDDDD),
    U128(0xEEEEEEEEEEEEEEEE, 0xEEEEEEEEEEEEEEEE),
    U128(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF),
    U128(0xFEDCBA9876543210, 0x0123456789ABCDEF),
    U128(0xEDCBA9876543210F, 0xF0123456789ABCDE),
    U128(0xDCBA9876543210FE, 0xEF0123456789ABCD),
    U128(0xCBA9876543210FED, 0xDEF0123456789ABC),
    U128(0xBA9876543210FEDC, 0xCDEF0123456789AB),
    U128(0xA9876543210FEDCB, 0xBCDEF0123456789A),
    U128(0x9876543210FEDCBA, 0xABCDEF0123456789),
    U128(0x876543210FEDCBA9, 0x9ABCDEF012345678),
    U128(0x76543210FEDCBA98, 0x89ABCDEF01234567),
    U128(0x6543210FEDCBA987, 0x789ABCDEF0123456),
    U128(0x543210FEDCBA9876, 0x6789ABCDEF012345),
    U128(0x43210FEDCBA98765, 0x56789ABCDEF01234),
    U128(0x3210FEDCBA987654, 0x456789ABCDEF0123),
    U128(0x210FEDCBA9876543, 0x3456789ABCDEF012),
    U128(0x10FEDCBA98765432, 0x23456789ABCDEF01),
    U128(0x0FEDCBA987654321, 0x123456789ABCDEF0),
    U128(0x0123456789ABCDEF, 0xFEDCBA9876543210),
    U128(0xF0123456789ABCDE, 0xEDCBA9876543210F),
    U128(0xEF0123456789ABCD, 0xDCBA9876543210FE),
    U128(0xDEF0123456789ABC, 0xCBA9876543210FED),
    U128(0xCDEF0123456789AB, 0xBA9876543210FEDC),
    U128(0xBCDEF0123456789A, 0xA9876543210FEDCB),
    U128(0xABCDEF0123456789, 0x9876543210FEDCBA),
    U128(0x9ABCDEF012345678, 0x876543210FEDCBA9),
    U128(0x89ABCDEF01234567, 0x76543210FEDCBA98),
    U128(0x789ABCDEF0123456, 0x6543210FEDCBA987),
    U128(0x6789ABCDEF012345, 0x543210FEDCBA9876),
    U128(0x56789ABCDEF01234, 0x43210FEDCBA98765),
    U128(0x456789ABCDEF0123, 0x3210FEDCBA987654),
    U128(0x3456789ABCDEF012, 0x210FEDCBA9876543),
    U128(0x23456789ABCDEF01, 0x10FEDCBA98765432),
    U128(0x123456789ABCDEF0, 0x0FEDCBA987654321)
};

size_t NT = sizeof VALUES / sizeof VALUES[0];

static void alloc_test_values(void) {
    #define ALLOC_TEST_VALUES(N)                        \
        {                                               \
            T##N = malloc(sizeof(uint##N##_t) * NT);    \
            for (size_t i = 0; i < NT; ++i)             \
                T##N[i] = (uint##N##_t) VALUES[i];      \
                                                        \
            P##N = malloc(sizeof(uint##N##_t) * N);     \
            uint##N##_t pow = ONE##N;                   \
            for (int i = 0; i < N; ++i, pow <<= 1)      \
                P##N[i] = pow;                          \
                                                        \
            R##N = malloc(sizeof(uint##N##_t) * NR);    \
            for (size_t i = 0; i < NR; ++i)             \
                R##N[i] = rand##N();                    \
        }
    TEMPLATE_STD(ALLOC_TEST_VALUES)
}

static void free_test_values(void) {
    #define FREE_TEST_VALUES(N)         \
        {                               \
            free(T##N); T##N = NULL;    \
            free(P##N); P##N = NULL;    \
            free(R##N); R##N = NULL;    \
        }
    TEMPLATE_STD(FREE_TEST_VALUES)
}

static bool suite_init;
static bool test_init;

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

static const char* filename = "log.txt";
static FILE* fptr;

static bool rand_init;

void init_suite(bool log) {
    if (!rand_init) {
        init_rand();
        rand_init = true;
    }

    setbuf(stdout, NULL);

    no_init_suite_check();
    alloc_test_values();
    suite_init = true;

    suite_errors = prev_test_errors = prev_width_errors = test_counter = 0;
    test_init = false;

    #define WIDTHS_FMT(N) "  %3d  "         // some clever replication iidssm
    #define WIDTHS_INT(N) , N
    #define BORDER_HYPHENS(N) "-------"
    printf("testing bits library\n");
    if (log) {
        if (!(fptr = fopen(filename, "wb"))) {
            printf("WARNING: could not create/open log file %s.\n", filename);
            printf("ERROR %d: %s\n", errno, strerror(errno));
            perror(filename);
        } else
            printf(" - saving output to %s\n", filename);
    }
    printf("\n");
    printf("            " TEMPLATE_STD(WIDTHS_FMT) "\n" TEMPLATE_STD(WIDTHS_INT));
    printf("          +-" TEMPLATE_STD(BORDER_HYPHENS) "-+\n");
}

void init_test(const char* name) {
    init_suite_check();
    no_init_test_check();
    test_init = true;
    prev_test_errors = suite_errors;

    printf("%8s  | ", (char*) name);
    if (fptr)
        fprintf(fptr, "%s:\n", (char*) name);
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

}

void term_suite(void) {
    init_suite_check();
    no_init_test_check();
    free_test_values();
    suite_init = false;

    printf("          +-" TEMPLATE_STD(BORDER_HYPHENS) "-+\n");
    printf("             tests: %lld\n", test_counter);
    printf("            errors: %lld\n", suite_errors);
    suite_errors = 0;

    if (fptr) {
        if (fflush(fptr)) {
            fprintf(stderr, "WARNING: could not flush log file stream %s.\n", filename);
            fprintf(stderr, "ERROR %d: %s\n", errno, strerror(errno));
        }
        if (fclose(fptr)) {
            fprintf(stderr, "WARNING: could not close log file %s.\n", filename);
            fprintf(stderr, "ERROR %d: %s\n", errno, strerror(errno));
        }
        fptr = NULL;
    }
}

#define TEST_SUITE_IMPLEMENTATIONS(N)                                                                                           \
    void check##N##_impl(const char* fn, uint##N##_t input, uint##N##_t expected, uint##N##_t actual) {                         \
        init_test_check();                                                                                                      \
        test_count();                                                                                                           \
                                                                                                                                \
        if (expected != actual) {                                                                                               \
            if (fptr) {                                                                                                         \
                fprintf(fptr, "\terror: %s%d() did not produce the expected output\n", fn, N);                                  \
                fprintf(fptr, "\t\tinput:   " FMT##N "\n", print##N(input));                                                    \
                fprintf(fptr, "\t\tserial:  " FMT##N "\n", print##N(expected));                                                 \
                fprintf(fptr, "\t\tactual:  " FMT##N "\n", print##N(actual));                                                   \
            }                                                                                                                   \
            error();                                                                                                            \
        }                                                                                                                       \
    }                                                                                                                           \
                                                                                                                                \
    void check##N##_impl_mask(const char* fn, uint##N##_t input, uint##N##_t mask, uint##N##_t expected, uint##N##_t actual) {  \
        init_test_check();                                                                                                      \
        test_count();                                                                                                           \
                                                                                                                                \
        if (expected != actual) {                                                                                               \
            if (fptr) {                                                                                                         \
                fprintf(fptr, "\terror: %s%d() did not produce the expected output\n", fn, N);                                  \
                fprintf(fptr, "\t\tinput:   " FMT##N "\n", print##N(input));                                                    \
                fprintf(fptr, "\t\tmask:    " FMT##N "\n", print##N(mask));                                                     \
                fprintf(fptr, "\t\tserial:  " FMT##N "\n", print##N(expected));                                                 \
                fprintf(fptr, "\t\tactual:  " FMT##N "\n", print##N(actual));                                                   \
            }                                                                                                                   \
            error();                                                                                                            \
        }                                                                                                                       \
    }                                                                                                                           \
                                                                                                                                \
    void check##N##_inv(const char* fn, const char* ifn, uint##N##_t input, uint##N##_t actual) {                               \
        init_test_check();                                                                                                      \
        test_count();                                                                                                           \
                                                                                                                                \
        if (input != actual) {                                                                                                  \
            if (fptr) {                                                                                                         \
                fprintf(fptr, "\terror: %s%d() did not invert %s%d()\n", ifn, N, fn, N);                                        \
                fprintf(fptr, "\t\tinput:   " FMT##N "\n", print##N(input));                                                    \
                fprintf(fptr, "\t\toutput:  " FMT##N "\n", print##N(actual));                                                   \
            }                                                                                                                   \
            error();                                                                                                            \
        }                                                                                                                       \
    }                                                                                                                           \
                                                                                                                                \
    void check##N##_inv_mask(const char* fn, const char* ifn, uint##N##_t input, uint##N##_t mask, uint##N##_t actual) {        \
        init_test_check();                                                                                                      \
        test_count();                                                                                                           \
                                                                                                                                \
        if (input != actual) {                                                                                                  \
            if (fptr) {                                                                                                         \
                fprintf(fptr, "\terror: %s%d() did not invert %s%d()\n", ifn, N, fn, N);                                        \
                fprintf(fptr, "\t\tinput:   " FMT##N "\n", print##N(input));                                                    \
                fprintf(fptr, "\t\tmask:    " FMT##N "\n", print##N(mask));                                                     \
                fprintf(fptr, "\t\toutput:  " FMT##N "\n", print##N(actual));                                                   \
            }                                                                                                                   \
            error();                                                                                                            \
        }                                                                                                                       \
    }                                                                                                                           \
                                                                                                                                \
    void check##N##_perm_assert(const char* fn, uint##N##_t input, uint##N##_t output) {                                        \
        init_test_check();                                                                                                      \
        test_count();                                                                                                           \
                                                                                                                                \
        int ipop = serial_pop##N(input);                                                                                        \
        int opop = serial_pop##N(output);                                                                                       \
        if (ipop != opop) {                                                                                                     \
            if (fptr) {                                                                                                         \
                fprintf(fptr, "\terror: permutation %s%d() does not preserve set bit count\n", fn, N);                          \
                fprintf(fptr, "\t\tinput:   " FMT##N " (%d bits set)\n", print##N(input), ipop);                                \
                fprintf(fptr, "\t\toutput:  " FMT##N " (%d bits set)\n", print##N(output), opop);                               \
            }                                                                                                                   \
            error();                                                                                                            \
        }                                                                                                                       \
    }                                                                                                                           \
                                                                                                                                \
    void check##N##_perm_assert_mask(const char* fn, uint##N##_t input, uint##N##_t mask, uint##N##_t output) {                 \
        init_test_check();                                                                                                      \
        test_count();                                                                                                           \
                                                                                                                                \
        int ipop = serial_pop##N(input);                                                                                        \
        int opop = serial_pop##N(output);                                                                                       \
        if (ipop != opop) {                                                                                                     \
            if (fptr) {                                                                                                         \
                fprintf(fptr, "\terror: permutation %s%d() does not preserve set bit count\n", fn, N);                          \
                fprintf(fptr, "\t\tmask:    " FMT##N "\n", print##N(mask));                                                     \
                fprintf(fptr, "\t\tinput:   " FMT##N " (%d bits set)\n", print##N(input), ipop);                                \
                fprintf(fptr, "\t\toutput:  " FMT##N " (%d bits set)\n", print##N(output), opop);                               \
            }                                                                                                                   \
            error();                                                                                                            \
        }                                                                                                                       \
    }
TEMPLATE_STD(TEST_SUITE_IMPLEMENTATIONS)
