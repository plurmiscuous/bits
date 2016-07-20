#ifndef _KRYPTO_H_
#define _KRYPTO_H_

#include <stdint.h>

#include "inc/N.h"
#include "inc/extint.h"

#define ASSERT 1

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

#endif // _KRYPTO_H_
