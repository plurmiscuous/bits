#include <iostream>
#include <iomanip>
#include <cstdint>

template <typename T>
class hexify {
  public:
    hexify(T t): t_(t) {}

    void operator()(std::ostream& os) const {
        std::ios fmt(nullptr);
        fmt.copyfmt(std::cout);
        os << "0x";
        os << std::setfill('0') << std::setiosflags(std::ios::uppercase) << std::hex;
        os << std::setw(sizeof(T) << 1) << static_cast<uint64_t>(t_);
        std::cout.copyfmt(fmt);
    }

  private:
    T t_;
};

template <>
class hexify<uint128_t> {
  public:
    hexify(uint128_t u128): u128_(u128) {}

    void operator()(std::ostream& os) const {
        std::ios fmt(nullptr);
        fmt.copyfmt(std::cout);
        os << "0x";
        os << std::setfill('0') << std::setiosflags(std::ios::uppercase) << std::hex;
        os << std::setw(16) << static_cast<uint64_t>(u128_ >> 64) << std::setw(16) << static_cast<uint64_t>(u128_);
        std::cout.copyfmt(fmt);
    }

  private:
    uint128_t u128_;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, hexify<T> n) {
    n(os);
    return os;
}
