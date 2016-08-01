#ifndef EXTINT_H
#define EXTINT_H

// Extended Integer Support

#include <stdint.h>

// __extension__ typedef          __int128  int128_t;
__extension__ typedef unsigned __int128 uint128_t;

// #define  INT128_MIN (-((uint128_t) 1 << 127))
// #define  INT128_MAX  (( (int128_t) 1 << 126) | (( (int128_t) 1 << 126) -  (int128_t) 1))
#define UINT128_MAX  (((uint128_t) 1 << 127) | (((uint128_t) 1 << 127) - (uint128_t) 1))

#define U8(u8)          UINT8_C(u8)
#define U16(u16)        UINT16_C(u16)
#define U32(u32)        UINT32_C(u32)
#define U64(u64)        UINT64_C(u64)
#define U128(h64, l64)  (((uint128_t) h64 << 64) | l64)

#endif // EXTINT_H
