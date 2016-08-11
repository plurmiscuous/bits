#ifndef _SERIAL_HH_
#define _SERIAL_HH_

namespace serial {

template <typename T> int pop(T bits);
template <typename T> int par(T bits);
template <typename T> int ctz(T bits);
template <typename T> int clz(T bits);
template <typename T> int mxset(T bits);
template <typename T> int mnset(T bits);
template <typename T> T max(T x, T y);
template <typename T> T min(T x, T y);
template <typename T> T gcd(T x, T y);
template <typename T> T lb(T bits);
template <typename T> bool ipow(T bits);
template <typename T> T cpow(T bits);
template <typename T> T fpow(T bits);
template <typename T> T lsb(T bits);
template <typename T> T msb(T bits);
template <typename T> T rev(T bits);
template <typename T> T shuf(T bits);
template <typename T> T ishuf(T bits);
template <typename T> T grp(T bits, T mask);
template <typename T> T igrp(T bits, T mask);
template <typename T> T omflip(T bits, T mask, uint8_t opts);
template <typename T> T bfly(T bits, T mask);
template <typename T> T ibfly(T bits, T mask);
template <typename T> T extr(T bits, T mask);
template <typename T> T depl(T bits, T mask);
template <typename T> T extl(T bits, T mask);
template <typename T> T depr(T bits, T mask);
template <typename T> T trans(T bits, int rows);
template <typename T> T rol(T bits, int rot);
template <typename T> T ror(T bits, int rot);
template <typename T> T bswap(T bits, int i, int j);
template <typename T> T rswap(T bits, int i, int j, int len);

}

///////////////////////////////
////    IMPLEMENTATIONS    ////
///////////////////////////////



#endif // _SERIAL_HH_
