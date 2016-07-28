#ifndef _PRINT_H_
#define _PRINT_H_

#include "../inc/extint.h"

// Format macros for use in templates along with print*
#define FMT8    "0x%02hhX"
#define FMT16   "0x%04hX"
#define FMT32   "0x%08X"
#define FMT64   "0x%016llX"
#define FMT128  "0x%016llX%016llX"

// Printing macros for use in templates along with FMT*
#define print8(u8)      (u8)
#define print16(u16)    (u16)
#define print32(u32)    (u32)
#define print64(u64)    (u64)
#define print128(u128)  (uint64_t)((u128) >> 64), (uint64_t) (u128)

// Prints a bit-array as a bordered MxN (0,1)-matrix
// INPUT:
//      matrix: the bit array to print
//      rows: the number of rows in the matrix
//      cols: the number of columns in the matrix
void printMxN(void* matrix, int rows, int cols);

#define FMTBSTR "0b%s"

// Prints the binary representation of an unsigned integer value.
// INPUT:
//      bits: the value to print
// RETURNS:
//      - a (0,1)-string representation of $bits
// NOTE:
//      Internally, bitstrN uses a static buffer so only only one bitstr can
//      be used in a single printf statement.
char* bitstr8(uint8_t bits);
char* bitstr16(uint16_t bits);
char* bitstr32(uint32_t bits);
char* bitstr64(uint64_t bits);
char* bitstr128(uint128_t bits);

#endif // _PRINT_H_
