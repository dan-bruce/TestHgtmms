#ifndef _TSPII_HGTMMFECHWDRVIF_H
#define _TSPII_HGTMMFECHWDRVIF_H
/*--------------------------------------------------------------------------
 Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  HGTMM
 AUTHOR   :  Denham Reynolds - October 2011
 DESCRIPTION:Base class for the hardware independent interface. 
 --------------------------------------------------------------------------*/

#include "../../../CommonTypes/CT_Float32.h"
#include "../../../CommonTypes/CT_G709Trace.h"

typedef char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef long int32;
typedef unsigned long uint32;

//#include "TsPii/TSPII_FecIf.h"
class Trace_TspiiRecord {

};

class TSPII_HgtmmFecHwDrvIf
{
public:

    /* Constructor */
    TSPII_HgtmmFecHwDrvIf(uint16 thePortId, uint16 theTraceRecord);
    virtual ~TSPII_HgtmmFecHwDrvIf();

    // -----------------------------------------------------------------------------------
    // FEC Monitoring Interfaces
    // -----------------------------------------------------------------------------------
    virtual uint32 GetFECCorrectedBytesCount();
    virtual uint32 GetHighFECCorrectedBytesCount();

protected:

#if 1
    uint32 itsCorrectedBytesCount;
    uint32 itsHighCorrectedBytesCount;
#endif

    uint16 itsPortId;
    uint16 itsTraceRecord;
};

#endif // _TSPII_HGTMMFECHWDRVIF_H
