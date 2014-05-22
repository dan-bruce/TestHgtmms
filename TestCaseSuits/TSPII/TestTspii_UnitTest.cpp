/*
 * TestTspii.cpp
 *
 *  Created on: May 22, 2014
 *      Author: d20li
 */

#include <limits.h>
#include "../../hgtmm/TelecomServices/TsPii_Imp/TSPII_HgtmmFecHwDrvIf.h"
#include "gtest/gtest.h"

TEST(TSPII_HgtmmFecHwDrvIfTest, GetFECCorrectedBytesCount) {
    // This test is named "GetFECCorrectedBytesCount",
    // and belongs to the "TSPII_HgtmmFecHwDrvIfTest"

    int fecCorrectedBytesCount = 0;
    TSPII_HgtmmFecHwDrvIf hgtmmFecHwDrvIf(0, 0);
    fecCorrectedBytesCount = hgtmmFecHwDrvIf.GetFECCorrectedBytesCount();
    EXPECT_EQ(fecCorrectedBytesCount, 0);

}

TEST(TSPII_HgtmmFecHwDrvIfTest, GetHighFECCorrectedBytesCount) {

    int highFECCorrectedBytesCount = 0;
    TSPII_HgtmmFecHwDrvIf hgtmmFecHwDrvIf(0, 0);
    highFECCorrectedBytesCount = hgtmmFecHwDrvIf.GetHighFECCorrectedBytesCount();
    EXPECT_EQ(highFECCorrectedBytesCount, 0);

    /*
     EXPECT_FALSE(IsPrime(6));
     EXPECT_TRUE(IsPrime(23));
     */

}

