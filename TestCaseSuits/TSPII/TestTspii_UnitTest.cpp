/*
 * TestTspii.cpp
 *
 *  Created on: May 22, 2014
 *      Author: d20li
 */

#include <limits.h>
#include "../../hgtmm/TelecomServices/TsPii_Imp/TSPII_HgtmmFecHwDrvIf.h"
#include "gtest/gtest.h"


// Tests TSPII_HgtmmFecHwDrvIf of negative numbers.
TEST(TSPII_HgtmmFecHwDrvIfTest, GetHighFECCorrectedBytesCount) {
  // This test is named "Negative", and belongs to the "FactorialTest"
  // test case.

  int highFECCorrectedBytesCount = 0;
  TSPII_HgtmmFecHwDrvIf hgtmmFecHwDrvIf(0,0);
  highFECCorrectedBytesCount= hgtmmFecHwDrvIf.GetHighFECCorrectedBytesCount();
  EXPECT_EQ(highFECCorrectedBytesCount, 0);

}
