#include <iostream>

#include "../bits.hh"
#include "../testing/test_cases.hh"
#include "../inc/extint.hh"
#include "../util/hexstr.hh"
#include "../util/random.hh"

int main(void) {
    TestCases tc;

    while (tc.more()) {
        uint128_t u = tc.next<uint128_t>();
        std::cout << hexstr<uint128_t>(u) << std::endl;
    }

    Random r;

    for (int i = 0; i < 16; ++i)
        std::cout << hexstr<uint128_t>(r.rand<uint128_t>()) << std::endl;
}
