#ifndef _KRYPTO_H_
#define _KRYPTO_H_

#include <stdint.h>

#include "inc/extint.h"
#include "inc/template.h"

#define ASSERT 1

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

/*
// // Useful for calling functions without the bit-width specified.
// // Example:
// //      If bits is of type uint32_t, the statement:
// //           typeof(bits) parity = GENERIC(par, bits);
// //      is equivalent to:
// //           uint32_t parity = par32(bits);
// #define GENERIC(fn, X)      \
//     _Generic((X),           \
//         uint8_t  : fn##8,   \
//         uint16_t : fn##16,  \
//         uint32_t : fn##32,  \
//         uint64_t : fn##64,  \
//         uint128_t: fn##128  \
// )(X)
*/

/// DOCUMENTATION

// FUNCTION NAME
//      uint fn(uint bits);
// DESCRIPTION:
//      ....
// PARAMETERS:
//      bits: ...
// OUTPUT:
//      ...

// //////////////////////////////////
// ////    STANDARD FUNCTIONS    ////
// //////////////////////////////////

//// CALCULATIONS

// POPULATION:
//      int pop(uint bits);
// INPUT:
//      bits: the value to calculate on
// OUTPUT:
//      - the number of set (non-zero) bits in the word
#define POP_DECL(N) int pop##N(uint##N##_t bits);
TEMPLATE_STD(POP_DECL)

// PARITY:
//      int par(uint bits);
// INPUT:
//      bits: the value to calculate on
// OUTPUT:
//      - 0 if the number of set bits is even
//      - 1 otherwise
#define PAR_DECL(N) int par##N(uint##N##_t bits);
TEMPLATE_STD(PAR_DECL)

// COUNT TRAILING ZEROS:
//      int ctz(uint bits);
// INPUT:
//      bits: the value to calculate on
// OUTPUT:
//      - the number of least significant 0-bits before the first set bit
#define CTZ_DECL(N) int ctz##N(uint##N##_t bits);
TEMPLATE_STD(CTZ_DECL)

// COUNT TRAILING ZEROS:
//      int clz(uint bits);
// INPUT:
//      bits: the value to calculate on
// OUTPUT:
//      - the number of most significant 0-bits before the first set bit
#define CLZ_DECL(N) int clz##N(uint##N##_t bits);
TEMPLATE_STD(CLZ_DECL)

// LONGEST CHAIN OF SET BITS
//      int mxset(uint bits);
// INPUT:
//      bits: the value to calculate on
// OUTPUT:
//      - the length of the longest chain of set bits
#define MXSET_DECL(N) int mxset##N(uint##N##_t bits);
TEMPLATE_STD(MXSET_DECL)

// LONGEST CHAIN OF SET BITS
//      int mnset(uint bits);
// INPUT:
//      bits: the value to calculate on
// OUTPUT:
//      - the length of the shortest chain of set bits
#define MNSET_DECL(N) int mnset##N(uint##N##_t bits);
TEMPLATE_STD(MNSET_DECL)

// MAXIMUM
//      uint max(uint x, uint y);
// INPUT:
//      x, y: the values to compare
// OUTPUT:
//      - the maximum of the $x and $y
#define MAX_DECL(N) uint##N##_t max##N(uint##N##_t x, uint##N##_t y);
TEMPLATE_STD(MAX_DECL)

// MINIMUM
//      uint min(uint x, uint y);
// INPUT:
//      x, y: the values to compare
// OUTPUT:
//      - the minimum of the $x and $y
#define MIN_DECL(N) uint##N##_t min##N(uint##N##_t x, uint##N##_t y);
TEMPLATE_STD(MIN_DECL)

// GREATEST COMMON DIVISOR
//      uint gcd(uint x, uint y);
// INPUT:
//      x, y: the values to calculate on
// OUTPUT:
//      - the largest integer that divides both $x and $y without a remainder
#define GCD_DECL(N) uint##N##_t gcd##N(uint##N##_t x, uint##N##_t y);
TEMPLATE_STD(GCD_DECL)

// BINARY LOGARITHM
//      uint lb(uint bits);
// INPUT:
//      bits: the value to calculate on
// OUTPUT:
//      - returns the base-2 logarithm of $bits, rounded-down
#define LB_DECL(N) uint##N##_t lb##N(uint##N##_t bits);
TEMPLATE_STD(LB_DECL)

// IS POWER OF 2
//      int ipow(uint bits);
// INPUT:
//      bits: the value to calculate on
// OUTPUT:
//      - 0 if $bits is 0
//      - 1 if $bits is a power-of-2
//      - 0 otherwise
#define IPOW_DECL(N) int ipow##N(uint##N##_t bits);
TEMPLATE_STD(IPOW_DECL)

// CEIL POWER OF 2
//      uint cpow(uint bits);
// INPUT:
//      bits: the value to calculate on
// OUTPUT:
//      - 1 if $bits is 0
//      - $bits if $bits is already a power-of-2
//      - 0 if $bits is greater than the maximum power-of-2 the uint can hold
//      - the next greatest power-of-2 greater than $bits, otherwise
#define CPOW_DECL(N) uint##N##_t cpow##N(uint##N##_t bits);
TEMPLATE_STD(CPOW_DECL)

// FLOOR POWER OF 2
//      uint fpow(uint bits);
// INPUT:
//      bits: the value to calculate on
// OUTPUT:
//      - 0 if $bits is 0
//      - $bits if $bits is already a power-of-2
//      - the next smallest power-of-2 greater than $bits, otherwise
#define FPOW_DECL(N) uint##N##_t fpow##N(uint##N##_t bits);
TEMPLATE_STD(FPOW_DECL)

// LEAST SIGNIFICANT BIT
//      uint lsb(uint bits);
// INPUT:
//      bits: the value to calculate on
// OUTPUT:
//      - a mask with only the least significant bit of $bits set
#define LSB_DECL(N) uint##N##_t lsb##N(uint##N##_t bits);
TEMPLATE_STD(LSB_DECL)

// MOST SIGNIFICANT BIT
//      uint msb(uint bits);
// INPUT:
//      bits: the value to calculate on
// OUTPUT:
//      - a mask with only the most significant bit of $bits set
#define MSB_DECL(N) uint##N##_t msb##N(uint##N##_t bits);
TEMPLATE_STD(MSB_DECL)

//// PERMUTATIONS

// ROTATE LEFT
//      uint rol(uint bits, int rot);
// INPUT:
//      bits: the bit array to permute
//      rot: the number of positions to rotate left
// OUTPUT:
//      - $bits cyclically shifted to the left by $rot
#define ROL_DECL(N) uint##N##_t rol##N(uint##N##_t bits, int rot);
TEMPLATE_STD(ROL_DECL)

// ROTATE RIGHT
//      uint ror(uint bits, int rot);
// INPUT:
//      bits: the bit array to permute
//      rot: the number of positions to rotate right
// OUTPUT:
//      - $bits cyclically shifted to the right by $rot
#define ROR_DECL(N) uint##N##_t ror##N(uint##N##_t bits, int rot);
TEMPLATE_STD(ROR_DECL)

// DELTA SWAP
//      uint delta(uint bits, uint mask, int shift);
// INPUT:
//      bits: the bit array to permute
//      mask:
//      shift:
// OUTPUT:
//      -
#define DELTA_DECL(N) uint##N##_t delta##N(uint##N##_t bits, uint##N##_t mask, int shift);
TEMPLATE_STD(DELTA_DECL)

// BIT SWAP
//      uint bswap(uint bits, int i, int j);
// INPUT:
//      bits: the bit array to permute
//      i, j: the indices of the bits to swap
// OUTPUT:
//      - $bits with the bit at $i swapped with the bit at $j
#define BSWAP_DECL(N) uint##N##_t bswap##N(uint##N##_t bits, int i, int j);
TEMPLATE_STD(BSWAP_DECL)

// BIT-RANGE SWAP
//      uint rswap(uint bits, int i, int j, int len);
// INPUT:
//      bits: the bit array to permute
//      i, j: the lower indices of the bit ranges to swap
//      len: the number of bits to swap at each bit-index
// OUTPUT:
//      - $bits with the $len bits above $i swapped with the $len bits above $j
#define RSWAP_DECL(N) uint##N##_t rswap##N(uint##N##_t bits, int i, int j, int len);
TEMPLATE_STD(RSWAP_DECL)

// REVERSE
//      uint rev(uint bits);
// INPUT:
//      bits: the bit array to permute
// OUTPUT:
//      - the reverse of $bits
#define REV_DECL(N) uint##N##_t rev##N(uint##N##_t bits);
TEMPLATE_STD(REV_DECL)

// SHUFFLE
//      uint shuf(uint bits);
// INPUT:
//      bits: the bit array to permute
// OUTPUT:
//      - $bits after a perfect outer-shuffle
#define SHUF_DECL(N) uint##N##_t shuf##N(uint##N##_t bits);
TEMPLATE_STD(SHUF_DECL)

// INVERSE SHUFFLE
//      uint ishuf(uint bits);
// INPUT:
//      bits: the bit array to permute
// OUTPUT:
//      - $bits after reversing a perfect outer-shuffle
#define ISHUF_DECL(N) uint##N##_t ishuf##N(uint##N##_t bits);
TEMPLATE_STD(ISHUF_DECL)

// GROUP
//      uint grp(uint bits, uint mask);
// INPUT:
//      bits: the bit value to permute
//      mask:
// OUTPUT:
//      -
#define GRP_DECL(N) uint##N##_t grp##N(uint##N##_t bits, uint##N##_t mask);
TEMPLATE_STD(GRP_DECL)

// UNGROUP
//      uint igrp(uint bits, uint mask);
// INPUT:
//      bits: the bit value to permute
//      mask:
// OUTPUT:
//      -
#define IGRP_DECL(N) uint##N##_t igrp##N(uint##N##_t bits, uint##N##_t mask);
TEMPLATE_STD(IGRP_DECL)

// OMEGA-FLIP
//      uint omflip(uint bits, uint mask, uint8_t ctrl);
// INPUT:
//      bits: the bit array to permute
//      mask:
//      ctrl:
// OUTPUT:
//      -
#define OMFLIP_DECL(N) uint##N##_t omflip##N(uint##N##_t bits, uint##N##_t mask, uint8_t ctrl);
TEMPLATE_STD(OMFLIP_DECL)

// BUTTERFLY NETWORK
//      uint bfly(uint bits, uint mask);
// INPUT:
//      bits: the bit array to permute
//      mask:
// OUTPUT:
//      -
#define BFLY_DECL(N) uint##N##_t bfly##N(uint##N##_t bits, uint##N##_t mask);
TEMPLATE_STD(BFLY_DECL)

// INVERSE BUTTERFLY NETWORK
//      uint ibfly(uint bits, uint mask);
// INPUT:
//      bits: the bit array to permute
//      mask:
// OUTPUT:
//      -
#define IBFLY_DECL(N) uint##N##_t ibfly##N(uint##N##_t bits, uint##N##_t mask);
TEMPLATE_STD(IBFLY_DECL)

// BENES NETWORK
//      uint benes(uint bits, uint mask, int log1, int log2);
// INPUT:
//      bits: the bit array to permute
//      mask:
//      log1:
//      log2:
// OUTPUT:
//      -
#define BENES_DECL(N) uint##N##_t benes##N(uint##N##_t bits, uint##N##_t mask, int log1, int log2);
TEMPLATE_STD(BENES_DECL)

// TRANSPOSE
//      uint trans(uint bits, int rows);
// INPUT:
//      bits: the bit matrix to permute
//      rows: the number of rows in the matrix
// OUTPUT:
//      -
#define TRANS_DECL(N) uint##N##_t trans##N(uint##N##_t bits, int rows);
TEMPLATE_STD(TRANS_DECL)

/// MANIPULATIONS

// LINEAR-FEEDBACK SHIFT REGISTER
//      uint lfsr(uint bits);
// INPUT:
//      bits: the bit value to manipulate
// OUTPUT:
//      -
#define LFSR_DECL(N) uint##N##_t lfsr##N(uint##N##_t bits);
TEMPLATE_STD(LFSR_DECL)

// INVERSE LINEAR-FEEDBACK SHIFT REGISTER
//      uint ilfsr(uint bits);
// INPUT:
//      bits: the bit value to manipulate
// OUTPUT:
//      -
#define ILFSR_DECL(N) uint##N##_t ilfsr##N(uint##N##_t bits);
TEMPLATE_STD(ILFSR_DECL)

// BITWISE TERNARY
//      uint tern(uint xbits, uint ybits, uint ctrl);
// INPUT:
//      xbits:
//      ybits:
//      ctrl:
// OUTPUT:
//      -
#define TERN_DECL(N) uint##N##_t tern##N(uint##N##_t xbits, uint##N##_t ybits, uint##N##_t ctrl);
TEMPLATE_STD(TERN_DECL)

// BINARY REPRESENTATION TO GRAY CODE
//      uint gray(uint bits);
// INPUT:
//      bits: the bit value to manipulate
// OUTPUT:
//      -
#define GRAY_DECL(N) uint##N##_t gray##N(uint##N##_t bits);
TEMPLATE_STD(GRAY_DECL)

// GRAY CODE TO BINARY REPRESENTATION
//      uint igray(uint bits);
// INPUT:
//      bits: the bit value to manipulate
// OUTPUT:
//      -
#define IGRAY_DECL(N) uint##N##_t igray##N(uint##N##_t bits);
TEMPLATE_STD(IGRAY_DECL)

// EXTRACT LEFT
//      uint extl(uint bits, uint mask);
// INPUT:
//      bits: the bit value to manipulate
//      mask:
// OUTPUT:
//      -
#define EXTL_DECL(N) uint##N##_t extl##N(uint##N##_t bits, uint##N##_t mask);
TEMPLATE_STD(EXTL_DECL)

// EXTRACT RIGHT
//      uint extr(uint bits, uint mask);
// INPUT:
//      bits: the bit value to manipulate
//      mask:
// OUTPUT:
//      -
#define EXTR_DECL(N) uint##N##_t extr##N(uint##N##_t bits, uint##N##_t mask);
TEMPLATE_STD(EXTR_DECL)

// DEPOSIT LEFT
//      uint depl(uint bits, uint mask);
// INPUT:
//      bits: the bit value to manipulate
//      mask:
// OUTPUT:
//      -
#define DEPL_DECL(N) uint##N##_t depl##N(uint##N##_t bits, uint##N##_t mask);
TEMPLATE_STD(DEPL_DECL)

// DEPOSIT RIGHT
//      uint depr(uint bits, uint mask);
// INPUT:
//      bits: the bit value to manipulate
//      mask:
// OUTPUT:
//      -
#define DEPR_DECL(N) uint##N##_t depr##N(uint##N##_t bits, uint##N##_t mask);
TEMPLATE_STD(DEPR_DECL)

// //////////////////////////////////
// ////    P-SQUARE FUNCTIONS    ////
// //////////////////////////////////


// //////////////////////////////////
// ////     MASKS AND MACROS     ////
// //////////////////////////////////

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

// MASK GENERATION:
//     WORD[i] = ((uintN_t) (-1)) / ((1 << (1 << i)) + 1);
//     UNIT[i] = ((uintN_t) (-1)) / ((1 << (1 << i)) - 1);
//     SHUF[i] = WORD[i+1] & ~WORD[i];

// WORD MASKS

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

// UNIT MASKS

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

// SHUFFLE MASKS

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

// TRANSPOSE MASKS

static const uint128_t TRANS128[] = {
    u128(0x00AA00AA00AA00AA, 0x00AA00AA00AA00AA),
    u128(0x0000CCCC0000CCCC, 0x0000CCCC0000CCCC),
    u128(0x00000000F0F0F0F0, 0x00000000F0F0F0F0)
};

// LFSR TAPS

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

#endif // _KRYPTO_H_
