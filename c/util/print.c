#include <stdio.h>
#include <stdint.h>

#include "print.h"
#include "../bits.h"
#include "../inc/extint.h"
#include "../inc/N.h"

// Prints a bit-array as a bordered MxN (0,1)-matrix
// INPUT:
//      matrix: the bit array to print
//      rows: the number of rows in the matrix
//      cols: the number of columns in the matrix
void printMxN(void* matrix, int rows, int cols) {
    uint8_t* bits = (uint8_t*) matrix;
    int size = rows * cols;
    int bytes = size >> 3;

    // top of border
    printf("+ ");
    for (int io = cols; io--;)
        printf("- ");
    printf("+\n| ");

    // process whole bytes
    for (int b = 0; b < bytes; ++b)
        for (uint8_t mask = 1; mask; mask <<= 1) {
            printf("%d ", !!(bits[b] & mask));
            if (--size % cols == 0)
                printf("|\n%s", b != bytes - 1 || size ? "| " : "");
        }
    // process remaining bits
    for (uint8_t mask = 1; size; mask <<= 1) {
        printf("%d ", !!(bits[bytes] & mask));
        if (--size % cols == 0)
            printf("|\n%s", size ? "| " : "");
    }

    // bottom of border
    printf("+ ");
    for (int io = cols; io--;)
        printf("- ");
    printf("+\n");
}

#define BITSTR_TEMPL(N)                                         \
    char* bitstr##N(uint##N##_t bits) {                         \
        static char buf[BITS##N + 1];                           \
        uint##N##_t mask = (uint##N##_t) 1 << (BITS##N - 1);    \
        for (int i = 0; i < BITS##N; ++i, mask >>= 1)           \
            buf[i] = (bits & mask) ? '1' : '0';                 \
        buf[BITS##N] = 0;                                       \
        return buf;                                             \
    }
TEMPLATE_STD(BITSTR_TEMPL)
