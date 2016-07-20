#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <assert.h>

#include "bits.h"
#include "bittest/test_funcs.h"
#include "bittest/test_suite.h"

int main(void) {
      init_suite(DISPLAY_DIFF_ON);

      test_pop();
      test_par();
      test_ctz();
      test_clz();
      test_mxset();
      test_mnset();
      test_max();
      test_min();
      test_gcd();
      test_lb();
      test_ipow();
      test_cpow();
      test_fpow();
      test_lsb();
      test_msb();

      test_rev();
      test_shuf();

      test_extr();
      test_depl();
      test_extl();
      test_depr();
      test_grp();

      test_omflip();
      test_bfly();
      // test_benes();

      test_trans();

      term_suite();
}
