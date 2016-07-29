#ifndef _BITS_HH_
#define _BITS_HH_

#include <cstdint>

////////////////////////////
////    CALCULATIONS    ////
////////////////////////////

// POPULATION:
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         the number of set (non-zero) bits in the word
template <typename T>
int pop(T bits);

// PARITY:
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         0, if the number of set bits is even
//         1, otherwise
template <typename T>
int par(T bits);

// COUNT TRAILING ZEROS:
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         the number of least significant 0-bits before the first set bit
template <typename T>
int ctz(T bits);

// COUNT TRAILING ZEROS:
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         the number of most significant 0-bits before the first set bit
template <typename T>
int clz(T bits);

// LONGEST CHAIN OF SET BITS
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         the length of the longest chain of set bits
template <typename T>
int mxset(T bits);

// LONGEST CHAIN OF SET BITS
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         the length of the shortest chain of set bits
template <typename T>
int mnset(T bits);

// MAXIMUM
//   - Parameters:
//         x, y: the values to compare
//   - Returns:
//         the maximum of the $x and $y
template <typename T>
T max(T x, T y);

// MINIMUM
//   - Parameters:
//         x, y: the values to compare
//   - Returns:
//         the minimum of the $x and $y
template <typename T>
T min(T x, T y);

// GREATEST COMMON DIVISOR
//   - Parameters:
//         x, y: the values to calculate on
//   - Returns:
//         the largest integer that divides both $x and $y without a remainder
template <typename T>
T gcd(T x, T y);

// BINARY LOGARITHM
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         returns the base-2 logarithm of $bits, rounded-down
template <typename T>
T lb(T bits);

// IS POWER OF 2
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         0, if $bits is 0
//         1, if $bits is a power-of-2
//         0, otherwise
template <typename T>
int ipow(T bits);

// CEIL POWER OF 2
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         1, if $bits is 0
//         $bits, if $bits is already a power-of-2
//         0, if $bits is greater than the maximum power-of-2 the uint can hold
//         the next greatest power-of-2 greater than $bits, otherwise
template <typename T>
T cpow(T bits);

// FLOOR POWER OF 2
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         0, if $bits is 0
//         $bits, if $bits is already a power-of-2
//         the next smallest power-of-2 greater than $bits, otherwise
template <typename T>
T fpow(T bits);

// LEAST SIGNIFICANT BIT
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         a mask with only the least significant bit of $bits set
template <typename T>
T lsb(T bits);

// MOST SIGNIFICANT BIT
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         a mask with only the most significant bit of $bits set
template <typename T>
T msb(T bits);

////////////////////////////
////    PERMUTATIONS    ////
////////////////////////////

// ROTATE LEFT
//   - Parameters:
//         bits: the bit array to permute
//         rot: the number of positions to rotate left
//   - Returns:
//         $bits cyclically shifted to the left by $rot
template <typename T>
T rol(T bits, int rot);

// ROTATE RIGHT
//   - Parameters:
//         bits: the bit array to permute
//         rot: the number of positions to rotate right
//   - Returns:
//         $bits cyclically shifted to the right by $rot
template <typename T>
T ror(T bits, int rot);

// DELTA SWAP
//   - Parameters:
//         bits: the bit array to permute
//         mask:
//         shift:
//   - Returns:
//         .
template <typename T>
T delta(T bits, T mask, int del);

// BIT SWAP
//   - Parameters:
//         bits: the bit array to permute
//         i, j: the indices of the bits to swap
//   - Returns:
//         $bits with the bit at $i swapped with the bit at $j
template <typename T>
T bswap(T bits, int i, int j);

// BIT-RANGE SWAP
//   - Parameters:
//         bits: the bit array to permute
//         i, j: the lower indices of the bit ranges to swap
//         len: the number of bits to swap at each bit-index
//   - Returns:
//         $bits with the $len bits above $i swapped with the $len bits above $j
//         undefined, if the specified bit-ranges ovelap
template <typename T>
T rswap(T bits, int i, int j, int len);

// REVERSE
//   - Parameters:
//         bits: the bit array to permute
//   - Returns:
//         the reverse of $bits
template <typename T>
T rev(T bits);

// SHUFFLE
//   - Parameters:
//         bits: the bit array to permute
//   - Returns:
//         $bits after a perfect outer-shuffle
template <typename T>
T shuf(T bits);

// INVERSE SHUFFLE
//   - Parameters:
//         bits: the bit array to permute
//   - Returns:
//         $bits after reversing a perfect outer-shuffle
template <typename T>
T ishuf(T bits);

// GROUP
//   - Parameters:
//         bits: the bit value to permute
//         mask:
//   - Returns:
//         .
template <typename T>
T grp(T bits, T mask);

// UNGROUP
//   - Parameters:
//         bits: the bit value to permute
//         mask:
//   - Returns:
//         .
template <typename T>
T igrp(T bits, T mask);

// OMEGA-FLIP
//   - Parameters:
//         bits: the bit array to permute
//         mask:
//         ctrl:
//   - Returns:
//         .
template <typename T>
T omflip(T bits, T mask, uint8_t ctrl);

// BUTTERFLY NETWORK
//   - Parameters:
//         bits: the bit array to permute
//         mask:
//   - Returns:
//         .
template <typename T>
T bfly(T bits, T mask);

// INVERSE BUTTERFLY NETWORK
//   - Parameters:
//         bits: the bit array to permute
//         mask:
//   - Returns:
//         .
template <typename T>
T ibfly(T bits, T mask);

// TRANSPOSE
//   - Parameters:
//         bits: the bit matrix to permute
//         rows: the number of rows in the matrix
//   - Returns:
//         .
template <typename T>
T trans(T bits, int rows);

/////////////////////////////
////    MANIPULATIONS    ////
/////////////////////////////

// // LINEAR-FEEDBACK SHIFT REGISTER
// //   - Parameters:
// //         bits: the bit value to manipulate
// //   - Returns:
// //         the next value of an LFSR containing $bits as its state
// template <typename T>
// T lfsr(T bits);

// // INVERSE LINEAR-FEEDBACK SHIFT REGISTER
// //   - Parameters:
// //         bits: the bit value to manipulate
// //   - Returns:
// //         the previous value of an LFSR containing $bits as its state
// template <typename T>
// T ilfsr(T bits);

// BITWISE TERNARY
//   - Parameters:
//         xbits: the bit values for a 'true' result
//         ybits: the bit values for a 'false' result
//         ctrl: the conditional bits
//   - Returns:
//         the output with the i-th bit equal to the i-th bit from $xbits
//           if $ctrl contains a 1 in that bit-position, otherwise the i-th bit of
//           the output is equal to the i-th bit of $ybits
template <typename T>
T tern(T xbits, T ybits, T ctrl);

// BINARY REPRESENTATION TO GRAY CODE
//   - Parameters:
//         bits: the bit value to manipulate
//   - Returns:
//         the gray code representation of the binary value $bits
template <typename T>
T gray(T bits);

// GRAY CODE TO BINARY REPRESENTATION
//   - Parameters:
//         bits: the bit value to manipulate
//   - Returns:
//         the binary representation of the gray code $bits
template <typename T>
T igray(T bits);

// EXTRACT LEFT
//   - Parameters:
//         bits: the bit value to manipulate
//         mask:
//   - Returns:
//         .
template <typename T>
T extl(T bits, T mask);

// EXTRACT RIGHT
//   - Parameters:
//         bits: the bit value to manipulate
//         mask:
//   - Returns:
//         .
template <typename T>
T extr(T bits, T mask);

// DEPOSIT LEFT
//   - Parameters:
//         bits: the bit value to manipulate
//         mask:
//   - Returns:
//         .
template <typename T>
T depl(T bits, T mask);

// DEPOSIT RIGHT
//   - Parameters:
//         bits: the bit value to manipulate
//         mask:
//   - Returns:
//         .
template <typename T>
T depr(T bits, T mask);

#endif // _BITS_HH_
