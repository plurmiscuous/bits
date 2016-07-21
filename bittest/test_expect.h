#ifndef _TEST_NAIVE_H_
#define _TEST_NAIVE_H_

#include <stdint.h>

#include "../inc/extint.h"
#include "../inc/N.h"

#define EXPECT_DECL(N)                                                                             \
    int expect_pop##N(uint##N##_t bits);                                                           \
    int expect_par##N(uint##N##_t bits);                                                           \
    int expect_ctz##N(uint##N##_t bits);                                                           \
    int expect_clz##N(uint##N##_t bits);                                                           \
    int expect_mxset##N(uint##N##_t bits);                                                         \
    int expect_mnset##N(uint##N##_t bits);                                                         \
    uint##N##_t expect_max##N(uint##N##_t x, uint##N##_t y);                                       \
    uint##N##_t expect_min##N(uint##N##_t x, uint##N##_t y);                                       \
    uint##N##_t expect_gcd##N(uint##N##_t x, uint##N##_t y);                                       \
    uint##N##_t expect_lb##N(uint##N##_t bits);                                                    \
    int expect_ipow##N(uint##N##_t bits);                                                          \
    uint##N##_t expect_cpow##N(uint##N##_t bits);                                                  \
    uint##N##_t expect_fpow##N(uint##N##_t bits);                                                  \
    uint##N##_t expect_lsb##N(uint##N##_t bits);                                                   \
    uint##N##_t expect_msb##N(uint##N##_t bits);                                                   \
    uint##N##_t expect_rol##N(uint##N##_t bits, int rot);                                          \
    uint##N##_t expect_ror##N(uint##N##_t bits, int rot);                                          \
    uint##N##_t expect_bswap##N(uint##N##_t bits, int i, int j);                                   \
    uint##N##_t expect_rswap##N(uint##N##_t bits, int i, int j, int len);                          \
    uint##N##_t expect_rev##N(uint##N##_t bits);                                                   \
    uint##N##_t expect_shuf##N(uint##N##_t bits);                                                  \
    uint##N##_t expect_ishuf##N(uint##N##_t bits);                                                 \
    uint##N##_t expect_grp##N(uint##N##_t bits, uint##N##_t mask);                                 \
    uint##N##_t expect_igrp##N(uint##N##_t bits, uint##N##_t mask);                                \
    uint##N##_t expect_omflip##N(uint##N##_t bits, uint##N##_t mask, uint8_t opts);                \
    uint##N##_t expect_bfly##N(uint##N##_t bits, uint##N##_t mask);                                \
    uint##N##_t expect_ibfly##N(uint##N##_t bits, uint##N##_t mask);                               \
    uint##N##_t expect_benes##N(uint##N##_t bits, uint##N##_t mask, int log1, int log2);           \
    uint##N##_t expect_extr##N(uint##N##_t bits, uint##N##_t mask);                                \
    uint##N##_t expect_extl##N(uint##N##_t bits, uint##N##_t mask);                                \
    uint##N##_t expect_depr##N(uint##N##_t bits, uint##N##_t mask);                                \
    uint##N##_t expect_depl##N(uint##N##_t bits, uint##N##_t mask);                                \
    uint##N##_t expect_trans##N(uint##N##_t bits, int rows);                                       \

TEMPLATE_STD(EXPECT_DECL)

#endif // _TEST_NAIVE_H_
