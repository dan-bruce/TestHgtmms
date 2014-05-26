#ifndef MSA_CFP_LINE_SPECIALIZED_DEVICE_H
#define MSA_CFP_LINE_SPECIALIZED_DEVICE_H
/***********************************BEGIN************************************/
/**                      CONFIDENTIAL AND PROPRIETARY                      **/
/**         Copyright (C) 2003-2011 Tellabs, All Rights Reserved           **/
/****************************************************************************/
/**                                                                        **/
/**  File:    MsaCfpLineSpecializedDevice.h                                    **/
/**  Type:    C++ include                                                  **/
/**  Description:                                                          **/
/**     Declaration for the MsaCfpLineSpecializedDevice class (layer 3)        **/
/**                                                                        **/
/**     This class adds specialized (application specific) functions       **/
/**     to the MsaCfpGenericDevice class.                                  **/
/**                                                                        **/
/************************************END*************************************/

//#include "MsaCfpGenericDevice.h"            // Generic device.
//#include "MdioStationManager.h"             // Bus manager class.
//#include "MsaCfpTlabDevice.h"

typedef char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef long int32;
typedef unsigned long uint32;
typedef unsigned long long int uint64;

namespace Devices
{
namespace MsaCfp
{


namespace OpticalPower
{
enum Enum
{
    AGGREGATE,
    MIN,
    MAX
};
} // namespace OpticalPower

/*********************************BEGIN********************************
 *
 *  Name:  MsaCfpLineSpecializedDevice
 *
 *  Description:
 *         Declaration of the MsaCfpLineSpecializedDevice class.
 *
 *         This class adds application specific extensions to the
 *         generic device class for this device.
 *
 *********************************END***********************************/
class MsaCfpLineSpecializedDevice
                /*: public MsaCfpGenericDevice,
                public Common7100SpecializedDevice
*/
{
public:
    // Standard methods for all devices.
    static MsaCfpLineSpecializedDevice& GetInstance();
    static void DeleteInstance();

    // Device Initialization
    virtual void InitCold();
    virtual void InitWarm();

    virtual uint64 getFECCorrectedBytesCount();
    virtual bool isGreyOptical();


    bool getPresent() {
        return isPresent;
    }
    static inline bool detectCfpPresence();

    //TraceDebug myTraceDebug;

protected:
    // ctor/dtor should be protected for singleton classes
    MsaCfpLineSpecializedDevice();
    virtual ~MsaCfpLineSpecializedDevice(); // Should be virtual if any methods are

    static void createRealInsantce();


    static MsaCfpLineSpecializedDevice *myRealInstance;
    static MsaCfpLineSpecializedDevice *myDummyInstance;


    static bool isOkToAccessCfp;

    static bool isPresent;

    static bool firstInstantiation;


};


} // namespace MsaCfp
} // namespace Devices
#endif // MSA_CFP_LINE_SPECIALIZED_DEVICE_H
