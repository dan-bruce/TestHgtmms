/*--------------------------------------------------------------------------
 Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  HGTMM 
 AUTHOR   :  
 Modify   :  
 DESCRIPTION:Base class for the hardware independent interface. 
 --------------------------------------------------------------------------*/
#include "../TSPII_HgtmmFecHwDrvIf.h"
#include "../TSPII_HgtmmUtils.h"

#include "MsaCfpLineSpecializedDevice.h"
#include "Pm5440SpecializedDevice.h"
using namespace Devices;

///////////////////////////////////////////////////////////////////////////////
TSPII_HgtmmFecHwDrvIf::TSPII_HgtmmFecHwDrvIf(
                uint16 thePortId, uint16 theTraceRecord)
                :
                                itsPortId(thePortId),
                                itsTraceRecord(theTraceRecord)
{

#if 1 /*temp*/
    itsCorrectedBytesCount = 0;
    itsHighCorrectedBytesCount = 0;
#endif

}

///////////////////////////////////////////////////////////////////////////////
TSPII_HgtmmFecHwDrvIf::~TSPII_HgtmmFecHwDrvIf()
{
}

uint32 TSPII_HgtmmFecHwDrvIf::GetFECCorrectedBytesCount()
{
#if 1
    uint32 aHwPort = HGTMM_PM5440_INVALID_PORT;

    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);

    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return itsCorrectedBytesCount;
    }

    if (TSPII_HgtmmUtils::GetInstance().IsClientPort(itsPortId))
    {
        // Client Side Port
        const uint64 aCount = 0;//Pm5440::Pm5440SpecializedDevice::GetInstance().Otu[aHwPort].getFecCorr0BitCnt() + Pm5440::Pm5440SpecializedDevice::GetInstance().Otu[aHwPort].getFecCorr1BitCnt();
        itsCorrectedBytesCount = static_cast<uint32>(aCount);
        itsHighCorrectedBytesCount = static_cast<uint32>(aCount >> 32);
    }
    else if (TSPII_HgtmmUtils::GetInstance().IsLinePort(itsPortId))
    {
        const uint64 aCount = MsaCfp::MsaCfpLineSpecializedDevice::GetInstance().getFECCorrectedBytesCount();

        itsCorrectedBytesCount = static_cast<uint32>(aCount);
        itsHighCorrectedBytesCount = static_cast<uint32>(aCount >> 32);
    }
    else  // default
    {
        //itsTraceRecord.AddTrace(ERROR, "FEC, GetFECCorrectedBytesCount, Error port Id, itsPortId: %d", itsPortId);
    }
#endif
    return itsCorrectedBytesCount;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HgtmmFecHwDrvIf::GetHighFECCorrectedBytesCount()
{
    // NOTE - You must call GetFECCorrectedBytesCount() first before this.
    itsHighCorrectedBytesCount = 0;
    return itsHighCorrectedBytesCount;
}

