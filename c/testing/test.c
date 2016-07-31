#include "test_suite.h"
#include "test_serial.h"

TEST_FN(pop, TEST_CALC)
TEST_FN(par, TEST_CALC)
TEST_FN(ctz, TEST_CALC)
TEST_FN(clz, TEST_CALC)
TEST_FN(mxset, TEST_CALC)
TEST_FN(mnset, TEST_CALC)
TEST_FN(lb, TEST_CALC)
TEST_FN(ipow, TEST_CALC)
TEST_FN(cpow, TEST_CALC)
TEST_FN(fpow, TEST_CALC)
TEST_FN(lsb, TEST_CALC)
TEST_FN(msb, TEST_CALC)

TEST_FN(max, TEST_CALC_PAIR)
TEST_FN(min, TEST_CALC_PAIR)
TEST_FN(gcd, TEST_CALC_PAIR)

TEST_FN_IFN(rev, rev, TEST_PERM_INV)
TEST_FN_IFN(shuf, ishuf, TEST_PERM_INV)
TEST_FN_IFN(bfly, ibfly, TEST_PERM_MASK_INV)

TEST_FN(extr, TEST_MANI_MASK)
TEST_FN(depl, TEST_MANI_MASK)
TEST_FN(extl, TEST_MANI_MASK)
TEST_FN(depr, TEST_MANI_MASK)

TEST_FN_IFN(gray, igray, TEST_INV)
TEST_FN_IFN(lfsr, ilfsr, TEST_INV)
TEST_FN_IFN(grp, igrp, TEST_PERM_MASK_INV)

TEST_FN(trans, TEST_TRANS_PERM)
TEST_FN(omflip, TEST_OMFLIP_PERM)
TEST_FN(rol, TEST_ROT_PERM)
TEST_FN(ror, TEST_ROT_PERM)
TEST_FN(bswap, TEST_BSWAP_PERM)
TEST_FN(rswap, TEST_RSWAP_PERM)

int main(void) {
      init_suite(true);

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
