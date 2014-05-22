#ifndef _TSPII_HGTMMFECHWDRVIF_H
#define _TSPII_HGTMMFECHWDRVIF_H
/*--------------------------------------------------------------------------
Copyright(c) Tellabs Transport Group. All rights reserved

 SUBSYSTEM:  TSPII
 TARGET   :  HGTMM
 AUTHOR   :  Denham Reynolds - October 2011
 DESCRIPTION:Base class for the hardware independent interface. 
--------------------------------------------------------------------------*/

#include "TsPii/TSPII_FecIf.h"
#include "TsPii_Imp/TSPII_Trace.h"

class TSPII_HgtmmFecHwDrvIf : public TSPII_FecIf
{
public:
    
    /* Constructor */            TSPII_HgtmmFecHwDrvIf(uint16 thePortId, Trace_TspiiRecord& theTraceRecord);
    virtual                      ~TSPII_HgtmmFecHwDrvIf();

    // -----------------------------------------------------------------------------------
    // FEC Monitoring Interfaces
    // -----------------------------------------------------------------------------------
    virtual void                 UpdateValues();
    virtual uint32               GetFECCorrectedBytesCount();
    virtual uint32               GetHighFECCorrectedBytesCount();
    virtual uint32               GetHighNonCorrectableRSFrameCount();
    virtual uint32               GetBitErrorCountOnOnes();
    virtual uint32               GetBitErrorCountOnZeros();
    virtual uint32               GetNonCorrectableRSFrameCount();
    virtual uint32               GetBip8Count();
    virtual uint32               GetBeiCount();
    virtual uint32               GetIAE();
    virtual uint32               GetLOF();
    virtual uint32               GetLOMF();
	virtual uint32               GetFECM();
    virtual uint32               GetAIS();
    virtual uint32               GetBDI();
    //virtual uint32               GetBerSf();
    virtual uint32               GetBerSd();
    virtual const CT_G709Trace & GetRxTrace();
    virtual const CT_Float32 &   GetBER();


    // -----------------------------------------------------------------------------------
    // FEC Config Interfaces
    // -----------------------------------------------------------------------------------
    virtual void                 SetCorrectionEnable(bool theEnable);
    virtual void                 SetTxTrace(const CT_G709Trace & theTrace);
    virtual void                 ForceBDI(bool theEnable);
    // Use SetFecType for all FEC types and eliminate the
    // need to use SetEnableFECCorrection and SetEnableSuperFEC.
    virtual void                 SetFECType(CT_TEL_FecType theFECType);
    //virtual void                 SetBerSfThreshold(CT_TEL_BERLevels theThreshold);
    //virtual void                 SetBerSdThreshold(CT_TEL_BERLevels theThreshold);
    virtual void                 SetBDIAndBEIAllowed(bool allowed);
    virtual void                 SetErrorGeneration(bool theEnable);
    virtual void                 SetBurstyBerSdThreshold(uint intervals, uint32 threshold);

    virtual uint32               GetBip8CountHigh() const;
    virtual uint32               GetBeiCountHigh() const;
    virtual bool                 GetCorrectionEnable() const;
    virtual const CT_G709Trace & GetTxTrace() const;
    virtual bool                 GetForcedBDI() const;
    virtual bool                 GetSuperFecEnable() const;
    //virtual CT_TEL_BERLevels     GetBerSfThreshold() const;
    //virtual CT_TEL_BERLevels     GetBerSdThreshold() const;
    virtual bool                 GetBDIAndBEIAllowed() const;
    virtual bool                 GetErrorGeneration() const;
    virtual uint                 GetBurstyBerSdIntervals() const;
    virtual uint32               GetBurstyBerSdThreshold() const;
    virtual CT_TEL_FecType       GetFECType() const;

protected:
    uint16                itsPortId;
    Trace_TspiiRecord &   itsTraceRecord;
};

#endif // _TSPII_HGTMMFECHWDRVIF_H
