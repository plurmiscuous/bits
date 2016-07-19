Bits
====

## About

Bits is a permutation/manipulation library created provide a myriad of operations that work on a wide range of word sizes.

## Usage

The two primary files are `bits.c` and the accompanying `bits.h`. The files in the `inc\` directory are required for compilation.

## Testing

Many (soon to be all) provided functions are tested against a naive (or at least more obvious) implementation on a selection of chosen, as well as random, test cases. To buld the test suite the library, use `make test`. The command `make run` will both build and execute.

## Notes

### Makefile

This project is still under development. The Makefile is configured for my system. You may need to modify it for your own.

### License

GNU GPL v3 or higher.

### Credit

Much of this code is inspired by the code, pseudocode, and research of others. A very short list of those I am grateful for is below.

+ Henry S. Warren, Jr.
+ Sean Eron Anderson of Stanford
+ Jasper Neumann
+ The folks at https://chessprogramming.wikispaces.com/
+ Ruby B. Lee of Princeton
...Many more to be added as the project nears completion
