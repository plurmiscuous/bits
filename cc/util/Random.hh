#ifndef _RANDOM_HH_
#define _RANDOM_HH_

class Random final {
  public:
    Random();

    template <typename T> T rand();
};

#endif // _RANDOM_HH_
