/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  HGTMM 
 AUTHOR   :  
 Modify   :  
 DESCRIPTION:Base class for the hardware independent interface. 
--------------------------------------------------------------------------*/
#include "TsPii/TSPII_Common.h"
#include "TsPii_Imp/TSPII_HgtmmFecHwDrvIf.h"
#include "TsPii_Imp/TSPII_HgtmmUtils.h"
#include "Devices/TohFpgaSpecializedDevice.h"
#include "TSPII_Trace.h"
#include "CommonTypes/CT_G709Trace.h"
#include "Devices/Pm5440SpecializedDevice.h"
#include "Devices/MsaCfp100gLhSpecializedDevice.h"
#include "Devices/MsaCfp100gLhAcaciaSpecializedDevice.h"
#include "Devices/MsaSfpSpecializedDevice.h"
#include "TsPii/TSPII_RsIf.h"

using namespace Devices;

///////////////////////////////////////////////////////////////////////////////
TSPII_HgtmmFecHwDrvIf::TSPII_HgtmmFecHwDrvIf(uint16 thePortId, Trace_TspiiRecord& theTraceRecord) :
    TSPII_FecIf(false),
    itsPortId(thePortId),
    itsTraceRecord(theTraceRecord)
{
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
void TSPII_HgtmmFecHwDrvIf::UpdateValues()
{
}

// FEC and other alarm and BIP and configuration are set on Digi120, including the client port and line port.
///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HgtmmFecHwDrvIf::GetFECCorrectedBytesCount()
{
    uint32  aHwPort = HGTMM_PM5440_INVALID_PORT;

    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);

    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return itsCorrectedBytesCount;
    }

    if(TSPII_HgtmmUtils::GetInstance().IsClientPort(itsPortId))
    {
        // Client Side Port
        const uint64 aCount = Pm5440::Pm5440SpecializedDevice::GetInstance().Otu[aHwPort].getFecCorr0BitCnt() + Pm5440::Pm5440SpecializedDevice::GetInstance().Otu[aHwPort].getFecCorr1BitCnt();
        itsCorrectedBytesCount = static_cast<uint32>(aCount);
        itsHighCorrectedBytesCount = static_cast<uint32>(aCount >> 32);
    }
    else if(TSPII_HgtmmUtils::GetInstance().IsLinePort(itsPortId))
    {
        const uint64 aCount = MsaCfp::MsaCfp100gLhSpecializedDevice::GetInstance().
            ntwkLaneVr2OtnFec.getNtwkFecCorrectedBitsCntPmAccum();
        itsCorrectedBytesCount = static_cast<uint32>(aCount);
        itsHighCorrectedBytesCount = static_cast<uint32>(aCount >> 32);
    }
    else  // default
    {
       //itsTraceRecord.AddTrace(ERROR, "FEC, GetFECCorrectedBytesCount, Error port Id, itsPortId: %d", itsPortId);
    }

    return itsCorrectedBytesCount;    
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HgtmmFecHwDrvIf::GetHighFECCorrectedBytesCount() 
{
    // NOTE - You must call GetFECCorrectedBytesCount() first before this.
    return itsHighCorrectedBytesCount;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HgtmmFecHwDrvIf::GetBitErrorCountOnOnes()
{
    uint32  aHwPort = HGTMM_PM5440_INVALID_PORT;
    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);

    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return itsErrorCountOnOnes;
    }

    if(TSPII_HgtmmUtils::GetInstance().IsClientPort(itsPortId))
    {
        itsErrorCountOnOnes = Pm5440::Pm5440SpecializedDevice::GetInstance().Otu[aHwPort].getFecCorr1BitCnt();
    }
    else if(TSPII_HgtmmUtils::GetInstance().IsLinePort(itsPortId))
    {
    }
    else  // default
    {
       //itsTraceRecord.AddTrace(ERROR, "FEC, GetFECCorrectedBytesCount, Error port Id, itsPortId: %d", itsPortId);
    }

    return itsErrorCountOnOnes;    
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HgtmmFecHwDrvIf::GetBitErrorCountOnZeros()
{
    uint32  aHwPort = HGTMM_PM5440_INVALID_PORT;

    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);

    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return itsErrorCountOnZeros;
    }

    if(TSPII_HgtmmUtils::GetInstance().IsClientPort(itsPortId))
    {
        itsErrorCountOnZeros = Pm5440::Pm5440SpecializedDevice::GetInstance().Otu[aHwPort].getFecCorr0BitCnt();
    }
    else if(TSPII_HgtmmUtils::GetInstance().IsLinePort(itsPortId))
    {
    }
    else  // default
    {
       //itsTraceRecord.AddTrace(ERROR, "FEC, GetFECCorrectedBytesCount, Error port Id, itsPortId: %d", itsPortId);
    }

    return itsErrorCountOnZeros;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HgtmmFecHwDrvIf::GetNonCorrectableRSFrameCount()
{
    uint32  aHwPort = HGTMM_PM5440_INVALID_PORT;

    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);

    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return itsNonCorrectableRSFrameCount;
    }

    if(TSPII_HgtmmUtils::GetInstance().IsClientPort(itsPortId))
    {
        // Client Side Port
        const uint64 aCount = Devices::Pm5440::Pm5440SpecializedDevice::GetInstance().Otu[aHwPort].getFecUncorrBlkCnt();
        itsNonCorrectableRSFrameCount = static_cast<uint32>(aCount);
        itsHighNonCorrectableRSFrameCount = static_cast<uint32>(aCount >> 32);
    }
    else if(TSPII_HgtmmUtils::GetInstance().IsLinePort(itsPortId))
    {
        const uint64 aCount = MsaCfp::MsaCfp100gLhSpecializedDevice::GetInstance().getNtwkFecUncorrectedBlocksPmAccum();
        itsNonCorrectableRSFrameCount = static_cast<uint32>(aCount);
        itsHighNonCorrectableRSFrameCount = static_cast<uint32>(aCount >> 32);
    }
    else  // default 
    {
       //itsTraceRecord.AddTrace(ERROR, "FEC, GetNonCorrectableRSFrameCount, Error port Id, itsPortId: %d", itsPortId);
    }

    return itsNonCorrectableRSFrameCount;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HgtmmFecHwDrvIf::GetHighNonCorrectableRSFrameCount() 
{
    // NOTE - You must call GetNonCorrectableRSFrameCount() first before this.
    return itsHighNonCorrectableRSFrameCount;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HgtmmFecHwDrvIf::GetBip8Count()
{
    uint32  aHwPort = HGTMM_PM5440_INVALID_PORT;

    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);

    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return itsBip8Count;
    }

    if(TSPII_HgtmmUtils::GetInstance().IsClientPort(itsPortId))
    {
        // Client Side Port
        const uint64 aCount = Devices::Pm5440::Pm5440SpecializedDevice::GetInstance().Otu[aHwPort].getOtuBip8Cnt();
        itsBip8Count = static_cast<uint32>(aCount);
        itsHighBip8Count = static_cast<uint32>(aCount >> 32);
    }
    else if(TSPII_HgtmmUtils::GetInstance().IsLinePort(itsPortId))
    {
        const uint64 aCount = Devices::Pm5440::Pm5440SpecializedDevice::GetInstance().getSysOtuBipCnt();
        itsBip8Count = static_cast<uint32>(aCount);
        itsHighBip8Count = static_cast<uint32>(aCount >> 32);
    }
    else  // default
    {
        //itsTraceRecord.AddTrace(ERROR, "FEC, GetBip8Count, Error port Id, itsPortId: %d", itsPortId);
    }
    return itsBip8Count;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HgtmmFecHwDrvIf::GetBip8CountHigh() const
{
    // NOTE - You must call GetBip8Count() first before this.
    return itsHighBip8Count;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HgtmmFecHwDrvIf::GetBeiCount()
{
    uint32  aHwPort = HGTMM_PM5440_INVALID_PORT;

    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);

    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return itsBeiCount;
    }
    if(TSPII_HgtmmUtils::GetInstance().IsClientPort(itsPortId))
    {
        // Client Side Port
        const uint64 aCount =  Devices::Pm5440::Pm5440SpecializedDevice::GetInstance().Otu[aHwPort].getOtuBeiCnt();
        itsBeiCount = static_cast<uint32>(aCount);
        itsHighBeiCount = static_cast<uint32>(aCount >> 32);
    }
    else if(TSPII_HgtmmUtils::GetInstance().IsLinePort(itsPortId))
    {
        // Line Side Port
        const uint64 aCount = Devices::Pm5440::Pm5440SpecializedDevice::GetInstance().getSysOtuBeiCnt();
        itsBeiCount = static_cast<uint32>(aCount);
        itsHighBeiCount = static_cast<uint32>(aCount >> 32);
    }
    else  // default
    {
        //itsTraceRecord.AddTrace(ERROR, "FEC, GetBeiCount, Error port Id, itsPortId: %d", itsPortId);
    }
    return itsBeiCount;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HgtmmFecHwDrvIf::GetBeiCountHigh() const
{
    // NOTE - You must call GetBeiCount() first before this.
    return itsHighBeiCount;
}

///////////////////////////////////////////////////////////////////////////////
// For OTU layer, only support LOF, LOM, AIS, BERSD, BDI, IAE(for TCM slip) alarm, LOS will report on OPT, 
// TIM will calculate by MON
uint32 TSPII_HgtmmFecHwDrvIf::GetLOF()
{
    uint32  aHwPort = HGTMM_PM5440_INVALID_PORT;
    uint32  aAlarm  = 0;

    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);

    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return itsLOF;
    }
    if(TSPII_HgtmmUtils::GetInstance().IsClientPort(itsPortId))
    {
        // Client Side Port
        Pm5440::Pm5440SpecializedDevice::GetInstance().updateAlarm(true);
        aAlarm = Pm5440::Pm5440SpecializedDevice::GetInstance().Otu[aHwPort].getFecLOF();
    }
    else if(TSPII_HgtmmUtils::GetInstance().IsLinePort(itsPortId))
    {
        // Line Side Port
        Pm5440::Pm5440SpecializedDevice::GetInstance().updateAlarm(true);
        aAlarm = Pm5440::Pm5440SpecializedDevice::GetInstance().getSysFecLOF();
    }
    else  // default
    {
        //itsTraceRecord.AddTrace(ERROR, "FEC, GetLOF, Error port Id, itsPortId: %d", itsPortId);
    }

    if ((aAlarm != itsLOF) && (aAlarm%2==1))
        itsTraceRecord.AddTrace(ALMFEC, "aHwPort:%d, GetLOF, Report OTU-LOF!, aAlarm: %d", aHwPort, aAlarm);
    else if ((aAlarm != itsLOF) && (aAlarm%2==0))
        itsTraceRecord.AddTrace(ALMFEC, "aHwPort:%d, GetLOF, Clear OTU-LOF!, aAlarm: %d", aHwPort, aAlarm);
    
    itsLOF = aAlarm;
    return itsLOF;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HgtmmFecHwDrvIf::GetLOMF()
{
    uint32  aHwPort = HGTMM_PM5440_INVALID_PORT;
    uint32  aAlarm  = 0;

    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);

    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return itsLOMF;
    }
    if(TSPII_HgtmmUtils::GetInstance().IsClientPort(itsPortId))
    {
        // Client Side Port
        Pm5440::Pm5440SpecializedDevice::GetInstance().updateAlarm(true);
        aAlarm = Pm5440::Pm5440SpecializedDevice::GetInstance().Otu[aHwPort].getFecLOM();
    }
    else if(TSPII_HgtmmUtils::GetInstance().IsLinePort(itsPortId))
    {
        // Line Side Port
        Pm5440::Pm5440SpecializedDevice::GetInstance().updateAlarm(true);
        aAlarm = Pm5440::Pm5440SpecializedDevice::GetInstance().getSysFecLOM();
    }
    else  // default
    {
        //itsTraceRecord.AddTrace(ERROR, "FEC, GetLOMF, Error port Id, itsPortId: %d", itsPortId);
    }

    //if ((aAlarm != itsLOMF) && (aAlarm%2==1))
        //itsTraceRecord.AddTrace(ALMFEC, "aHwPort:%d, GetLOMF, Report OTU-LOMF!, aAlarm: %d", aHwPort, aAlarm);
    //else if ((aAlarm != itsLOMF) && (aAlarm%2==0))
        //itsTraceRecord.AddTrace(ALMFEC, "aHwPort:%d, GetLOMF, Clear OTU-LOMF!, aAlarm: %d", aHwPort, aAlarm);

    itsLOMF = aAlarm;
    return itsLOMF;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HgtmmFecHwDrvIf::GetFECM()
{
    uint32  aHwPort = HGTMM_PM5440_INVALID_PORT;
    uint32  aCount  = 0;

    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);
    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return aCount;
    }

    if(TSPII_HgtmmUtils::GetInstance().IsClientPort(itsPortId))
    {
        //Pm5440::Pm5440SpecializedDevice::GetInstance().updateAlarm(true);
        //aCount = Pm5440::Pm5440SpecializedDevice::GetInstance().Port[aHwPort].getFecMismatch();
    }
    else  // default
    {
		aCount = 0;
    }

    return aCount;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HgtmmFecHwDrvIf::GetAIS()
{
    uint32  aHwPort = HGTMM_PM5440_INVALID_PORT;
    uint32  aAlarm  = 0;

    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);

    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return itsAIS;
    }
    if(TSPII_HgtmmUtils::GetInstance().IsClientPort(itsPortId))
    {
        // Client Side Port
        Pm5440::Pm5440SpecializedDevice::GetInstance().updateAlarm(true);
        aAlarm = Pm5440::Pm5440SpecializedDevice::GetInstance().Otu[aHwPort].getFecAIS();
    }
    else if(TSPII_HgtmmUtils::GetInstance().IsLinePort(itsPortId))
    {
        // Line Side Port
        // OTU-AIS didn't support for OTU4
        //aAlarm = Pm5440::Pm5440SpecializedDevice::GetInstance().getSysFecAIS();
    }
    else  // default
    {
        //itsTraceRecord.AddTrace(ERROR, "FEC, GetAIS, Error port Id, itsPortId: %d", itsPortId);
    }

    if ((aAlarm != itsAIS) && (aAlarm%2==1))
        itsTraceRecord.AddTrace(ALMFEC, "aHwPort:%d, GetAIS, Report OTU-AIS!, aAlarm: %d", aHwPort, aAlarm);
    else if ((aAlarm != itsAIS) && (aAlarm%2==0))
        itsTraceRecord.AddTrace(ALMFEC, "aHwPort:%d, GetAIS, Clear OTU-AIS!, aAlarm: %d", aHwPort, aAlarm);

    itsAIS = aAlarm;
    return itsAIS;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HgtmmFecHwDrvIf::GetBerSd()
{
    uint32  aHwPort = HGTMM_PM5440_INVALID_PORT;
    uint32  aAlarm  = 0;

    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);

    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return itsBerSd;
    }
    if(TSPII_HgtmmUtils::GetInstance().IsClientPort(itsPortId))
    {
        // Client Side Port
        Pm5440::Pm5440SpecializedDevice::GetInstance().updateAlarm(true);
        aAlarm = Pm5440::Pm5440SpecializedDevice::GetInstance().Otu[aHwPort].getFecDEG();
    }
    else if(TSPII_HgtmmUtils::GetInstance().IsLinePort(itsPortId))
    {
        // Line Side Port
        Pm5440::Pm5440SpecializedDevice::GetInstance().updateAlarm(true);
        aAlarm = Pm5440::Pm5440SpecializedDevice::GetInstance().getSysFecDEG();
    }
    else  // default 
    {
        //itsTraceRecord.AddTrace(ERROR, "FEC, GetBerSd, Error port Id, itsPortId: %d", itsPortId);
    }

    if ((aAlarm != itsBerSd) && (aAlarm%2==1))
        itsTraceRecord.AddTrace(ALMFEC, "aHwPort:%d, GetBerSd, Report OTU-BerSd!, aAlarm: %d", aHwPort, aAlarm);
    else if ((aAlarm != itsBerSd) && (aAlarm%2==0))
        itsTraceRecord.AddTrace(ALMFEC, "aHwPort:%d, GetBerSd, Clear OTU-BerSd!, aAlarm: %d", aHwPort, aAlarm);

    itsBerSd = aAlarm;
    return itsBerSd;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HgtmmFecHwDrvIf::GetBDI()
{
    uint32  aHwPort = HGTMM_PM5440_INVALID_PORT;
    uint32  aAlarm  = 0;

    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);

    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return itsBDI;
    }
    if(TSPII_HgtmmUtils::GetInstance().IsClientPort(itsPortId))
    {
        // Client Side Port
        aAlarm = Pm5440::Pm5440SpecializedDevice::GetInstance().Otu[aHwPort].getFecBDI();
    }
    else if(TSPII_HgtmmUtils::GetInstance().IsLinePort(itsPortId))
    {
        // Line Side Port
        aAlarm = Pm5440::Pm5440SpecializedDevice::GetInstance().getSysFecBDI();
    }
    else  // default 
    {
        //itsTraceRecord.AddTrace(ERROR, "FEC, GetBDI, Error port Id, itsPortId: %d", itsPortId);
    }

    if ((aAlarm != itsBDI) && (aAlarm%2==1))
        itsTraceRecord.AddTrace(ALMFEC, "aHwPort:%d, GetBDI, Report OTU-BDI!, aAlarm: %d", aHwPort, aAlarm);
    else if ((aAlarm != itsBDI) && (aAlarm%2==0))
        itsTraceRecord.AddTrace(ALMFEC, "aHwPort:%d, GetBDI, Clear OTU-BDI!, aAlarm: %d", aHwPort, aAlarm);

    itsBDI = aAlarm;
    return itsBDI;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HgtmmFecHwDrvIf::GetIAE()
{
    uint32  aHwPort = HGTMM_PM5440_INVALID_PORT;
    uint32  aAlarm  = 0;

    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);

    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return itsIAE;
    }
    if(TSPII_HgtmmUtils::GetInstance().IsClientPort(itsPortId))
    {
        // Client Side Port
        aAlarm = Pm5440::Pm5440SpecializedDevice::GetInstance().Otu[aHwPort].getFecIAE();
    }
    else if(TSPII_HgtmmUtils::GetInstance().IsLinePort(itsPortId))
    {
        // Line Side Port
        aAlarm = Pm5440::Pm5440SpecializedDevice::GetInstance().getSysFecIAE();
    }
    else  // default 
    {
        //itsTraceRecord.AddTrace(ERROR, "FEC, GetIAE, Error port Id, itsPortId: %d", itsPortId);
    }

    if ((aAlarm != itsIAE) && (aAlarm%2==1))
        itsTraceRecord.AddTrace(ALMFEC, "aHwPort:%d, GetIAE, Report OTU-IAE!, aAlarm: %d", aHwPort, aAlarm);
    else if ((aAlarm != itsIAE) && (aAlarm%2==0))
        itsTraceRecord.AddTrace(ALMFEC, "aHwPort:%d, GetIAE, Clear OTU-IAE!, aAlarm: %d", aHwPort, aAlarm);

    itsIAE = aAlarm;
    return itsIAE;
}


///////////////////////////////////////////////////////////////////////////////
const CT_Float32 & TSPII_HgtmmFecHwDrvIf::GetBER()
{
    uint32  aHwPort = HGTMM_PM5440_INVALID_PORT;
    //uint32  aAlarm  = itsBER;

    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);

    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return itsBER;
    }
    if(TSPII_HgtmmUtils::GetInstance().IsClientPort(itsPortId))
    {
        // Client Side Port
    }
    else if(TSPII_HgtmmUtils::GetInstance().IsLinePort(itsPortId))
    {
        if(MsaCfp::MsaCfp100gLhSpecializedDevice::GetInstance().nvr1BaseId.getVendorName().find("Acacia") != string::npos)
        {
            // Line Side Port
            double aBer;
            aBer = static_cast<double>(MsaCfp::MsaCfp100gLhAcaciaSpecializedDevice::GetInstance().myAcaciaPrivateDevice.getNtwkCurrentBer());
            itsBER.SetFloat(aBer);
        }
    }
    else  // default 
    {
       //itsTraceRecord.AddTrace(ERROR, "FEC, GetBER, Error port Id, itsPortId: %d", itsPortId);
    }
    return itsBER;
}

///////////////////////////////////////////////////////////////////////////////
const CT_G709Trace & TSPII_HgtmmFecHwDrvIf::GetRxTrace()
{
    uint32        aHwPort = HGTMM_PM5440_INVALID_PORT;
    CT_G709Trace   aRxTti = itsRxTrace;
    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);

    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return itsRxTrace;
    }

    if(TSPII_HgtmmUtils::GetInstance().IsClientPort(itsPortId))
    {
        // Client Side Port
        aRxTti = Pm5440::Pm5440SpecializedDevice::GetInstance().Otu[aHwPort].getRxTrace();

        unsigned int        aRegionId   = TSPII_HgtmmUtils::ConvertTspPort2RegionId(itsPortId);
        TSPII_RsRegion      *aRsRegion  = TSPII_SubApplication::GetInstance()->GetRs(aRegionId);
        CT_TEL_SignalType   aSignalType = (*aRsRegion)[0].GetSignalType();
        switch(aSignalType)
        {
        case CT_TEL_SIGNAL_OCH_P:
            aRxTti.SetTraceType(CT_TEL_PROPRIETARY_TRACE);
            break;
        default: 
            aRxTti.SetTraceType(CT_TEL_STANDARD_TRACE);
            break;
        }
    }
    else if(TSPII_HgtmmUtils::GetInstance().IsLinePort(itsPortId))
    {
        // Line Side Port
        aRxTti = Devices::Pm5440::Pm5440SpecializedDevice::GetInstance().getSysOtuRxTrace();
        aRxTti.SetTraceType(CT_TEL_PROPRIETARY_TRACE);
    }
    else  // default 
    {
       //itsTraceRecord.AddTrace(ERROR, "FEC, GetRxTrace, Error port Id, itsPortId: %d", itsPortId);
    }

    itsRxTrace = aRxTti;
    return itsRxTrace;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HgtmmFecHwDrvIf::SetCorrectionEnable(bool theEnable)
{
    uint32  aHwPort = HGTMM_PM5440_INVALID_PORT;

    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);

    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return;
    }

    TSPII_TRACE(FEC, "itsPortId %d SetCorrectionEnable %s",itsPortId, theEnable == true?"ON":"OFF"); 

    itsFECEnabled = theEnable;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HgtmmFecHwDrvIf::SetTxTrace(const CT_G709Trace & theTrace)
{
    uint32   aHwPort = HGTMM_PM5440_INVALID_PORT;
    bool    aSetTxTraceChanged = true;

    TSPII_TRACE(FEC,"Set TxTrace Fec port = %d",itsPortId); 
    TSPII_STRACE(FEC,"              Sapi  = "+theTrace.GetSapiPrintable(false));
    TSPII_STRACE(FEC,"              Dapi  = "+theTrace.GetDapiPrintable(false));
    TSPII_STRACE(FEC,"          Operator  = "+theTrace.GetOperatorSpecificPrintable(false));
    TSPII_TRACE(FEC,"  CRC = 0x%x, valid  = %s",theTrace.GetCRC7(), TEXT_ON_OFF(theTrace.IsValid()));               

    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);
    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return;
    }

    if (GetTxTrace() == theTrace)
        aSetTxTraceChanged = false;
    
    if(TSPII_HgtmmUtils::GetInstance().IsClientPort(itsPortId))
    {
        // Client Side Port
        Pm5440::Pm5440SpecializedDevice::GetInstance().Otu[aHwPort].setTxTrace(theTrace);
    }
    else if(TSPII_HgtmmUtils::GetInstance().IsLinePort(itsPortId))
    {
        // Line Side Port
        Pm5440::Pm5440SpecializedDevice::GetInstance().setSysOtuTxTrace(theTrace);
    }
    else  // default
    {
       //itsTraceRecord.AddTrace(ERROR, "FEC, SetTxTrace, Error port Id, itsPortId: %d", itsPortId);
    }
    if (aSetTxTraceChanged)
        itsTraceRecord.AddTrace(FEC, "aHwPort:%d, SetTxTrace, SAPI:%s, DAPI:%s, OPER:%s", aHwPort, theTrace.GetSapi().c_str(), theTrace.GetDapi().c_str(), theTrace.GetOperatorSpecific().c_str());
    itsTxTrace = theTrace;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HgtmmFecHwDrvIf::ForceBDI(bool theEnable)
{
    uint32  aHwPort = HGTMM_PM5440_INVALID_PORT;
    bool    aForceBDIChanged = false;
    bool    aCurrentForceBDI = false;

    aCurrentForceBDI  = GetForcedBDI();

    if(aCurrentForceBDI != theEnable)
    {
        aForceBDIChanged = true;
    }

    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);
    TSPII_TRACE(FEC, "itsPortId %d ForceBDI %s",itsPortId, theEnable==true?"ON":"OFF");

    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return;
    }

    if(TSPII_HgtmmUtils::GetInstance().IsClientPort(itsPortId))
    {
        // Client Side Port
        Pm5440::Pm5440SpecializedDevice::GetInstance().Otu[aHwPort].forceBdi(theEnable);
    }
    else if(TSPII_HgtmmUtils::GetInstance().IsLinePort(itsPortId))
    {
        // Line Side Port
        Pm5440::Pm5440SpecializedDevice::GetInstance().forceSysBdi(theEnable);
    }
    else  // default 
    {
       //itsTraceRecord.AddTrace(ERROR, "FEC, ForceBDI, Error port Id, itsPortId: %d", itsPortId);
    }

    if (aForceBDIChanged)
        itsTraceRecord.AddTrace(FEC, "aHwPort:%d, ForceBDI: %s", aHwPort, theEnable==true?"ON":"OFF");
    itsForcedBDI = theEnable;
}

/////////////////////////////////////////////////////////////////////////////
// Use SetFecType for all FEC types and eliminate the
// need to use SetEnableFECCorrection and SetEnableSuperFEC.
void TSPII_HgtmmFecHwDrvIf::SetFECType(CT_TEL_FecType theFECType)
{
    uint32              aHwPort = HGTMM_PM5440_INVALID_PORT;
    bool                aFecTypeChanged = (GetFECType() != theFECType)?true:false;
    CT_TEL_FecType      aCurrentFecType = itsFECType;

    TSPII_TRACE(FEC,"itsPortId %d SetFECType %s",itsPortId, DISPLAY_FEC_TYPE(theFECType));
    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);
    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return;
    }

    if(TSPII_HgtmmUtils::GetInstance().IsClientPort(itsPortId))
    {
        // Client Side Port // Set Digi120, support GFEC and NO FEC three mode
        switch (theFECType)
        {
        case CT_TEL_FEC_TYPE_NONE:
            Pm5440::Pm5440SpecializedDevice::GetInstance().Port[aHwPort].setFecType(Pm5440::ClientFecType::NOFEC);
            break;
        case CT_TEL_FEC_TYPE_REGULAR:
            Pm5440::Pm5440SpecializedDevice::GetInstance().Port[aHwPort].setFecType(Pm5440::ClientFecType::GFEC);
            break;
        case CT_TEL_FEC_TYPE_SUPER:
            Pm5440::Pm5440SpecializedDevice::GetInstance().Port[aHwPort].setFecType(Pm5440::ClientFecType::EFEC);
            break;
        default:
            break;
        }
    }
    else if(TSPII_HgtmmUtils::GetInstance().IsLinePort(itsPortId))
    {
        // Line Side Port // Only support Soft-D FEC
    }
    else
    {
       //itsTraceRecord.AddTrace(ERROR, "aHwPort:%d, FEC, SetFECType, Error port Id, itsPortId: %d", aHwPort, itsPortId);
    }

    itsFECType = theFECType;
    if (aFecTypeChanged)
    {
        itsTraceRecord.AddTrace(FEC, "aHwPort:%d, theNewFecType %s, theOldFecType %s", aHwPort, DISPLAY_FEC_TYPE(theFECType), 
         DISPLAY_FEC_TYPE(aCurrentFecType));
    }
}

//////////////////////////////////////////////////////////////////////////////
void TSPII_HgtmmFecHwDrvIf::SetBDIAndBEIAllowed(bool theEnable)
{
    uint32  aHwPort = HGTMM_PM5440_INVALID_PORT;
   
    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);
    TSPII_TRACE(FEC, "itsPortId %d SetBDIAndBEIAllowed %s",itsPortId, theEnable==true?"ON":"OFF");

    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return;
    }
    if(TSPII_HgtmmUtils::GetInstance().IsClientPort(itsPortId))
    {
        Pm5440::Pm5440SpecializedDevice::GetInstance().Otu[aHwPort].allowBdiBeiEnabled(theEnable);
    }
    else if(TSPII_HgtmmUtils::GetInstance().IsLinePort(itsPortId))
    {
        // Line Side Port
        Pm5440::Pm5440SpecializedDevice::GetInstance().allowSysBdiBeiEnabled(theEnable);
    }
    else  // default 
    {
       //itsTraceRecord.AddTrace(ERROR, "FEC, ForceBDI, Error port Id, itsPortId: %d", itsPortId);
    }
    if (itsAllowBDIBEI != theEnable)
        itsTraceRecord.AddTrace(FEC, "aHwPort:%d, SetBDIAndBEIAllowed, theEnable %s", aHwPort, theEnable?"ON":"OFF");
    itsAllowBDIBEI = theEnable;
}

//////////////////////////////////////////////////////////////////////////////
void TSPII_HgtmmFecHwDrvIf::SetBurstyBerSdThreshold(uint intervals, uint32 threshold)
{
    uint32  aHwPort = HGTMM_PM5440_INVALID_PORT;
    bool    aBurstyBerSdThresholdChanged = false;

    if((GetBurstyBerSdIntervals() != intervals) || (GetBurstyBerSdThreshold() != threshold))
    {
        aBurstyBerSdThresholdChanged = true;
    }
    TSPII_TRACE(FEC, "itsPortId %d SetBurstyBersdThr, INTV=%d, THR=%d",itsPortId, intervals, threshold);
    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);
    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return;
    }

    if(TSPII_HgtmmUtils::GetInstance().IsClientPort(itsPortId))
    {
        // Client Side Port
        Pm5440::Pm5440SpecializedDevice::GetInstance().Otu[aHwPort].setBurstyBerSdThreshold(intervals, threshold);
    }
    else if(TSPII_HgtmmUtils::GetInstance().IsLinePort(itsPortId))
    {
        // Line Side Port
    }
    else  // default 
    {
       //itsTraceRecord.AddTrace(ERROR, "FEC, SetBurstyBerSdThreshold, Error port Id, itsPortId: %d", itsPortId);
    }

    itsBurstySdBerIntervals = intervals;
    itsBurstySdBerThreshold = threshold;
    if (aBurstyBerSdThresholdChanged)
        itsTraceRecord.AddTrace(FEC, "aHwPort:%d, SetBurstyBerSdThreshold, Interval: %d, Thereshold: %d", aHwPort, intervals, threshold);
}

//////////////////////////////////////////////////////////////////////////////
bool TSPII_HgtmmFecHwDrvIf::GetSuperFecEnable() const
{
    return itsSuperFecEnabled;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_HgtmmFecHwDrvIf::GetCorrectionEnable() const
{
    return itsFECEnabled;
}

///////////////////////////////////////////////////////////////////////////////
const CT_G709Trace & TSPII_HgtmmFecHwDrvIf::GetTxTrace() const 
{
    return itsTxTrace;
}


///////////////////////////////////////////////////////////////////////////////
bool TSPII_HgtmmFecHwDrvIf::GetForcedBDI() const
{
    return itsForcedBDI;
}

///////////////////////////////////////////////////////////////////////////////
bool TSPII_HgtmmFecHwDrvIf::GetBDIAndBEIAllowed() const
{
    return itsAllowBDIBEI;
}

///////////////////////////////////////////////////////////////////////////////
uint TSPII_HgtmmFecHwDrvIf::GetBurstyBerSdIntervals() const
{
    return itsBurstySdBerIntervals;
}

///////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HgtmmFecHwDrvIf::GetBurstyBerSdThreshold() const
{
    return itsBurstySdBerThreshold;
}

///////////////////////////////////////////////////////////////////////////////
void TSPII_HgtmmFecHwDrvIf::SetErrorGeneration(bool theEnable)
{
    uint32  aHwPort = HGTMM_PM5440_INVALID_PORT;
    bool    aErrorGenerationChanged = false;

    if(GetErrorGeneration() != theEnable)
    {
        aErrorGenerationChanged = true;
    }

    TSPII_TRACE(FEC, "itsPortId %d SetErrorGeneration %s",itsPortId, theEnable==true?"ON":"OFF");

    aHwPort = TSPII_HgtmmUtils::GetInstance().ConvertTspiiPort2Pm5440Port(itsPortId);

    if (aHwPort == HGTMM_PM5440_INVALID_PORT)
    {
        return;
    }
    
    if(TSPII_HgtmmUtils::GetInstance().IsClientPort(itsPortId))
    {
        Pm5440::Pm5440SpecializedDevice::GetInstance().Otu[aHwPort].setErrorGeneration(theEnable);
    }
    else if(TSPII_HgtmmUtils::GetInstance().IsLinePort(itsPortId))
    {
        // Line Side Port
    }
    else
    {
    }
   
    itsErrorGeneration = theEnable;
    if (aErrorGenerationChanged)
        itsTraceRecord.AddTrace(FEC, "aHwPort:%d, SetErrorGeneration, theEnable %s", aHwPort, theEnable==true?"ON":"OFF");
}
///////////////////////////////////////////////////////////////////////////////
bool TSPII_HgtmmFecHwDrvIf::GetErrorGeneration() const
{
    return itsErrorGeneration;
}

///////////////////////////////////////////////////////////////////////////////
CT_TEL_FecType TSPII_HgtmmFecHwDrvIf::GetFECType() const
{
    return itsFECType;
}

