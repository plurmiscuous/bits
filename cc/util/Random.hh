#ifndef _RANDOM_HH_
#define _RANDOM_HH_

class Random final {
  public:
    Random();
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    template <typename T> T rand();
};

#endif // _RANDOM_HH_
