#include <stdio.h>
#include <stdint.h>

#include "print.h"
#include "../bits.h"
#include "../inc/extint.h"
#include "../inc/N.h"

uint8_t print8(uint8_t u8) {
    return u8;
}

uint16_t print16(uint16_t u16) {
    return u16;
}

uint32_t print32(uint32_t u32) {
    return u32;
}

uint64_t print64(uint64_t u64) {
    return u64;
}

char* print128(uint128_t val) {
    static char strbuf[33];

    uint8_t n1 = val >> 120;
    uint64_t n2 = val >> 60 & ((1ULL << 60) - 1);
    uint64_t n3 = val & ((1ULL << 60) - 1);
    snprintf(strbuf, sizeof strbuf, "%.2X%.15llX%.15llX", n1, n2, n3);

    return strbuf;
}

// prints bits as an rows-by-n matrix
void printMxN(void* matrix, int rows, int cols) {
    #define USE_COLOR 1
    #if USE_COLOR
        static const char* COLOR[] = {
            "\033[0;30m",   // 0
            "\033[0;96m"    // 1
        };
        #define RESET "\033[0m"
    #else
        static const char* COLOR[] = { "", "" };
        #define RESET ""
    #endif

    uint8_t* bits = (uint8_t*) matrix;
    int size = rows * cols;
    int bytes = size >> 3;

    // top of border
    printf("+ ");
    for (int io = 0; io < cols; ++io)
        printf("- ");
    printf("+\n| ");

    // process whole bytes
    for (int b = 0; b < bytes; ++b)
        for (uint8_t mask = 1; mask; mask <<= 1) {
            int code = !!(bits[b] & mask);
            printf("%s%d ", COLOR[code], code);
            if (--size % cols == 0)
                printf("%s|\n%s", RESET, b != bytes - 1 || size ? "| " : "");
        }
    // process remaining bits
    for (uint8_t mask = 1; size; mask <<= 1) {
        int code = !!(bits[bytes] & mask);
        printf("%s%d ", COLOR[code], code);
        if (--size % cols == 0)
            printf("%s|\n%s", RESET, size ? "| " : "");
    }

    // bottom of border
    printf("+ ");
    for (int io = 0; io < cols; ++io)
        printf("- ");
    printf("+\n");
}

#define BITSTR(N)                                               \
    char* bitstr##N(uint##N##_t bits) {                         \
        static char buf[BITS##N + 1];                           \
        uint##N##_t mask = (uint##N##_t) 1 << (BITS##N - 1);    \
        for (int i = 0; i < BITS##N; ++i, mask >>= 1)           \
            buf[i] = (bits & mask) ? '1' : '0';                 \
        buf[BITS##N] = 0;                                       \
        return buf;                                             \
    }
TEMPLATE_STD(BITSTR)
