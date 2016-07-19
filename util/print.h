#ifndef _PRINT_H_
#define _PRINT_H_

#include "../inc/extint.h"

#define FMT8    "0x%02hhX"
#define FMT16   "0x%04hX"
#define FMT32   "0x%08X"
#define FMT64   "0x%016llX"
#define FMT128  "0x%s"
#define FMTBSTR "0b%s"

uint8_t  print8(uint8_t u8);
uint16_t print16(uint16_t u16);
uint32_t print32(uint32_t u32);
uint64_t print64(uint64_t u64);
char*    print128(uint128_t u128);
void     printMxN(void* matrix, int rows, int cols);

#define print(X)                \
    _Generic((X),               \
        uint8_t   : print8,     \
        uint16_t  : print16,    \
        uint32_t  : print32,    \
        uint64_t  : print64,    \
        uint128_t : print128    \
)(X)

char* bitstr8(uint8_t bits);
char* bitstr16(uint16_t bits);
char* bitstr32(uint32_t bits);
char* bitstr64(uint64_t bits);
char* bitstr128(uint128_t bits);

#define bitstr(X)               \
    _Generic((X),               \
        uint8_t   : bitstr8,    \
        uint16_t  : bitstr16,   \
        uint32_t  : bitstr32,   \
        uint64_t  : bitstr64,   \
        uint128_t : bitstr128   \
)(X)

#endif // _PRINT_H_
