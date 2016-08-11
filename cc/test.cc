#include <iostream>

#include "bits.hh"
#include "testing/serial.hh"
#include "testing/BitTester.hh"

int main(void) {
    #define TESTING_TEMPLATE(T)                                             \
    {                                                                       \
        BitTester<T> tester;                                                \
        tester.testInt("pop", bits::pop<T>, serial::pop<T>);                \
        tester.testInt("par", bits::par<T>, serial::par<T>);                \
        tester.testInt("ctz", bits::ctz<T>, serial::ctz<T>);                \
        tester.testInt("clz", bits::clz<T>, serial::clz<T>);                \
        tester.testInt("mxset", bits::mxset<T>, serial::mxset<T>);          \
        tester.testInt("mnset", bits::mnset<T>, serial::mnset<T>);          \
        tester.test("lb", bits::lb<T>, serial::lb<T>);                      \
        tester.test("ipow", bits::ipow<T>, serial::ipow<T>);                \
        tester.test("cpow", bits::cpow<T>, serial::cpow<T>);                \
        tester.test("fpow", bits::fpow<T>, serial::fpow<T>);                \
        tester.test("lsb", bits::lsb<T>, serial::lsb<T>);                   \
        tester.test("msb", bits::msb<T>, serial::msb<T>);                   \
                                                                            \
        tester.testPair("max", bits::max<T>, serial::max<T>);               \
        tester.testPair("min", bits::min<T>, serial::min<T>);               \
        tester.testPair("gcd", bits::gcd<T>, serial::gcd<T>);               \
                                                                            \
        tester.test("rev", bits::rev<T>, serial::rev<T>);                   \
        tester.testInv("rev", bits::rev<T>, bits::rev<T>);                  \
                                                                            \
        tester.test("shuf", bits::shuf<T>, serial::shuf<T>);                \
        tester.test("ishuf", bits::ishuf<T>, serial::ishuf<T>);             \
        tester.testInv("shuf", bits::shuf<T>, bits::ishuf<T>);              \
                                                                            \
        tester.testMask("grp", bits::grp<T>, serial::grp<T>);               \
        tester.testMask("igrp", bits::igrp<T>, serial::igrp<T>);            \
        tester.testInvMask("grp", bits::grp<T>, bits::igrp<T>);             \
                                                                            \
        tester.testMask("bfly", bits::bfly<T>, serial::bfly<T>);            \
        tester.testMask("ibfly", bits::ibfly<T>, serial::ibfly<T>);         \
        tester.testInvMask("bfly", bits::bfly<T>, bits::ibfly<T>);          \
                                                                            \
        tester.testMask("extr", bits::extr<T>, serial::extr<T>);            \
        tester.testMask("depl", bits::depl<T>, serial::depl<T>);            \
        tester.testMask("extl", bits::extl<T>, serial::extl<T>);            \
        tester.testMask("depr", bits::depr<T>, serial::depr<T>);            \
                                                                            \
        tester.testWidth("rol", bits::rol<T>, serial::rol<T>);              \
        tester.testWidth("ror", bits::ror<T>, serial::ror<T>);              \
        tester.testInvWidth("rol", bits::rol<T>, bits::ror<T>);             \
                                                                            \
        tester.testBswap("bswap", bits::bswap<T>, serial::bswap<T>);        \
        tester.testRswap("rswap", bits::rswap<T>, serial::rswap<T>);        \
        tester.testTrans("trans", bits::trans<T>, serial::trans<T>);        \
        tester.testOmflip("omflip", bits::omflip<T>, serial::omflip<T>);    \
    }
    TEMPLIFY(TESTING_TEMPLATE)
}
