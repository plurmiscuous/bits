#ifndef _TEST_SUITE_HH_
#define _TEST_SUITE_HH_

#include "../util/Hexify.hh"

void init_suite();
void init_test(const char* name);
void init_width();
void term_width(void);
void term_test(void);
void term_suite(void);

template <typename T> void check_impl(const char* fn, T input, T serialed, T actual);
template <typename T> void check_inv(const char* fn, const char* ifn, T input, T actual);
template <typename T> void check_perm_assert(const char* fn, T input, T output);

//////


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
// static char* test_name; // remove this if never used outside init_test()
static int print_diff;

// IMPLEMENTATIONS

template <typename T>
void check_impl(const char* fn, T input, T expected, T actual) {
    init_test_check();
    test_count();

    if (expected != actual) {
        if (print_diff) {
            std::cout << "\t\terror: " << fn << BITS<T>() << "() did not produce the expected output" << std::endl;
            std::cout << "\t\t\tinput:    " << Hexify<T>(input) << std::endl;
            std::cout << "\t\t\texpected: " << Hexify<T>(expected) << std::endl;
            std::cout << "\t\t\tactual:   " << Hexify<T>(actual) << std::endl;
        }
        error();
    }
}

template <typename T>
void check_inv(const char* fn, const char* ifn, T input, T actual) {
    init_test_check();
    test_count();

    if (input != actual) {
        if (print_diff) {
            std::cout << "\t\terror: " << ifn << BITS<T>() << "() did not invert " << fn << BITS<T>() << "()" << std::endl;
            std::cout << "\t\t\tinput:  " << Hexify<T>(input) << std::endl;
            std::cout << "\t\t\toutput: " << Hexify<T>(actual) << std::endl;
        }
        error();
    }
}

template <typename T>
void check_perm_assert(const char* fn, T input, T output) {
    init_test_check();
    test_count();

    int ipop = serial_pop(input);
    int opop = serial_pop(output);
    if (ipop != opop) {
        if (print_diff) {
            std::cout << "\t\terror: permutation " << fn << BITS<T>() << "() does not preserve set bit count" << std::endl;
            std::cout << "\t\t\tinput:           " << Hexify<T>(input) << std::endl;
            std::cout << "\t\t\tinput bits set:  " << ipop << std::endl;
            std::cout << "\t\t\toutput:          " << Hexify<T>(output) << std::endl;
            std::cout << "\t\t\toutput bits set: " << opop << std::endl;
        }
        error();
    }
}

#endif // _TEST_SUITE_HH_
