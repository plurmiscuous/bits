Bits
====

## About

Bits is a bit permutation/manipulation library implemented in both C and C++.

## Usage

### C

The two primary files are `c/bits.c` and the accompanying `c/bits.h`. The files in the `c/inc/` directory are required for compilation.

`c/bits.h` contains generic function declaration macros of the form
```C
uint##N##_t func##N(uint##N##_t);
```
which expand into declarations for each bit-width:
```C
uint8_t func8(uint8_t);
uint16_t func16(uint16_t);
uint32_t func32(uint32_t);
uint64_t func64(uint64_t);
uint128_t func128(uint128_t);
```

### C++

The library is in `cc/bits.hh` a single-include header file. The files in the `cc/inc/`

## Support

Currently bit-widths of 8, 16, 32, 64, and 128 are supported. The project is extensible to other word sizes that can be referenced through `uintN_t` type definitions, where `N` is the width.

### Extending

The following must contain appropriate entries for new bit-widths:
+ `inc/N.h`:
    - LOGN, BITSN, and the other macros
    - masks
    - LFSR taps
    - `TEMPLATE_*` macros
+ `inc/extint.h`:
    - `typedef`(s) for the `uintN_t` type(s), if necessary

## Testing

Many (soon to be all) provided functions are tested against a naive (or at least more obvious) implementation on a selection of chosen, as well as random, test cases. To build the test suite, use `make test`. The command `make run` will both build and execute.

## Notes

### Makefile

This project is still under development. The Makefile is configured for my system. You may need to modify it for your own.

### License

GNU GPL v3 or higher.

### Credit

Much of this code is inspired by the code, pseudocode, and research of others. A _very_ short list of those who's work I am grateful for is below. This list will be expanded as the project nears completion.

+ Henry S. Warren, Jr.
+ Sean E. Anderson
+ Jasper Neumann
+ Ruby B. Lee
+ The folks at https://chessprogramming.wikispaces.com/
