#ifndef _HEXSTR_HH_
#define _HEXSTR_HH_

#include <iostream>
#include <iomanip>

#include "../inc/extint.hh"

template <typename T>
class Hexstr {
  public:
    explicit Hexstr(T t): t_(t) {}

    std::ostream& operator()(std::ostream& os) const {
        std::ios fmt(nullptr);
        fmt.copyfmt(std::cout);
        os << "0x";
        os << std::setfill('0') << std::setiosflags(std::ios::uppercase) << std::hex;
        os << std::setw(sizeof(T) << 1) << static_cast<uint64_t>(t_);
        std::cout.copyfmt(fmt);
        return os;
    }

  private:
    T t_;
};

template <>
class Hexstr<uint128_t> {
  public:
    explicit Hexstr(uint128_t u128): u128_(u128) {}

    std::ostream& operator()(std::ostream& os) const {
        std::ios fmt(nullptr);
        fmt.copyfmt(std::cout);
        os << "0x";
        os << std::setfill('0') << std::setiosflags(std::ios::uppercase) << std::hex;
        os << std::setw(16) << static_cast<uint64_t>(u128_ >> 64);
        os << std::setw(16) << static_cast<uint64_t>(u128_);
        std::cout.copyfmt(fmt);
        return os;
    }

  private:
    uint128_t u128_;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, Hexstr<T> uint_t) {
    return uint_t(os);
}

#endif // _HEXSTR_HH_
