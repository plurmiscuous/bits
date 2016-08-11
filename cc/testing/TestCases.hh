#ifndef _TEST_CASES_HH_
#define _TEST_CASES_HH_

#include <cstddef>

#include "../inc/extint.hh"

class TestCases final {
  public:
    TestCases();
    ~TestCases();

    template <typename T> T next();
    bool more();

  private:
    uint128_t* test_cases_;
    size_t test_size_;
    size_t test_case_;
};

#endif // _TEST_CASES_HH_
