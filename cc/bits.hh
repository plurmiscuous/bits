#ifndef _BITS_HH_
#define _BITS_HH_

#include <cstdint>
#include <cstddef>

#include "inc/extint.hh"

// The ASSERT macro turns on run-time assertions for function arguments, such as
// asserting that shift amounts are non-negative and within the width of data
// type being operated on.
#define ASSERT 1

////////////////////////////
////    CALCULATIONS    ////
////////////////////////////

// POPULATION:
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         the number of set (non-zero) bits in the word
template <typename T>
static int pop(T bits);

// PARITY:
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         0, if the number of set bits is even
//         1, otherwise
template <typename T>
static int par(T bits);

// COUNT TRAILING ZEROS:
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         the number of least significant 0-bits before the first set bit
template <typename T>
static int ctz(T bits);

// COUNT TRAILING ZEROS:
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         the number of most significant 0-bits before the first set bit
template <typename T>
static int clz(T bits);

// LONGEST CHAIN OF SET BITS
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         the length of the longest chain of set bits
template <typename T>
static int mxset(T bits);

// LONGEST CHAIN OF SET BITS
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         the length of the shortest chain of set bits
template <typename T>
static int mnset(T bits);

// MAXIMUM
//   - Parameters:
//         x, y: the values to compare
//   - Returns:
//         the maximum of the $x and $y
template <typename T>
static T max(T x, T y);

// MINIMUM
//   - Parameters:
//         x, y: the values to compare
//   - Returns:
//         the minimum of the $x and $y
template <typename T>
static T min(T x, T y);

// GREATEST COMMON DIVISOR
//   - Parameters:
//         x, y: the values to calculate on
//   - Returns:
//         the largest integer that divides both $x and $y without a remainder
template <typename T>
static T gcd(T x, T y);

// BINARY LOGARITHM
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         returns the base-2 logarithm of $bits, rounded-down
template <typename T>
static T lb(T bits);

// IS POWER OF 2
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         0, if $bits is 0
//         1, if $bits is a power-of-2
//         0, otherwise
template <typename T>
static int ipow(T bits);

// CEIL POWER OF 2
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         1, if $bits is 0
//         $bits, if $bits is already a power-of-2
//         0, if $bits is greater than the maximum power-of-2 the uint can hold
//         the next greatest power-of-2 greater than $bits, otherwise
template <typename T>
static T cpow(T bits);

// FLOOR POWER OF 2
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         0, if $bits is 0
//         $bits, if $bits is already a power-of-2
//         the next smallest power-of-2 greater than $bits, otherwise
template <typename T>
static T fpow(T bits);

// LEAST SIGNIFICANT BIT
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         a mask with only the least significant bit of $bits set
template <typename T>
static T lsb(T bits);

// MOST SIGNIFICANT BIT
//   - Parameters:
//         bits: the value to calculate on
//   - Returns:
//         a mask with only the most significant bit of $bits set
template <typename T>
static T msb(T bits);

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
static T rol(T bits, int rot);

// ROTATE RIGHT
//   - Parameters:
//         bits: the bit array to permute
//         rot: the number of positions to rotate right
//   - Returns:
//         $bits cyclically shifted to the right by $rot
template <typename T>
static T ror(T bits, int rot);

// DELTA SWAP
//   - Parameters:
//         bits: the bit array to permute
//         mask:
//         shift:
//   - Returns:
//         .
template <typename T>
static T delta(T bits, T mask, int shift);

// BIT SWAP
//   - Parameters:
//         bits: the bit array to permute
//         i, j: the indices of the bits to swap
//   - Returns:
//         $bits with the bit at $i swapped with the bit at $j
template <typename T>
static T bswap(T bits, int i, int j);

// BIT-RANGE SWAP
//   - Parameters:
//         bits: the bit array to permute
//         i, j: the lower indices of the bit ranges to swap
//         len: the number of bits to swap at each bit-index
//   - Returns:
//         $bits with the $len bits above $i swapped with the $len bits above $j
//         undefined, if the specified bit-ranges ovelap
template <typename T>
static T rswap(T bits, int i, int j, int len);

// REVERSE
//   - Parameters:
//         bits: the bit array to permute
//   - Returns:
//         the reverse of $bits
template <typename T>
static T rev(T bits);

// SHUFFLE
//   - Parameters:
//         bits: the bit array to permute
//   - Returns:
//         $bits after a perfect outer-shuffle
template <typename T>
static T shuf(T bits);

// INVERSE SHUFFLE
//   - Parameters:
//         bits: the bit array to permute
//   - Returns:
//         $bits after reversing a perfect outer-shuffle
template <typename T>
static T ishuf(T bits);

// GROUP
//   - Parameters:
//         bits: the bit value to permute
//         mask:
//   - Returns:
//         .
template <typename T>
static T grp(T bits, T mask);

// UNGROUP
//   - Parameters:
//         bits: the bit value to permute
//         mask:
//   - Returns:
//         .
template <typename T>
static T igrp(T bits, T mask);

// OMEGA-FLIP
//   - Parameters:
//         bits: the bit array to permute
//         mask:
//         ctrl:
//   - Returns:
//         .
template <typename T>
static T omflip(T bits, T mask, uint8_t ctrl);

// BUTTERFLY NETWORK
//   - Parameters:
//         bits: the bit array to permute
//         mask:
//   - Returns:
//         .
template <typename T>
static T bfly(T bits, T mask);

// INVERSE BUTTERFLY NETWORK
//   - Parameters:
//         bits: the bit array to permute
//         mask:
//   - Returns:
//         .
template <typename T>
static T ibfly(T bits, T mask);

// TRANSPOSE
//   - Parameters:
//         bits: the bit matrix to permute
//         rows: the number of rows in the matrix
//   - Returns:
//         .
template <typename T>
static T trans(T bits, int rows);

/////////////////////////////
////    MANIPULATIONS    ////
/////////////////////////////

// // LINEAR-FEEDBACK SHIFT REGISTER
// //   - Parameters:
// //         bits: the bit value to manipulate
// //   - Returns:
// //         the next value of an LFSR containing $bits as its state
// template <typename T>
// static T lfsr(T bits);

// // INVERSE LINEAR-FEEDBACK SHIFT REGISTER
// //   - Parameters:
// //         bits: the bit value to manipulate
// //   - Returns:
// //         the previous value of an LFSR containing $bits as its state
// template <typename T>
// static T ilfsr(T bits);

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
static T tern(T xbits, T ybits, T ctrl);

// BINARY REPRESENTATION TO GRAY CODE
//   - Parameters:
//         bits: the bit value to manipulate
//   - Returns:
//         the gray code representation of the binary value $bits
template <typename T>
static T gray(T bits);

// GRAY CODE TO BINARY REPRESENTATION
//   - Parameters:
//         bits: the bit value to manipulate
//   - Returns:
//         the binary representation of the gray code $bits
template <typename T>
static T igray(T bits);

// EXTRACT LEFT
//   - Parameters:
//         bits: the bit value to manipulate
//         mask:
//   - Returns:
//         .
template <typename T>
static T extl(T bits, T mask);

// EXTRACT RIGHT
//   - Parameters:
//         bits: the bit value to manipulate
//         mask:
//   - Returns:
//         .
template <typename T>
static T extr(T bits, T mask);

// DEPOSIT LEFT
//   - Parameters:
//         bits: the bit value to manipulate
//         mask:
//   - Returns:
//         .
template <typename T>
static T depl(T bits, T mask);

// DEPOSIT RIGHT
//   - Parameters:
//         bits: the bit value to manipulate
//         mask:
//   - Returns:
//         .
template <typename T>
static T depr(T bits, T mask);

#if ASSERT
    #include <cassert>
#else
    #define assert(x) ((void)(0))  // no side-effects
#endif

/////////////////////////////
////    N-BIT SUPPORT    ////
/////////////////////////////

template <typename T>
constexpr int BITS() {
    return sizeof(T) << 3;
}

template <typename T>
constexpr int LOG(int p = 3, std::size_t s = 1) {
    return sizeof(T) == s ? p : LOG<T>(p + 1, s << 1);
}

template <typename T>
constexpr T ONE() {
    return T(1);
}

template <typename T>
constexpr T ALL() {
    return T(-1);
}

template <typename T>
constexpr T WORD(int idx) {
    return T(-1) / ((T(1) << (T(1) << idx)) + 1);
}

template <typename T>
constexpr T SHUF(int idx) {
    return WORD<T>(idx + 1) & ~WORD<T>(idx);
}

///////////////////////////////
////    IMPLEMENTATIONS    ////
///////////////////////////////

// POPULATION
template <typename T>
static int pop(T bits) {
    for (int i = 0; i < LOG<T>(); ++i)
        bits = (bits & WORD<T>(i)) + ((bits >> (1 << i)) & WORD<T>(i));

    return static_cast<int>(bits);
}

// PARITY
template <typename T>
static int par(T bits) {
    for (int i = BITS<T>(); i >>= 1;)
        bits ^= bits >> i;

    return static_cast<int>(bits & 0x1);
}

// COUNT TRAILING ZEROS
template <typename T>
static int ctz(T bits) {
    int n = 1;
    T mask = ALL<T>();

    for (int i = BITS<T>() >> 1; i > 1; i >>= 1) {
        mask >>= i;
        if ((bits & mask) == 0) {
            n += i;
            bits >>= i;
        }
    }

    return static_cast<int>((-(bits == 0) & BITS<T>()) | (-(bits != 0) & (n - (bits & 1))));
}

// COUNT LEADING ZEROS
template <typename T>
static int clz(T bits) {
    int n = 0;
    T mask = ALL<T>() >> (BITS<T>() >> 1);

    for (int i = BITS<T>(); i >>= 1;) {
        if (bits <= mask) {
            n += i;
            bits <<= i;
        }
        mask |= mask << (i >> 1);
    }

    return static_cast<int>((-(bits == 0) & BITS<T>()) | (-(bits != 0) & n));
}

// LONGEST CHAIN OF SET BITS
template <typename T>
static int mxset(T bits) {
    int k;
    for (k = 0; bits; ++k)
        bits &= (bits >> 1);

    return k;
}

// SHORTEST CHAIN OF SET BITS
template <typename T>
static int mnset(T bits) {
    T dn = bits & ~(bits >> 1);
    T up = bits & ~(bits << 1);

    int k;
    for (k = 1; bits && (dn & up) == 0; ++k)
        up <<= 1;

    return k - static_cast<int>(!bits);
}

// MAXIMUM
template <typename T>
static T max(T x, T y) {
    return x ^ ((x ^ y) & -(x < y));
}

// MINIMUM
template <typename T>
static T min(T x, T y) {
    return y ^ ((x ^ y) & -(x < y));
}

// GREATEST COMMON DIVISOR
template <typename T>
static T gcd(T x, T y) {
    while (y != 0) {
        y ^= x %= y;
        y ^= x ^= y;
    }
    return x;
}

// BINARY LOGARITHM
template <typename T>
static T lb(T bits) {
    T m = ALL<T>();
    T log = 0;

    for (int i = LOG<T>(); i--;) {
        m >>= (1 << i);
        T shift = (bits > m) << i;
        bits >>= shift;
        log |= shift;
    }

    return log;
}

// IS POWER OF 2
template <typename T>
static int ipow(T bits) {
    return bits && (bits & (bits - 1)) == 0;
}

// CEIL POWER OF 2
template <typename T>
static T cpow(T bits) {
    bits += bits == 0;
    --bits;
    for (int i = BITS<T>(); (i >>= 1) != 0;)
        bits |= bits >> i;
    ++bits;
    return bits;
}

// FLOOR POWER OF 2
template <typename T>
static T fpow(T bits) {
    for (int i = BITS<T>(); (i >>= 1) != 0;)
        bits |= bits >> i;
    return bits - (bits >> 1);
}

// ISOLATE LEAST SIGNIFICANT SET BIT
template <typename T>
static T lsb(T bits) {
    return bits & -bits;
}

// ISOLATE MOST SIGNIFICANT SET BIT
template <typename T>
static T msb(T bits) {
    for (int i = BITS<T>(); (i >>= 1) != 0;)
        bits |= bits >> i;
    return (bits >> 1) + (bits != 0);
}

////////////////////////////
////    PERMUTATIONS    ////
////////////////////////////

// ROTATE LEFT
template <typename T>
static T rol(T bits, int rot) {
    assert(0 <= rot && rot < BITS<T>());
    return (bits << rot) | (bits >> (BITS<T>() - rot));
}

// ROTATE RIGHT
template <typename T>
static T ror(T bits, int rot) {
    assert(0 <= rot && rot < BITS<T>());
    return (bits << (BITS<T>() - rot)) | (bits >> rot);
}

// DELTA SWAP
template <typename T>
static T delta(T bits, T mask, int delta) {
    assert(0 <= delta && delta < BITS<T>());
    T tmp = (bits ^ (bits >> delta)) & mask;
    bits ^= tmp ^ (tmp << delta);
    return bits;
}

// SWAPPING INDIVIDUAL BITS
template <typename T>
static T bswap(T bits, int i, int j) {
    assert(0 <= i && i < BITS<T>());
    assert(0 <= j && j < BITS<T>());
    T tmp = ((bits >> i) ^ (bits >> j)) & 1;
    return bits ^ ((tmp << i) | (tmp << j));
}

// SWAPPING BIT RANGES
template <typename T>
static T rswap(T bits, int i, int j, int len) {
    assert(0 <= len && len <= BITS<T>());
    assert(0 <= i && i < BITS<T>() && i + len <= BITS<T>());
    assert(0 <= j && j < BITS<T>() && j + len <= BITS<T>());
    assert(i + len < j || i < j + len);
    T tmp = ((bits >> i) ^ (bits >> j)) & ((ONE<T>() << len) - 1);
    return bits ^ ((tmp << i) | (tmp << j));
}

// REVERSE
template <typename T>
static T rev(T bits) {
    for (int i = 0; i < LOG<T>(); ++i)
        bits = (bits & WORD<T>(i)) << (1 << i) | (bits & ~WORD<T>(i)) >> (1 << i);
    return bits;
}

// PERFECT OUTER-SHUFFLE
template <typename T>
static T shuf(T bits) {
    for (int i = LOG<T>() - 1; i--;)
        bits = delta(bits, SHUF<T>[i], 1 << i);
    return bits;
}

// PERFECT OUTER-UNSHUFFLE
template <typename T>
static T ishuf(T bits) {
    for (int i = 0; i < LOG<T>() - 1; ++i)
        bits = delta(bits, SHUF<T>[i], 1 << i);
    return bits;
}

// OMFLIP
template <typename T>
static T omflip(T bits, T mask, uint8_t opts) {
    for (int i = 0; i < 2; ++i) {
        T m = (mask >> (i * (BITS<T>() >> 1))) & WORD<T>(LOG<T>() - 1);
        if (((opts >> i) & 0x1) == 0) {
            bits = delta(bits, m, BITS<T>() >> 1);
            bits = shuf(bits);
        } else {
            bits = ishuf(bits);
            bits = delta(bits, m, BITS<T>() >> 1);
        }
    }
    return bits;
}

// BUTTERFLY NETWORK
template <typename T>
static T bfly(T bits, T mask) {
    for (int i = LOG<T>(); i--;)
        bits = delta(bits, mask & WORD<T>(i), 1 << i);
    return bits;
}

// INVERSE-BUTTERFLY NETWORK
template <typename T>
static T ibfly(T bits, T mask) {
    for (int i = 0; i < LOG<T>(); ++i)
        bits = delta(bits, mask & WORD<T>(i), 1 << i);
    return bits;
}

// MATRIX TRANSPOSE
template <typename T>
static T trans(T bits, int rows) {
    assert(((BITS<T>() / rows) * rows) == BITS<T>());
    int c = LOG<T>() - lb(rows);
    int g = gcd(LOG<T>(), c);
    int d = LOG<T>() / g - 1;

    for (int i = 0; i < g; ++i) {
        for (int j = 0, k = i, n = i + c; j < d; ++j, k = n, n += c) {
            if (n >= LOG<T>())
                n -= LOG<T>();
            if (n != k) {
                int mx = max(n, k);
                int mn = k ^ n ^ mx;
                int sh = (1 << mx) - (1 << mn);
                bits = delta(bits, WORD<T>(mx) & ~WORD<T>(mn), sh);
            }
        }
    }
    return bits;
}

/////////////////////////////
////    MANIPULATIONS    ////
/////////////////////////////

// // LFSR WITH MAXIMAL-LENGTH SEQUENCE
// template <typename T>
// static T lfsr(T bits) {
//     bits = (bits >> 1) ^ ((-(bits & 0x1)) & FTAPS##N);
//     return bits;
// }

// // INVERSE LFSR WITH MAXIMAL-LENGTH SEQUENCE
// template <typename T>
// static T ilfsr(T bits) {
//     bits = (bits << 1) ^ (-(bits >> (BITS<T>() - 1)) & RTAPS##N);
//     return bits;
// }

// BITWISE TERNARY
template <typename T>
static T tern(T xbits, T ybits, T mask) {
    return (mask & (xbits ^ ybits)) ^ ybits;
}

// BINARY TO GRAY CODE
template <typename T>
static T gray(T bits) {
    return bits ^ (bits >> 1);
}

// GRAY TO BINARY CODE
template <typename T>
static T igray(T bits) {
    for (int i = 1; i < BITS<T>(); i <<= 1)
        bits ^= bits >> i;
    return bits;
}

// EXTRACT LEFT
template <typename T>
static T extl(T bits, T mask) {
    bits &= mask;
    T m1 = T(~mask) >> 1;

    for (int i = 0; i < LOG<T>(); ++i) {
        T m = m1;
        for (int j = 1; j < BITS<T>(); j <<= 1)
            m ^= (m >> j);

        T mv = m & mask;
        mask = (mask ^ mv) | (mv << (ONE<T>() << i));

        T mt = bits & mv;
        bits = (bits ^ mt) | (mt << (ONE<T>() << i));
        m1 &= ~m;
    }

    return bits;
}

// EXTRACT RIGHT
template <typename T>
static T extr(T bits, T mask) {
    bits &= mask;
    T m1 = ~mask << 1;

    for (int i = 0; i < LOG<T>(); ++i) {
        T m = m1;
        for (int j = 1; j < BITS<T>(); j <<= 1)
            m ^= (m << j);

        T mv = m & mask;
        mask = (mask ^ mv) | (mv >> (ONE<T>() << i));

        T mt = bits & mv;
        bits = (bits ^ mt) | (mt >> (ONE<T>() << i));
        m1 &= ~m;
    }

    return bits;
}

// DEPOSIT LEFT
template <typename T>
static T depl(T bits, T mask) {
    T masks[LOG<T>()];
    T m0 = mask;
    T m1 = ~mask << 1;

    for (int i = 0; i < LOG<T>(); ++i) {
        T m = m1;
        for (int j = 1; j < BITS<T>(); j <<= 1)
            m ^= (m << j);

        masks[i] = m & mask;
        mask = (mask ^ masks[i]) | (masks[i] >> (ONE<T>() << i));
        m1 &= ~m;
    }

    for (int i = LOG<T>(); i--;)
        bits ^= ((bits ^ (bits << (ONE<T>() << i))) & masks[i]);

    return bits & m0;
}

// DEPOSIT RIGHT
template <typename T>
static T depr(T bits, T mask) {
    T masks[LOG<T>()];
    T m0 = mask;
    T m1 = T(~mask) >> 1;

    for (int i = 0; i < LOG<T>(); ++i) {
        T m = m1;
        for (int j = 1; j < BITS<T>(); j <<= 1)
            m ^= (m >> j);

        masks[i] = m & mask;
        mask = (mask ^ masks[i]) | (masks[i] << (ONE<T>() << i));
        m1 &= ~m;
    }

    for (int i = LOG<T>(); i--;)
        bits ^= (bits ^ (bits >> (ONE<T>() << i))) & masks[i];

    return bits & m0;
}

// GROUP
template <typename T>
static T grp(T bits, T mask) {
    return extr(bits, mask) | extl(bits, ~mask);
}

// UNGROUP
template <typename T>
static T igrp(T bits, T mask) {
    return depr(bits, ~mask) | depl(bits, mask);
}

#endif // _BITS_HH_
