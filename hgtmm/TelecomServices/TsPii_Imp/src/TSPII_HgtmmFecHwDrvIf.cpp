/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  HGTMM 
 AUTHOR   :  
 Modify   :  
 DESCRIPTION:Base class for the hardware independent interface. 
--------------------------------------------------------------------------*/
#include "../TSPII_HgtmmFecHwDrvIf.h"



//using namespace Devices;

///////////////////////////////////////////////////////////////////////////////
TSPII_HgtmmFecHwDrvIf::TSPII_HgtmmFecHwDrvIf(uint16 thePortId, uint16 theTraceRecord) :
    itsPortId(thePortId),
    itsTraceRecord(theTraceRecord)
{
    itsHighCorrectedBytesCount = 0;
}

///////////////////////////////////////////////////////////////////////////////
TSPII_HgtmmFecHwDrvIf::~TSPII_HgtmmFecHwDrvIf()
{
}

/********************************************************
**
**  Function: UpdateValues
**
**  Description:
**
**
**  Inputs:
**      None
**
**  Returns:
**      None
**
********************************************************/



///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HgtmmFecHwDrvIf::GetHighFECCorrectedBytesCount() 
{
    // NOTE - You must call GetFECCorrectedBytesCount() first before this.
    itsHighCorrectedBytesCount = 0;
    return itsHighCorrectedBytesCount;
}




