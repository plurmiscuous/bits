#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <assert.h>

#include "bits.h"
#include "testing/test_funcs.h"
#include "testing/test_suite.h"

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

      test_rol();
      test_ror();
      test_bswap();
      test_rswap();
      test_rev();
      test_shuf();

      test_extr();
      test_depl();
      test_extl();
      test_depr();
      test_grp();

      test_omflip();
      test_bfly();

      test_gray();
      test_lfsr();

      test_trans();

      term_suite();
}
