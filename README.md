Bits
====

## About

Bits is a bit permutation/manipulation library.

## Usage

The two primary files are `bits.c` and the accompanying `bits.h`. The files in the `inc/` directory are required for compilation.

## Support

Currenty bit-widths of 8, 16, 32, 64, and 128 are supported. The project is extensible to other word sizes that can be referenced in a `uintN_t` format, where `N` is the width.

### Extending

The following files must contain appropriate entries for new bit-widths:
+ `inc/extint.h`: necessary `typedef`(s) for the `uintN_t` type(s)
+ `inc/N.h`: `#define` and `enum LOGS`, masks, LFSR taps, `TEMPLATE_*`

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
