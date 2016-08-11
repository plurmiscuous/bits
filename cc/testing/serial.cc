#include <cstdint>
#include <cstddef>
#include <cassert>

#include "serial.hh"
#include "../bits.hh"
#include "../inc/extint.hh"

template <typename T>
int serial::pop(T bits) {
    int set = 0;
    for (set = 0; bits; bits >>= 1)
        set += static_cast<int>(bits & 0x1);
    return set;
}

template <typename T>
int serial::par(T bits) {
    bool parity = 0;
    while (bits) {
        parity = !parity;
        bits = bits & (bits - 1);
    }
    return parity;
}

template <typename T>
int serial::ctz(T bits) {
    if (!bits)
        return bits::BITS<T>();

    int n = 0;
    T mask = 1;
    while ((bits & mask) == 0) {
        n++;
        mask <<= 1;
    }
    return n;
}

template <typename T>
int serial::clz(T bits) {
    if (!bits)
        return bits::BITS<T>();

    int n = 0;
    T mask = (T) 1 << (bits::BITS<T>() - 1);
    while ((bits & mask) == 0) {
        n++;
        mask >>= 1;
    }
    return n;
}

template <typename T>
int serial::mxset(T bits) {
    int set = 0;
    int max = 0;

    while (bits) {
        if (bits & 0x1)
            ++set;
        else {
            if (set > max)
                max = set;
            set = 0;
        }
        bits >>= 1;
    }

    if (set > max)
        max = set;

    return max;
}

template <typename T>
int serial::mnset(T bits) {
    int set = 0;
    int min = 0;

    while (bits) {
        if (bits & 0x1)
            ++set;
        else {
            if (!min || (set && set < min))
                min = set;
            set = 0;
        }
        bits >>= 1;
    }

    if (!min || (set && set < min))
        min = set;

    return min;
}

template <typename T>
T serial::max(T x, T y) {
    return x > y ? x : y;
}

template <typename T>
T serial::min(T x, T y) {
    return x < y ? x : y;
}

template <typename T>
T serial::gcd(T x, T y) {
    while (x != 0) {
        T tmp = x;
        x = y % x;
        y = tmp;
    }
    return y;
}

template <typename T>
T serial::lb(T bits) {
    int log = 0;
    while (bits >>= 1)
        ++log;
    return log;
}

template <typename T>
bool serial::ipow(T bits) {
    T b0 = bits;
    for (int i = 1; i < bits::BITS<T>(); i <<= 1)
        bits |= bits >> i;
    bits = (bits >> 1) + 1;
    return bits == b0;
}

template <typename T>
T serial::cpow(T bits) {
    if (!bits)
        return 1;

    T b0 = bits;
    for (int i = 1; i < bits::BITS<T>(); i <<= 1)
        bits |= bits >> i;
    bits = (bits >> 1) + 1;
    return bits == b0 ? b0 : (bits << 1);
}

template <typename T>
T serial::fpow(T bits) {
    for (int i = 1; i < bits::BITS<T>(); i <<= 1)
        bits |= bits >> i;
    bits = (bits >> 1) + (bits != 0);
    return bits;
}

template <typename T>
T serial::lsb(T bits) {
    if (!bits)
        return bits;

    int i = 0;
    while ((bits & 0x1) == 0) {
        ++i;
        bits >>= 1;
    }
    return T(1) << i;
}

template <typename T>
T serial::msb(T bits) {
    if (!bits)
        return bits;

    int i = 0;
    while (bits >>= 1)
        ++i;
    return T(1) << i;
}

template <typename T>
T serial::rev(T bits) {
    T rev = 0;
    for (std::size_t i = 0; i < bits::BITS<T>() - 1; ++i) {
        rev |= bits & 0x1;
        rev <<= 1;
        bits >>= 1;
    }
    rev |= bits & 0x1;
    return rev;
}

template <typename T>
T serial::shuf(T bits) {
    T lo = bits;
    T hi = (bits >> (bits::BITS<T>() / 2));
    T shuf = 0;
    for (std::size_t i = 0; i < bits::BITS<T>() / 2; ++i)
        shuf |= (lo & T(1) << i) << i | (hi & T(1) << i) << (i + 1);
    return shuf;
}

template <typename T>
T serial::ishuf(T bits) {
    T one = 1;
    T lo = bits & bits::WORD<T>(0);
    T hi = bits & ~bits::WORD<T>(0);
    T ishuf = 0;
    for (std::size_t i = 0; i < bits::BITS<T>() / 2; ++i)
        ishuf |= ((hi & one << (2 * i + 1)) << (bits::BITS<T>() / 2 - 1 - i))
                | ((lo & one << (2 * i)) >> i);
    return ishuf;
}

// Group:
//     Pseudocode for the GRP operation:
//         uint grp(uint R1, uint R2) {
//             uint R3 = 0;
//             int j = 0;
//             for (int i = 0; i < N; i++)
//                 if (R2[i] == 1)
//                     R3[j++] = R1[i];
//             for (int i = 0; i < N; i++)
//                 if (R2[i] == 0)
//                     R3[j++] = R1[i];
//             return R3;
//         }
// Source:
//     Ruby B. Lee, Zhijie Jerry Shi, Xiao Yang; Efficient Permutation
//         Instructions for Fast Software Cryptography
//         url: http://palms.ee.princeton.edu/PALMSopen/lee01efficient.pdf
//     Ruby B. Lee, Zhijie Jerry Shi; US Patent No. 7174014
//         url: http://patentimages.storage.googleapis.com/pdfs/US7174014.pdf
template <typename T>
T serial::grp(T bits, T mask) {
    T grp = 0;
    int k = 0;

    T b1 = bits;
    T m1 = mask;
    for (int i = bits::BITS<T>(); i--; b1 >>= 1, m1 >>= 1)
        if ((m1 & 0x1) == 1)
            grp |= (b1 & 0x1) << k++;

    T b0 = bits;
    T m0 = mask;
    for (int i = bits::BITS<T>(); i--; b0 >>= 1, m0 >>= 1)
        if ((m0 & 0x1) == 0)
            grp |= (b0 & 0x1) << k++;

    return grp;
}

// Ungroup:
//     Pseudocode for the UNGRP operation:
//         uint ungrp(uint R1, uint R2) {
//             uint R3 = 0;
//             int j = 0;
//             for (int i = 0; i < N; i++)
//                 if (R2[i] == 1)
//                     R3[i] = R1[j++];
//             for (int i = 0; i < N; i++)
//                 if (R2[i] == 0)
//                     R3[i] = R1[j++];
//             return R3;
//         }
// Source:
//     Zhijie Jerry Shi; Bit Permutation Instructions: Architecture,
//         Implementation, and Cryptographic Properties
//         url: http://saluc.engr.uconn.edu/publications/shi_thesis.pdf
template <typename T>
T serial::igrp(T bits, T mask) {
    T igrp = 0;

    T m1 = mask;
    for (int i = 0; i < bits::BITS<T>(); ++i) {
        if ((m1 & 0x1) == 1) {
            igrp |= (bits & 0x1) << i;
            bits >>= 1;
        }
        m1 >>= 1;
    }

    T m0 = mask;
    for (int i = 0; i < bits::BITS<T>(); ++i) {
        if ((m0 & 0x1) == 0) {
            igrp |= (bits & 0x1) << i;
            bits >>= 1;
        }
        m0 >>= 1;
    }

    return igrp;
}

// Omega-Flip:
//     Pseudocode for the OMFLIP operation:
//         uint omflip(uint R1, uint R2, uint8_t c) {
//             uint R3 = 0;
//             for (int i = 0; i < 2; i++)
//                 if (c[i] == 0)
//                     for (int j = 0; j < N / 2; j++)
//                         R3[2 * j] = R1[j];
//                         R3[2 * j + 1] = R1[j + N / 2];
//                         if (R2[j] == 1)
//                             swap(R3[2 * j], R3[2 * j + 1]);
//                 else
//                     for (int j = 0; j < N / 2; j++)
//                         R3[j] = R1[2 * j];
//                         R3[j + N / 2] = R1[2 * j + 1];
//                         if (R2[j + N / 2] == 1)
//                             swap(R3[j], R3[j + N / 2]);
//             return R3;
//         }
// Source:
//     Ruby B. Lee and Xiao Yang; US Patent No. 6952478
//         url: http://patentimages.storage.googleapis.com/pdfs/US6952478.pdf
template <typename T>
T serial::omflip(T bits, T mask, uint8_t opts) {
    T omflip = 0;
    for (int i = 0; i < 2; ++i) {
        T tmp = 0;
        if (((opts >> i) & 0x1) == 0) {
            for (int j = 0; j < bits::BITS<T>() / 2; ++j) {
                tmp |= ((bits >> j) & 0x1) << (2 * j);
                tmp |= ((bits >> (j + bits::BITS<T>() / 2)) & 0x1) << (2 * j + 1);
                if (mask >> j & 0x1)
                    tmp = serial::bswap<T>(tmp, 2 * j, 2 * j + 1);
            }
        } else {
            for (int j = 0; j < bits::BITS<T>() / 2; ++j) {
                tmp |= ((bits >> 2 * j) & 0x1) << j;
                tmp |= ((bits >> (2 * j + 1)) & 0x1) << (j + bits::BITS<T>() / 2);
                if (mask >> (j + i * bits::BITS<T>() / 2) & 0x1)
                    tmp = serial::bswap<T>(tmp, j, j + bits::BITS<T>() / 2);
            }
        }
        omflip = bits = tmp;
    }
    return omflip;
}

// Butterfly Network:
//     Pseudocode for the BFLY operation:
//         uint bfly(uint R1, uint R2) {
//             uint R3 = R1;
//             for (int dist = N / 2; dist > 0; dist = dist / 2)
//                 for (int k = 0; k < N; k += 2 * dist)
//                     for (int j = 0; j < dist; j++)
//                         if (R2[k + j] == 1)
//                             swap(R3[k + j], R3[k + j + dist]);
//             return R3;
//         }
// Source:
//     Ruby B. Lee, Zhijie Jerry Shi, Xiao Yang; Efficient Permutation
//         Instructions for Fast Software Cryptography (Adapted from CROSS
//         pseudocode)
//         url: http://palms.ee.princeton.edu/PALMSopen/lee01efficient.pdf
template <typename T>
T serial::bfly(T bits, T mask) {
    for (int d = bits::BITS<T>() / 2; d > 0; d /= 2)
        for (int k = 0; k < bits::BITS<T>(); k += 2 * d)
            for (int j = 0; j < d; ++j)
                if (mask >> (k + j) & 0x1)
                    bits = serial::bswap<T>(bits, k + j, k + j + d);
    return bits;
}

template <typename T>
T serial::ibfly(T bits, T mask) {
    for (int d = 1; d <= bits::BITS<T>() / 2; d *= 2)
        for (int k = bits::BITS<T>() - 2 * d; k >= 0; k -= 2 * d)
            for (int j = d - 1; j >= 0; --j)
                if (mask >> (k + j) & 0x1)
                    bits = serial::bswap<T>(bits, k + j, k + j + d);
    return bits;
}

// Source:
//     Bit manipulations using BMI2
//         url: https://www.randombit.net/bitbashing/2012/06/22/haswell_bit_permutations.html
//     BMI2
//         url: https://chessprogramming.wikispaces.com/BMI2
template <typename T>
T serial::extr(T bits, T mask) {
    T res = 0;
    int k = 0;

    for (int i = 0; i < bits::BITS<T>(); ++i)
        if (mask >> i & 0x1)
            res |= (bits >> i & 0x1) << k++;

    return res;
}

// Source:
//     Bit manipulations using BMI2
//         url: https://www.randombit.net/bitbashing/2012/06/22/haswell_bit_permutations.html
//     BMI2
//         url: https://chessprogramming.wikispaces.com/BMI2
template <typename T>
T serial::depl(T bits, T mask) {
    T res = 0;
    int k = 0;

    for (int i = 0; i < bits::BITS<T>(); ++i)
        if (mask >> i & 0x1)
            res |= (bits >> k++ & 0x1) << i;

    return res;
}

template <typename T>
T serial::extl(T bits, T mask) {
    T res = 0;
    int k = bits::BITS<T>();
    for (int i = bits::BITS<T>(); i--;)
        if (mask >> i & 0x1)
            res |= (bits >> i & 0x1) << --k;
    return res;
}

template <typename T>
T serial::depr(T bits, T mask) {
    T res = 0;
    int k = bits::BITS<T>();

    for (int i = bits::BITS<T>(); i--;)
        if (mask >> i & 0x1)
            res |= (bits >> --k & 0x1) << i;

    return res;
}

// Source:
//     Inplace (Fixed space) M x N size matrix transpose
//         url: http://www.geeksforgeeks.org/inplace-m-x-n-size-matrix-transpose/
template <typename T>
T serial::trans(T bits, int rows) {
    int cols = bits::BITS<T>() / rows;
    for (int i = 0; i < rows * cols; i++) {
        int j = i;
        do
            j = (j % rows) * cols + (j / rows);
        while (j < i);
        bits = serial::bswap(bits, i, j);
    }
    return bits;
}

template <typename T>
T serial::rol(T bits, int rot) {
    // rotate one bit at a time $rot times
    for (int i = rot; i--;)
        bits = (bits << 1) | (bits >> (bits::BITS<T>() - 1));
    return bits;
}

template <typename T>
T serial::ror(T bits, int rot) {
    // rotate one bit at a time $rot times
    for (int i = rot; i--;)
        bits = (bits >> 1) | (bits << (bits::BITS<T>() - 1));
    return bits;
}

template <typename T>
T serial::bswap(T bits, int i, int j) {
    assert(0 <= i && i < bits::BITS<T>());
    assert(0 <= j && j < bits::BITS<T>());
    // stored bits at indicies
    T bi = (bits >> i) & 0x1;
    T bj = (bits >> j) & 0x1;
    // clear any set bits
    bits &= ~((T(1) << i) | (T(1) << j));
    // update with stored bits
    bits |= (bi << j) | (bj << i);
    return bits;
}

template <typename T>
T serial::rswap(T bits, int i, int j, int len) {
    assert(0 <= i && i < bits::BITS<T>());
    assert(0 <= j && j < bits::BITS<T>());
    assert(0 <= len && i + len <= bits::BITS<T>() && j + len <= bits::BITS<T>());
    assert(i + len < j || i < j + len);
    // generate a mask for $len bits
    T mask = (T(1) << len) - 1;
    // stored $len bits at specified indicies
    T ri = (bits >> i) & mask;
    T rj = (bits >> j) & mask;
    // clear any set bits
    bits &= ~((mask << i) | (mask << j));
    // update with stored bits
    bits |= (ri << j) | (rj << i);
    return bits;
}

#define SERIAL_TEMPLATE(T)                                       \
    template int serial::pop<T>(T bits);                         \
    template int serial::par<T>(T bits);                         \
    template int serial::ctz<T>(T bits);                         \
    template int serial::clz<T>(T bits);                         \
    template int serial::mxset<T>(T bits);                       \
    template int serial::mnset<T>(T bits);                       \
    template T serial::max<T>(T x, T y);                         \
    template T serial::min<T>(T x, T y);                         \
    template T serial::gcd<T>(T x, T y);                         \
    template T serial::lb<T>(T bits);                            \
    template bool serial::ipow<T>(T bits);                       \
    template T serial::cpow<T>(T bits);                          \
    template T serial::fpow<T>(T bits);                          \
    template T serial::lsb<T>(T bits);                           \
    template T serial::msb<T>(T bits);                           \
    template T serial::rev<T>(T bits);                           \
    template T serial::shuf<T>(T bits);                          \
    template T serial::ishuf<T>(T bits);                         \
    template T serial::grp<T>(T bits, T mask);                   \
    template T serial::igrp<T>(T bits, T mask);                  \
    template T serial::omflip<T>(T bits, T mask, uint8_t opts);  \
    template T serial::bfly<T>(T bits, T mask);                  \
    template T serial::ibfly<T>(T bits, T mask);                 \
    template T serial::extr<T>(T bits, T mask);                  \
    template T serial::depl<T>(T bits, T mask);                  \
    template T serial::extl<T>(T bits, T mask);                  \
    template T serial::depr<T>(T bits, T mask);                  \
    template T serial::trans<T>(T bits, int rows);               \
    template T serial::rol<T>(T bits, int rot);                  \
    template T serial::ror<T>(T bits, int rot);                  \
    template T serial::bswap<T>(T bits, int i, int j);           \
    template T serial::rswap<T>(T bits, int i, int j, int len);
TEMPLIFY(SERIAL_TEMPLATE)
