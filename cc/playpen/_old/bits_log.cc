#include <iostream>

#include "../bits.hh"
#include "../inc/extint.hh"
#include "../inc/hexstr.hh"

#define TEMPLIFY(T) T(8) T(16) T(32) T(64) T(128)

int main(void) {
    #define HEXIFY_TEST_TEMPLATE(N)                                     \
        for (uint i = 0; i < LOG<uint##N##_t>(); ++i)                   \
            std::cout << hexstr<uint##N##_t>(WORD<uint##N##_t>(i)) << std::endl;  \
        std::cout << std::endl;
    TEMPLIFY(HEXIFY_TEST_TEMPLATE)
}
