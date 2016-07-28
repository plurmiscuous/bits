#ifndef _BITC_H_
#define _BITC_H_

#include <stdint.h>

#include "inc/N.h"
#include "inc/extint.h"

#define ASSERT 1

/// DOCUMENTATION

// FUNCTION NAME
//      uint fn(uint bits);
// DESCRIPTION:
//      ....
// PARAMETERS:
//      bits: ...
// RETURNS:
//      ...

// //////////////////////////////////
// ////    STANDARD FUNCTIONS    ////
// //////////////////////////////////

//// CALCULATIONS

// POPULATION:
//      int pop(uint bits);
// PARAMETERS:
//      bits: the value to calculate on
// RETURNS:
//      - the number of set (non-zero) bits in the word
#define POP_DECLARATION(N) \
    int pop##N(uint##N##_t bits);
TEMPLATE_STD(POP_DECLARATION)

// PARITY:
//      int par(uint bits);
// PARAMETERS:
//      bits: the value to calculate on
// RETURNS:
//      - 0 if the number of set bits is even
//      - 1 otherwise
#define PAR_DECLARATION(N) \
    int par##N(uint##N##_t bits);
TEMPLATE_STD(PAR_DECLARATION)

// COUNT TRAILING ZEROS:
//      int ctz(uint bits);
// PARAMETERS:
//      bits: the value to calculate on
// RETURNS:
//      - the number of least significant 0-bits before the first set bit
#define CTZ_DECLARATION(N) \
    int ctz##N(uint##N##_t bits);
TEMPLATE_STD(CTZ_DECLARATION)

// COUNT TRAILING ZEROS:
//      int clz(uint bits);
// PARAMETERS:
//      bits: the value to calculate on
// RETURNS:
//      - the number of most significant 0-bits before the first set bit
#define CLZ_DECLARATION(N) \
    int clz##N(uint##N##_t bits);
TEMPLATE_STD(CLZ_DECLARATION)

// LONGEST CHAIN OF SET BITS
//      int mxset(uint bits);
// PARAMETERS:
//      bits: the value to calculate on
// RETURNS:
//      - the length of the longest chain of set bits
#define MXSET_DECLARATION(N) \
    int mxset##N(uint##N##_t bits);
TEMPLATE_STD(MXSET_DECLARATION)

// LONGEST CHAIN OF SET BITS
//      int mnset(uint bits);
// PARAMETERS:
//      bits: the value to calculate on
// RETURNS:
//      - the length of the shortest chain of set bits
#define MNSET_DECLARATION(N) \
    int mnset##N(uint##N##_t bits);
TEMPLATE_STD(MNSET_DECLARATION)

// MAXIMUM
//      uint max(uint x, uint y);
// PARAMETERS:
//      x, y: the values to compare
// RETURNS:
//      - the maximum of the $x and $y
#define MAX_DECLARATION(N) \
    uint##N##_t max##N(uint##N##_t x, uint##N##_t y);
TEMPLATE_STD(MAX_DECLARATION)

// MINIMUM
//      uint min(uint x, uint y);
// PARAMETERS:
//      x, y: the values to compare
// RETURNS:
//      - the minimum of the $x and $y
#define MIN_DECLARATION(N) \
    uint##N##_t min##N(uint##N##_t x, uint##N##_t y);
TEMPLATE_STD(MIN_DECLARATION)

// GREATEST COMMON DIVISOR
//      uint gcd(uint x, uint y);
// PARAMETERS:
//      x, y: the values to calculate on
// RETURNS:
//      - the largest integer that divides both $x and $y without a remainder
#define GCD_DECLARATION(N) \
    uint##N##_t gcd##N(uint##N##_t x, uint##N##_t y);
TEMPLATE_STD(GCD_DECLARATION)

// BINARY LOGARITHM
//      uint lb(uint bits);
// PARAMETERS:
//      bits: the value to calculate on
// RETURNS:
//      - returns the base-2 logarithm of $bits, rounded-down
#define LB_DECLARATION(N) \
    uint##N##_t lb##N(uint##N##_t bits);
TEMPLATE_STD(LB_DECLARATION)

// IS POWER OF 2
//      int ipow(uint bits);
// PARAMETERS:
//      bits: the value to calculate on
// RETURNS:
//      - 0 if $bits is 0
//      - 1 if $bits is a power-of-2
//      - 0 otherwise
#define IPOW_DECLARATION(N) \
    int ipow##N(uint##N##_t bits);
TEMPLATE_STD(IPOW_DECLARATION)

// CEIL POWER OF 2
//      uint cpow(uint bits);
// PARAMETERS:
//      bits: the value to calculate on
// RETURNS:
//      - 1 if $bits is 0
//      - $bits if $bits is already a power-of-2
//      - 0 if $bits is greater than the maximum power-of-2 the uint can hold
//      - the next greatest power-of-2 greater than $bits, otherwise
#define CPOW_DECLARATION(N) \
    uint##N##_t cpow##N(uint##N##_t bits);
TEMPLATE_STD(CPOW_DECLARATION)

// FLOOR POWER OF 2
//      uint fpow(uint bits);
// PARAMETERS:
//      bits: the value to calculate on
// RETURNS:
//      - 0 if $bits is 0
//      - $bits if $bits is already a power-of-2
//      - the next smallest power-of-2 greater than $bits, otherwise
#define FPOW_DECLARATION(N) \
    uint##N##_t fpow##N(uint##N##_t bits);
TEMPLATE_STD(FPOW_DECLARATION)

// LEAST SIGNIFICANT BIT
//      uint lsb(uint bits);
// PARAMETERS:
//      bits: the value to calculate on
// RETURNS:
//      - a mask with only the least significant bit of $bits set
#define LSB_DECLARATION(N) \
    uint##N##_t lsb##N(uint##N##_t bits);
TEMPLATE_STD(LSB_DECLARATION)

// MOST SIGNIFICANT BIT
//      uint msb(uint bits);
// PARAMETERS:
//      bits: the value to calculate on
// RETURNS:
//      - a mask with only the most significant bit of $bits set
#define MSB_DECLARATION(N) \
    uint##N##_t msb##N(uint##N##_t bits);
TEMPLATE_STD(MSB_DECLARATION)

//// PERMUTATIONS

// ROTATE LEFT
//      uint rol(uint bits, int rot);
// PARAMETERS:
//      bits: the bit array to permute
//      rot: the number of positions to rotate left
// RETURNS:
//      - $bits cyclically shifted to the left by $rot
#define ROL_DECLARATION(N) \
    uint##N##_t rol##N(uint##N##_t bits, int rot);
TEMPLATE_STD(ROL_DECLARATION)

// ROTATE RIGHT
//      uint ror(uint bits, int rot);
// PARAMETERS:
//      bits: the bit array to permute
//      rot: the number of positions to rotate right
// RETURNS:
//      - $bits cyclically shifted to the right by $rot
#define ROR_DECLARATION(N) \
    uint##N##_t ror##N(uint##N##_t bits, int rot);
TEMPLATE_STD(ROR_DECLARATION)

// DELTA SWAP
//      uint delta(uint bits, uint mask, int shift);
// PARAMETERS:
//      bits: the bit array to permute
//      mask:
//      shift:
// RETURNS:
//      -
#define DELTA_DECLARATION(N) \
    uint##N##_t delta##N(uint##N##_t bits, uint##N##_t mask, int shift);
TEMPLATE_STD(DELTA_DECLARATION)

// BIT SWAP
//      uint bswap(uint bits, int i, int j);
// PARAMETERS:
//      bits: the bit array to permute
//      i, j: the indices of the bits to swap
// RETURNS:
//      - $bits with the bit at $i swapped with the bit at $j
#define BSWAP_DECLARATION(N) \
    uint##N##_t bswap##N(uint##N##_t bits, int i, int j);
TEMPLATE_STD(BSWAP_DECLARATION)

// BIT-RANGE SWAP
//      uint rswap(uint bits, int i, int j, int len);
// PARAMETERS:
//      bits: the bit array to permute
//      i, j: the lower indices of the bit ranges to swap
//      len: the number of bits to swap at each bit-index
// RETURNS:
//      - $bits with the $len bits above $i swapped with the $len bits above $j
//      - undefined, if the specified bit-ranges ovelap
#define RSWAP_DECLARATION(N) \
    uint##N##_t rswap##N(uint##N##_t bits, int i, int j, int len);
TEMPLATE_STD(RSWAP_DECLARATION)

// REVERSE
//      uint rev(uint bits);
// PARAMETERS:
//      bits: the bit array to permute
// RETURNS:
//      - the reverse of $bits
#define REV_DECLARATION(N) \
    uint##N##_t rev##N(uint##N##_t bits);
TEMPLATE_STD(REV_DECLARATION)

// SHUFFLE
//      uint shuf(uint bits);
// PARAMETERS:
//      bits: the bit array to permute
// RETURNS:
//      - $bits after a perfect outer-shuffle
#define SHUF_DECLARATION(N) \
    uint##N##_t shuf##N(uint##N##_t bits);
TEMPLATE_STD(SHUF_DECLARATION)

// INVERSE SHUFFLE
//      uint ishuf(uint bits);
// PARAMETERS:
//      bits: the bit array to permute
// RETURNS:
//      - $bits after reversing a perfect outer-shuffle
#define ISHUF_DECLARATION(N) \
    uint##N##_t ishuf##N(uint##N##_t bits);
TEMPLATE_STD(ISHUF_DECLARATION)

// GROUP
//      uint grp(uint bits, uint mask);
// PARAMETERS:
//      bits: the bit value to permute
//      mask:
// RETURNS:
//      -
#define GRP_DECLARATION(N) \
    uint##N##_t grp##N(uint##N##_t bits, uint##N##_t mask);
TEMPLATE_STD(GRP_DECLARATION)

// UNGROUP
//      uint igrp(uint bits, uint mask);
// PARAMETERS:
//      bits: the bit value to permute
//      mask:
// RETURNS:
//      -
#define IGRP_DECLARATION(N) \
    uint##N##_t igrp##N(uint##N##_t bits, uint##N##_t mask);
TEMPLATE_STD(IGRP_DECLARATION)

// OMEGA-FLIP
//      uint omflip(uint bits, uint mask, uint8_t ctrl);
// PARAMETERS:
//      bits: the bit array to permute
//      mask:
//      ctrl:
// RETURNS:
//      -
#define OMFLIP_DECLARATION(N) \
    uint##N##_t omflip##N(uint##N##_t bits, uint##N##_t mask, uint8_t ctrl);
TEMPLATE_STD(OMFLIP_DECLARATION)

// BUTTERFLY NETWORK
//      uint bfly(uint bits, uint mask);
// PARAMETERS:
//      bits: the bit array to permute
//      mask:
// RETURNS:
//      -
#define BFLY_DECLARATION(N) \
    uint##N##_t bfly##N(uint##N##_t bits, uint##N##_t mask);
TEMPLATE_STD(BFLY_DECLARATION)

// INVERSE BUTTERFLY NETWORK
//      uint ibfly(uint bits, uint mask);
// PARAMETERS:
//      bits: the bit array to permute
//      mask:
// RETURNS:
//      -
#define IBFLY_DECLARATION(N) \
    uint##N##_t ibfly##N(uint##N##_t bits, uint##N##_t mask);
TEMPLATE_STD(IBFLY_DECLARATION)

// TRANSPOSE
//      uint trans(uint bits, int rows);
// PARAMETERS:
//      bits: the bit matrix to permute
//      rows: the number of rows in the matrix
// RETURNS:
//      -
#define TRANS_DECLARATION(N) \
    uint##N##_t trans##N(uint##N##_t bits, int rows);
TEMPLATE_STD(TRANS_DECLARATION)

/////////////////////////
///   MANIPULATIONS   ///
/////////////////////////

// LINEAR-FEEDBACK SHIFT REGISTER
//      uint lfsr(uint bits);
// PARAMETERS:
//      bits: the bit value to manipulate
// RETURNS:
//      - the next value of an LFSR containing $bits as its state
#define LFSR_DECLARATION(N) \
    uint##N##_t lfsr##N(uint##N##_t bits);
TEMPLATE_STD(LFSR_DECLARATION)

// INVERSE LINEAR-FEEDBACK SHIFT REGISTER
//      uint ilfsr(uint bits);
// PARAMETERS:
//      bits: the bit value to manipulate
// RETURNS:
//      - the previous value of an LFSR containing $bits as its state
#define ILFSR_DECLARATION(N) \
    uint##N##_t ilfsr##N(uint##N##_t bits);
TEMPLATE_STD(ILFSR_DECLARATION)

// BITWISE TERNARY
//      uint tern(uint xbits, uint ybits, uint ctrl);
// PARAMETERS:
//      xbits: the bit values for a 'true' result
//      ybits: the bit values for a 'false' result
//      ctrl: the conditional bits
// RETURNS:
//      - the output with the i-th bit equal to the i-th bit from $xbits
//        if $ctrl contains a 1 in that bit-position, otherwise the i-th bit of
//        the output is equal to the i-th bit of $ybits
#define TERN_DECLARATION(N) \
    uint##N##_t tern##N(uint##N##_t xbits, uint##N##_t ybits, uint##N##_t ctrl);
TEMPLATE_STD(TERN_DECLARATION)

// BINARY REPRESENTATION TO GRAY CODE
//      uint gray(uint bits);
// PARAMETERS:
//      bits: the bit value to manipulate
// RETURNS:
//      - the gray code representation of the binary value $bits
#define GRAY_DECLARATION(N) \
    uint##N##_t gray##N(uint##N##_t bits);
TEMPLATE_STD(GRAY_DECLARATION)

// GRAY CODE TO BINARY REPRESENTATION
//      uint igray(uint bits);
// PARAMETERS:
//      bits: the bit value to manipulate
// RETURNS:
//      - the binary representation of the gray code $bits
#define IGRAY_DECLARATION(N) \
    uint##N##_t igray##N(uint##N##_t bits);
TEMPLATE_STD(IGRAY_DECLARATION)

// EXTRACT LEFT
//      uint extl(uint bits, uint mask);
// PARAMETERS:
//      bits: the bit value to manipulate
//      mask:
// RETURNS:
//      -
#define EXTL_DECLARATION(N) \
    uint##N##_t extl##N(uint##N##_t bits, uint##N##_t mask);
TEMPLATE_STD(EXTL_DECLARATION)

// EXTRACT RIGHT
//      uint extr(uint bits, uint mask);
// PARAMETERS:
//      bits: the bit value to manipulate
//      mask:
// RETURNS:
//      -
#define EXTR_DECLARATION(N) \
    uint##N##_t extr##N(uint##N##_t bits, uint##N##_t mask);
TEMPLATE_STD(EXTR_DECLARATION)

// DEPOSIT LEFT
//      uint depl(uint bits, uint mask);
// PARAMETERS:
//      bits: the bit value to manipulate
//      mask:
// RETURNS:
//      -
#define DEPL_DECLARATION(N) \
    uint##N##_t depl##N(uint##N##_t bits, uint##N##_t mask);
TEMPLATE_STD(DEPL_DECLARATION)

// DEPOSIT RIGHT
//      uint depr(uint bits, uint mask);
// PARAMETERS:
//      bits: the bit value to manipulate
//      mask:
// RETURNS:
//      -
#define DEPR_DECLARATION(N) \
    uint##N##_t depr##N(uint##N##_t bits, uint##N##_t mask);
TEMPLATE_STD(DEPR_DECLARATION)

// //////////////////////////////////
// ////    P-SQUARE FUNCTIONS    ////
// //////////////////////////////////

#endif // _BITC_H_
