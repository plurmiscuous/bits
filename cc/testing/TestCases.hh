#ifndef _TEST_CASES_HH_
#define _TEST_CASES_HH_

#include "../inc/extint.hh"

class TestCases final {
  public:
    TestCases();
    ~TestCases();

    template <typename T> T next();
    bool more();

  private:
    uint128_t* test_cases_;
    int test_size_;
    int test_case_;
};

#endif // _TEST_CASES_HH_
