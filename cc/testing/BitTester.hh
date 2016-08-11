#ifndef BITTESTER_H
#define BITTESTER_H

#include <iostream>
#include <cassert>
#include <map>
#include <typeinfo>

#include "TestCases.hh"
#include "../util/Hexstr.hh"
#include "../bits.hh"
#include "../inc/extint.hh"

static std::map<std::string, std::string> typenames = {
    #define TYPEID_STRING_TEMPLATE(T) { typeid(T).name(), #T },
    TEMPLIFY(TYPEID_STRING_TEMPLATE)
};

template <typename T>
class BitTester {
    public:
        BitTester() {}
        ~BitTester() {}

        template <typename Fn>
        void test(std::string name, Fn fn1, Fn fn2) {
            std::cout << "testing: " << name << "<" << typenames[typeid(T).name()] << ">()" << std::endl;
            TestCases args;
            while (args.more()) {
                T arg = args.next<T>();
                if (fn1(arg) != fn2(arg)) {
                    std::cout << "error: " << name << "<" << typenames[typeid(T).name()] << ">()" << std::endl;
                    std::cout << "  arg: " << Hexstr<T>(arg) << std::endl;
                    std::cout << "  bits: " << Hexstr<T>(fn1(arg)) << std::endl;
                    std::cout << "  serial: " << Hexstr<T>(fn2(arg)) << std::endl;
                }
                assert(fn1(arg) == fn2(arg));
            }
        }

        template <typename Fn>
        void testInt(std::string name, Fn fn1, Fn fn2) {
            std::cout << "testing: " << name << "<" << typenames[typeid(T).name()] << ">()" << std::endl;
            TestCases args;
            while (args.more()) {
                T arg = args.next<T>();
                if (fn1(arg) != fn2(arg)) {
                    std::cout << "error: " << name << "<" << typenames[typeid(T).name()] << ">()" << std::endl;
                    std::cout << "  arg: " << Hexstr<T>(arg) << std::endl;
                    std::cout << "  bits: " << fn1(arg) << std::endl;
                    std::cout << "  serial: " << fn2(arg) << std::endl;
                }
                assert(fn1(arg) == fn2(arg));
            }
        }

        template <typename Fn>
        void testPair(std::string name, Fn fn1, Fn fn2) {
            std::cout << "testing: " << name << "<" << typenames[typeid(T).name()] << ">()" << std::endl;
            TestCases args;
            while (args.more()) {
                T arg = args.next<T>();
                TestCases args2;
                while (args2.more()) {
                    T arg2 = args2.next<T>();
                    assert(fn1(arg, arg2) == fn2(arg, arg2));
                }
            }
        }

        template <typename Fn>
        void testInv(std::string name, Fn fn1, Fn fn2) {
            std::cout << "testing: " << name << "<" << typenames[typeid(T).name()] << ">()" << std::endl;
            TestCases args;
            while (args.more()) {
                T arg = args.next<T>();
                assert(fn2(fn1(arg)) == arg);
                assert(fn1(fn2(arg)) == arg);
            }
        }

        template <typename Fn>
        void testMask(std::string name, Fn fn1, Fn fn2) {
            std::cout << "testing: " << name << "<" << typenames[typeid(T).name()] << ">()" << std::endl;
            TestCases args;
            while (args.more()) {
                T arg = args.next<T>();
                TestCases masks;
                while (masks.more()) {
                    T mask = masks.next<T>();
                    assert(fn1(arg, mask) == fn2(arg, mask));
                }
            }
        }

        template <typename Fn>
        void testInvMask(std::string name, Fn fn1, Fn fn2) {
            std::cout << "testing: " << name << "<" << typenames[typeid(T).name()] << ">()" << std::endl;
            TestCases args;
            while (args.more()) {
                T arg = args.next<T>();
                TestCases masks;
                while (masks.more()) {
                    T mask = masks.next<T>();
                    assert(fn2(fn1(arg, mask), mask) == arg);
                    assert(fn1(fn2(arg, mask), mask) == arg);
                }
            }
        }

        template <typename Fn>
        void testWidth(std::string name, Fn fn1, Fn fn2) {
            std::cout << "testing: " << name << "<" << typenames[typeid(T).name()] << ">()" << std::endl;
            TestCases args;
            while (args.more()) {
                T arg = args.next<T>();
                for (int n = 0; n < bits::BITS<T>(); ++n)
                    assert(fn1(arg, n) == fn2(arg, n));
            }
        }

        template <typename Fn>
        void testInvWidth(std::string name, Fn fn1, Fn fn2) {
            std::cout << "testing: " << name << "<" << typenames[typeid(T).name()] << ">()" << std::endl;
            TestCases args;
            while (args.more()) {
                T arg = args.next<T>();
                for (int n = 0; n < bits::BITS<T>(); ++n) {
                    assert(fn2(fn1(arg, n), n) == arg);
                    assert(fn1(fn2(arg, n), n) == arg);
                }
            }
        }

        template <typename Fn>
        void testBswap(std::string name, Fn fn1, Fn fn2) {
            std::cout << "testing: " << name << "<" << typenames[typeid(T).name()] << ">()" << std::endl;
            TestCases args;
            while (args.more()) {
                T arg = args.next<T>();
                for (int i = 0; i < bits::BITS<T>(); ++i) {
                    for (int j = 0; j < i; ++j) {
                        assert(fn1(arg, i, j) == fn2(arg, i, j));
                        assert(fn1(fn1(arg, i, j), i, j) == arg);
                    }
                }
            }
        }

        template <typename Fn>
        void testRswap(std::string name, Fn fn1, Fn fn2) {
            std::cout << "testing: " << name << "<" << typenames[typeid(T).name()] << ">()" << std::endl;
            TestCases args;
            while (args.more()) {
                T arg = args.next<T>();
                for (int i = 0; i < bits::BITS<T>(); ++i) {
                    for (int j = 0; j < i; ++j) {
                        int max = (j - i) < (bits::BITS<T>() - j + 1) ? (j  - i) : (bits::BITS<T>() - j + 1);
                        for (int k = 1; k < max; ++k) {
                            assert(fn1(arg, i, j, k) == fn2(arg, i, j, k));
                            assert(fn1(fn1(arg, i, j, k), i, j, k) == arg);
                        }
                    }
                }
            }
        }

        template <typename Fn>
        void testTrans(std::string name, Fn fn1, Fn fn2) {
            std::cout << "testing: " << name << "<" << typenames[typeid(T).name()] << ">()" << std::endl;
            TestCases args;
            while (args.more()) {
                T arg = args.next<T>();
                for (int rows = 1; rows <= bits::BITS<T>(); rows <<= 1) {
                    assert(fn1(arg, rows) == fn2(arg, rows));
                    assert(fn1(fn1(arg, rows), bits::BITS<T>() / rows) == arg);
                }
            }
        }

        template <typename Fn>
        void testOmflip(std::string name, Fn fn1, Fn fn2) {
            std::cout << "testing: " << name << "<" << typenames[typeid(T).name()] << ">()" << std::endl;
            const T flip_mask = T(-1) >> (bits::BITS<T>() >> 1);
            TestCases args;
            while (args.more()) {
                T arg = args.next<T>();
                TestCases masks;
                while (masks.more()) {
                    T mask = masks.next<T>();
                    const T mirror_mask = (mask & flip_mask) | ((mask & flip_mask) << (bits::BITS<T>() >> 1));
                    for (uint8_t ctrl = 0; ctrl < 4; ++ctrl) {
                        assert(fn1(arg, mirror_mask, ctrl) == fn2(arg, mirror_mask, ctrl));
                        assert(fn1(fn1(arg, mirror_mask, ctrl), mirror_mask, ~ctrl) == arg);
                    }
                }
            }
        }
};

#endif  // BITTESTER_H
