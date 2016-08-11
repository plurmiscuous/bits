#ifndef _EXTINT_HH_
#define _EXTINT_HH_

#include <cstdint>

typedef __uint128_t uint128_t;

#define UINT128_MAX  (((uint128_t) 1 << 127) | (((uint128_t) 1 << 127) - (uint128_t) 1))

#define U8(u8)          UINT8_C(u8)
#define U16(u16)        UINT16_C(u16)
#define U32(u32)        UINT32_C(u32)
#define U64(u64)        UINT64_C(u64)
#define U128(h64, l64)  (((uint128_t) (h64) << 64) | (l64))

#define TEMPLIFY(T) \
    T(uint8_t)      \
    T(uint16_t)     \
    T(uint32_t)     \
    T(uint64_t)     \
    T(uint128_t)

#endif // _EXTINT_HH_
