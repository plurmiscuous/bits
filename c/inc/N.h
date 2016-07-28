#ifndef _N_H_
#define _N_H_

#include "extint.h"

//////////////////////////////////
////       N-BIT SUPPORT      ////
//////////////////////////////////

static const enum LOGS {
    LOG1,
    LOG2,
    LOG4,
    LOG8,
    LOG16,
    LOG32,
    LOG64,
    LOG128,
    LOGMAX
} BINARY_LOG;

// Bit-widths
#define BITS4   (1 << LOG4)
#define BITS8   (1 << LOG8)
#define BITS16  (1 << LOG16)
#define BITS32  (1 << LOG32)
#define BITS64  (1 << LOG64)
#define BITS128 (1 << LOG128)
#define BITSMAX (1 << LOGMAX)

// Positive one (good for '1 << n' situations)
#define ONE8   ((uint8_t)   +1)
#define ONE16  ((uint16_t)  +1)
#define ONE32  ((uint32_t)  +1)
#define ONE64  ((uint64_t)  +1)
#define ONE128 ((uint128_t) +1)

// Negative one (all bits set)
#define NEG8   ((uint8_t)   -1)
#define NEG16  ((uint16_t)  -1)
#define NEG32  ((uint32_t)  -1)
#define NEG64  ((uint64_t)  -1)
#define NEG128 ((uint128_t) -1)

// Square roots (for matrix operations)
#define SQRT4   (BITS4  >> 1)
#define SQRT16  (BITS16 >> 2)
#define SQRT64  (BITS64 >> 3)

//////////////////////////////////
////          MASKS           ////
//////////////////////////////////

// MASK GENERATION:
//     WORD[i] = ((uintN_t) (-1)) / ((1 << (1 << i)) + 1);
//     UNIT[i] = ((uintN_t) (-1)) / ((1 << (1 << i)) - 1);
//     SHUF[i] = WORD[i+1] & ~WORD[i];

static const uint8_t WORD8[] = {
    0x55,
    0x33,
    0x0F
};

static const uint16_t WORD16[] = {
    0x5555,
    0x3333,
    0x0F0F,
    0x00FF
};

static const uint32_t WORD32[] = {
    0x55555555,
    0x33333333,
    0x0F0F0F0F,
    0x00FF00FF,
    0x0000FFFF
};

static const uint64_t WORD64[] = {
    0x5555555555555555,
    0x3333333333333333,
    0x0F0F0F0F0F0F0F0F,
    0x00FF00FF00FF00FF,
    0x0000FFFF0000FFFF,
    0x00000000FFFFFFFF
};

static const uint128_t WORD128[] = {
    u128(0x5555555555555555, 0x5555555555555555),
    u128(0x3333333333333333, 0x3333333333333333),
    u128(0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F),
    u128(0x00FF00FF00FF00FF, 0x00FF00FF00FF00FF),
    u128(0x0000FFFF0000FFFF, 0x0000FFFF0000FFFF),
    u128(0x00000000FFFFFFFF, 0x00000000FFFFFFFF),
    u128(0x0000000000000000, 0xFFFFFFFFFFFFFFFF)
};

static const uint8_t UNIT8[] = {
    0xFF,
    0x55,
    0x11,
    0x01
};

static const uint16_t UNIT16[] = {
    0xFFFF,
    0x5555,
    0x1111,
    0x0101,
    0x0001
};

static const uint32_t UNIT32[] = {
    0xFFFFFFFF,
    0x55555555,
    0x11111111,
    0x01010101,
    0x00010001,
    0x00000001
};

static const uint64_t UNIT64[] = {
    0xFFFFFFFFFFFFFFFF,
    0x5555555555555555,
    0x1111111111111111,
    0x0101010101010101,
    0x0001000100010001,
    0x0000000100000001,
    0x0000000000000001
};

static const uint128_t UNIT128[] = {
    u128(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF),
    u128(0x5555555555555555, 0x5555555555555555),
    u128(0x1111111111111111, 0x1111111111111111),
    u128(0x0101010101010101, 0x0101010101010101),
    u128(0x0001000100010001, 0x0001000100010001),
    u128(0x0000000100000001, 0x0000000100000001),
    u128(0x0000000000000001, 0x0000000000000001),
    u128(0x0000000000000000, 0x0000000000000001)
};

static const uint8_t SHUF8[] = {
    0x22,
    0x0C
};

static const uint16_t SHUF16[] = {
    0x2222,
    0x0C0C,
    0x00F0
};

static const uint32_t SHUF32[] = {
    0x22222222,
    0x0C0C0C0C,
    0x00F000F0,
    0x0000FF00
};

static const uint64_t SHUF64[] = {
    0x2222222222222222,
    0x0C0C0C0C0C0C0C0C,
    0x00F000F000F000F0,
    0x0000FF000000FF00,
    0x00000000FFFF0000
};

static const uint128_t SHUF128[] = {
    u128(0x2222222222222222, 0x2222222222222222),
    u128(0x0C0C0C0C0C0C0C0C, 0x0C0C0C0C0C0C0C0C),
    u128(0x00F000F000F000F0, 0x00F000F000F000F0),
    u128(0x0000FF000000FF00, 0x0000FF000000FF00),
    u128(0x00000000FFFF0000, 0x00000000FFFF0000),
    u128(0x0000000000000000, 0xFFFFFFFF00000000)
};

static const uint16_t TRANS16[] = {
    0x0A0A,
    0x00CC
};

static const uint64_t TRANS64[] = {
    0x00AA00AA00AA00AA,
    0x0000CCCC0000CCCC,
    0x00000000F0F0F0F0
};

// static const uint128_t TRANS128[] = {
//     u128(0x00AA00AA00AA00AA, 0x00AA00AA00AA00AA),
//     u128(0x0000CCCC0000CCCC, 0x0000CCCC0000CCCC),
//     u128(0x00000000F0F0F0F0, 0x00000000F0F0F0F0)
// };

//////////////////////////////////
////        LFSR TAPS         ////
//////////////////////////////////

#define FTAPS4   (0xC)
#define FTAPS8   (0x95)
#define FTAPS16  (0x801C)
#define FTAPS32  (0x80000062)
#define FTAPS64  (0x800000000000000E)
#define FTAPS128 (u128(0x8000000000000000, 0x0000000000000043))

#define RTAPS4   (0x9)
#define RTAPS8   (0x2B)
#define RTAPS16  (0x0039)
#define RTAPS32  (0x000000C5)
#define RTAPS64  (0x000000000000001D)
#define RTAPS128 (u128(0x0000000000000000, 0x0000000000000087))

//////////////////////////////////
////     TEMPLATE SUPPORT     ////
//////////////////////////////////

/*
 *  Macros for replicating other templated macros for particular bit-widths.
 *  These macros accept a single macro as an argument and that argument must
 *  accept a single argument which will be the bit-width.
 *
 *  Example:
 *      #define FUNCTION_TEMPLATE(N)        \
 *          int func##N(uint##N##_t arg) {  \
 *              assert(N > 0);              \
 *              return arg == N;            \
 *          }
 *      TEMPLATE_STD(FUNCTION_TEMPLATE)
 *
 *  Example:
 *      bool func(int n) {
 *          switch (n) {
 *              #define SWITCH_CASE_TEMPLATE(N)  \
 *                  case N:                      \
 *                      return calc##N(n);
 *              TEMPLATE_STD(SWITCH_CASE_TEMPLATE)
 *              default:
 *                  return false;
 *          }
 *      }
 */

#define TEMPLATE_STD(T)      T(8) T(16) T(32) T(64) T(128)
#define TEMPLATE_SQR(T)           T(16)       T(64)

#define TEMPLATE_STD_SIMD128(T) T(4) T(8) T(16) T(32) T(64)
#define TEMPLATE_SQR_SIMD128(T) T(4)      T(16)       T(64)

#define TEMPLATE_STD_TEST(TEST, func)                \
    TEST(  8, func)                                  \
    TEST( 16, func)                                  \
    TEST( 32, func)                                  \
    TEST( 64, func)                                  \
    TEST(128, func)                                  \

#define TEMPLATE_STD_TEST_INV(TEST, func, ifunc)     \
    TEST(  8, func, ifunc)                           \
    TEST( 16, func, ifunc)                           \
    TEST( 32, func, ifunc)                           \
    TEST( 64, func, ifunc)                           \
    TEST(128, func, ifunc)                           \

#endif // _N_H_
