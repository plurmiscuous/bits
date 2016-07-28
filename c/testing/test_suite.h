#ifndef _TEST_H_
#define _TEST_H_

#include <stdint.h>
#include <stddef.h>

#include "../bits.h"
#include "../inc/extint.h"
#include "../inc/N.h"
#include "../util/print.h"

#define DISPLAY_DIFF_OFF 0
#define DISPLAY_DIFF_ON  1

void init_suite(int output_diff);
void init_test(const char* name);
void init_width();
void term_width(void);
void term_test(void);
void term_suite(void);

#define TEST_SUITE_DECLARATIONS(N)                                                                              \
    uint##N##_t* T##N;                                                                                          \
    uint##N##_t* P##N;                                                                                          \
    uint##N##_t* R##N;                                                                                          \
    void check##N##_impl(const char* fn, uint##N##_t input, uint##N##_t serialed, uint##N##_t actual);          \
    void check##N##_inv(const char* fn, const char* ifn, uint##N##_t input, uint##N##_t actual);                \
    void check##N##_perm_assert(const char* fn, uint##N##_t input, uint##N##_t output);
TEMPLATE_STD(TEST_SUITE_DECLARATIONS)


#endif // _TEST_H_
