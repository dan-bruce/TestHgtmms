/***********************************BEGIN************************************/
/**                      CONFIDENTIAL AND PROPRIETARY                      **/
/**         Copyright (C) 2011 Tellabs, All Rights Reserved                **/
/****************************************************************************/
/**                                                                        **/
/**  File:    MsaCfpLineSpecializedDevice.cpp                              **/
/**  Type:    C++ source                                                   **/
/**  Description:                                                          **/
/**     Implementation of the MsaCfpLineSpecializedDevice class (layer 3)  **/
/**                                                                        **/
/**     This class adds specialized (application specific) functions       **/
/**     to the MsaCfpLineSpecializedDevice class.                          **/
/**                                                                        **/
/************************************END*************************************/

#include "../MsaCfpLineSpecializedDevice.h"        // Device Specialized Layer.

#include "TSPII_HgtmmUtils.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <set>


// Everything in the devices library will be contained in this namespace.
namespace Devices
{
namespace MsaCfp
{

MsaCfpLineSpecializedDevice *MsaCfpLineSpecializedDevice::myRealInstance = 0;
MsaCfpLineSpecializedDevice *MsaCfpLineSpecializedDevice::myDummyInstance = 0;

bool MsaCfpLineSpecializedDevice::firstInstantiation = true;
bool MsaCfpLineSpecializedDevice::isPresent = false;
bool MsaCfpLineSpecializedDevice::isOkToAccessCfp = false;

// list of frequencies vs. tlab channels, there are 0-43 channels in FP3.0
// and they are 100GHz spacing.  The frequencies are in Ghz

/*********************************BEGIN**********************************/
/**                                                                    **/
/**  Function:  MsaCfpLineSpecializedDevice                            **/
/**                                                                    **/
/**  Description:                                                      **/
/**      Constructor for MsaCfpLineSpecializedDevice class.  Simply    **/
/**      invokes the bass class constructor.                           **/
/**                                                                    **/
/**  Inputs:                                                           **/
/**      baseAddress - The base address of this device.                **/
/**                                                                    **/
/**  Outputs:                                                          **/
/**      None.                                                         **/
/**                                                                    **/
/**  Returns:                                                          **/
/**      None.                                                         **/
/**                                                                    **/
/**********************************END***********************************/
MsaCfpLineSpecializedDevice::MsaCfpLineSpecializedDevice()
/*
 MdioStationInterface *sta,
 uint8 busad, uint8 mmdad)
 :
 MsaCfpGenericDevice(sta, busad, mmdad),
 myTlabDevice(getAccessibleReference(),
 reinterpret_cast<void*>(&Hw::regs->VendorNvr1Regs))
 */
{

}
/*********************************BEGIN**********************************/
/**                                                                    **/
/**  Function:  ~MsaCfpLineSpecializedDevice                               **/
/**                                                                    **/
/**  Description:                                                      **/
/**      Destructor for MsaCfpLineSpecializedDevice class.                 **/
/**                                                                    **/
/**  Inputs:                                                           **/
/**      None.                                                         **/
/**                                                                    **/
/**  Outputs:                                                          **/
/**      None.                                                         **/
/**                                                                    **/
/**  Returns:                                                          **/
/**      None.                                                         **/
/**                                                                    **/
/**********************************END***********************************/
MsaCfpLineSpecializedDevice::~MsaCfpLineSpecializedDevice()
{
}

/*********************************BEGIN**********************************/
/**                                                                    **/
/**  Function:  GetInstance                                            **/
/**                                                                    **/
/**  Description:                                                      **/
/**      If needed, instantiate this class and then return a           **/
/**      reference to the class.                                       **/
/**                                                                    **/
/**  Inputs:                                                           **/
/**      None.                                                         **/
/**                                                                    **/
/**  Outputs:                                                          **/
/**      None.                                                         **/
/**                                                                    **/
/**  Returns:                                                          **/
/**      Returns a reference to this class.                            **/
/**                                                                    **/
/**********************************END***********************************/
MsaCfpLineSpecializedDevice& MsaCfpLineSpecializedDevice::GetInstance()
{
    if (firstInstantiation)
    {
        myDummyInstance = NULL;
        if (detectCfpPresence())
        {
            createRealInsantce();
            isPresent = true;
        }
        firstInstantiation = false;
    }

    return isPresent ? (*myRealInstance) : (*myDummyInstance);
}

/***************************************************************************
 *
 * Function:    DeleteInstance
 *
 * Description:
 *      delete the instance of this class
 *
 * Inputs:
 *      none
 *
 * Outputs:
 *      None
 *
 * Returns:
 *      None
 *
 ****************************************************************************/
void MsaCfpLineSpecializedDevice::DeleteInstance()
{
    delete myRealInstance;
    myRealInstance = NULL;
    delete myDummyInstance;
    myRealInstance = NULL;
}

void MsaCfpLineSpecializedDevice::createRealInsantce()
{

    myRealInstance = new MsaCfpLineSpecializedDevice();

}

/****************************************************BEGIN*****************
 *
 * Function:    detectCfpPresence
 *
 * Description:  return Presence of CFP
 *
 * Inputs:     none
 *
 * Outputs:    None
 *
 * Returns:   bool
 *
 ****************************************************END*******************/
bool MsaCfpLineSpecializedDevice::detectCfpPresence()
{
    //The CFP presence bit is identical with QSFP1 on HGTMM,just reuse the interface
    return true;
}

/*********************************BEGIN**********************************/
/**                                                                    **/
/**  Function:  InitCold                                               **/
/**                                                                    **/
/**  Description:                                                      **/
/**      This method initializes the specialized device from           **/
/**      a cold or power up condition.                                 **/
/**                                                                    **/
/**  Inputs:                                                           **/
/**      None.                                                         **/
/**                                                                    **/
/**  Outputs:                                                          **/
/**      None.                                                         **/
/**                                                                    **/
/**  Returns:                                                          **/
/**      None.                                                         **/
/**                                                                    **/
/**********************************END***********************************/
void MsaCfpLineSpecializedDevice::InitCold()
{

}

/*********************************BEGIN**********************************/
/**                                                                    **/
/**  Function:  InitWarm                                               **/
/**                                                                    **/
/**  Description:                                                      **/
/**      This method initializes the specialized device from           **/
/**      a warm reset.                                                 **/
/**                                                                    **/
/**  Inputs:                                                           **/
/**      None.                                                         **/
/**                                                                    **/
/**  Outputs:                                                          **/
/**      None.                                                         **/
/**                                                                    **/
/**  Returns:                                                          **/
/**      None.                                                         **/
/**                                                                    **/
/**********************************END***********************************/
void MsaCfpLineSpecializedDevice::InitWarm()
{

}

uint64 MsaCfpLineSpecializedDevice::getFECCorrectedBytesCount()
{
    return 0;
}

}            // namespace CFP
}            // namespace Devices
