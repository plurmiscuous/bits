#ifndef TEST_SERIAL_H
#define TEST_SERIAL_H

#include <stdint.h>

#include "../inc/extint.h"
#include "../inc/N.h"

#define SERIAL_DECLARATIONS(N)                                                                     \
    int serial_pop##N(uint##N##_t bits);                                                           \
    int serial_par##N(uint##N##_t bits);                                                           \
    int serial_ctz##N(uint##N##_t bits);                                                           \
    int serial_clz##N(uint##N##_t bits);                                                           \
    int serial_mxset##N(uint##N##_t bits);                                                         \
    int serial_mnset##N(uint##N##_t bits);                                                         \
    uint##N##_t serial_max##N(uint##N##_t x, uint##N##_t y);                                       \
    uint##N##_t serial_min##N(uint##N##_t x, uint##N##_t y);                                       \
    uint##N##_t serial_gcd##N(uint##N##_t x, uint##N##_t y);                                       \
    uint##N##_t serial_lb##N(uint##N##_t bits);                                                    \
    int serial_ipow##N(uint##N##_t bits);                                                          \
    uint##N##_t serial_cpow##N(uint##N##_t bits);                                                  \
    uint##N##_t serial_fpow##N(uint##N##_t bits);                                                  \
    uint##N##_t serial_lsb##N(uint##N##_t bits);                                                   \
    uint##N##_t serial_msb##N(uint##N##_t bits);                                                   \
    uint##N##_t serial_rol##N(uint##N##_t bits, int rot);                                          \
    uint##N##_t serial_ror##N(uint##N##_t bits, int rot);                                          \
    uint##N##_t serial_bswap##N(uint##N##_t bits, int i, int j);                                   \
    uint##N##_t serial_rswap##N(uint##N##_t bits, int i, int j, int len);                          \
    uint##N##_t serial_rev##N(uint##N##_t bits);                                                   \
    uint##N##_t serial_shuf##N(uint##N##_t bits);                                                  \
    uint##N##_t serial_ishuf##N(uint##N##_t bits);                                                 \
    uint##N##_t serial_grp##N(uint##N##_t bits, uint##N##_t mask);                                 \
    uint##N##_t serial_igrp##N(uint##N##_t bits, uint##N##_t mask);                                \
    uint##N##_t serial_omflip##N(uint##N##_t bits, uint##N##_t mask, uint8_t opts);                \
    uint##N##_t serial_bfly##N(uint##N##_t bits, uint##N##_t mask);                                \
    uint##N##_t serial_ibfly##N(uint##N##_t bits, uint##N##_t mask);                               \
    uint##N##_t serial_extr##N(uint##N##_t bits, uint##N##_t mask);                                \
    uint##N##_t serial_extl##N(uint##N##_t bits, uint##N##_t mask);                                \
    uint##N##_t serial_depr##N(uint##N##_t bits, uint##N##_t mask);                                \
    uint##N##_t serial_depl##N(uint##N##_t bits, uint##N##_t mask);                                \
    uint##N##_t serial_trans##N(uint##N##_t bits, int rows);
TEMPLATE_STD(SERIAL_DECLARATIONS)

#endif // TEST_SERIAL_H
