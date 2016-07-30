Bits (C)
========

## Usage

The two primary files are `c/bits.c` and the accompanying `c/bits.h` header. The files in the `c/inc/` directory are required for compilation.

`c/bits.h` contains generic function declaration macros of the form
```C
uint##N##_t fn##N(uint##N##_t);
```
which expand into declarations for each supported bit-width:
```C
uint8_t fn8(uint8_t);
uint16_t fn16(uint16_t);
uint32_t fn32(uint32_t);
uint64_t fn64(uint64_t);
uint128_t fn128(uint128_t);
```

## N-bit Support

Currently bit-widths of 8, 16, 32, 64, and 128 are supported. The project is extensible to other word sizes that can be referenced through `uintN_t` type definitions, where `N` is the width.

### Extending

The following must contain appropriate entries for new bit-widths:
+ `inc/N.h`: necessary macros, masks, values, and templating constructs
+ `inc/extint.h`: `typedef`s for any `uintN_t` type extensions

## Testing

Included is a custom test suite and harness in which most functions are tested against a serial/naive (or at least more obvious) implementation on a selection of chosen, as well as random, test cases. Functions that remain to be tested include the LFSR and Gray Code functions since I have yet to design adequate 'expected output' functions for them.

To build the test suite, use `make test`. The command `make run` will both build and execute.
