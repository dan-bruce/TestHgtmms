#ifndef PM5440_SPECIALIZED_DEVICE_HH
#define PM5440_SPECIALIZED_DEVICE_HH

/***********************************BEGIN************************************/
/**                      CONFIDENTIAL AND PROPRIETARY                      **/
/**         Copyright (C) 2003-2007 Tellabs, All Rights Reserved           **/
/****************************************************************************/
/**                                                                        **/
/**  File:    Pm5440SpecializedDevice.h                                    **/
/**  Type:    C++ include                                                  **/
/**  Description:                                                          **/
/**     Declaration for the Pm5440SpecializedDevice class (layer 3)        **/
/**                                                                        **/
/**     This class adds specialized (application specific) functions       **/
/**     to the Pm5440SpecializedDevice class.                              **/
/**                                                                        **/
/************************************END*************************************/

typedef char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef long int32;
typedef unsigned long uint32;
typedef unsigned long long int uint64;
namespace Devices
{
  namespace Pm5440
  {
 /*******************************BEGIN******************************
        **
        **  Name:  Constants
        **
        **  Description:
        **         The following constants define information needed
        **         for the board specific use of Pm5450.
        **
        **  Constant Values:
        **         DRV_MEM_SPACE - Defines the size of the Regs
        **                         structure.  Used to allocate a block
        **                         of memory when the device is used in
        **                         the simulation environment.
        **         DrvMem        - An external declaration of the memory
        **                         needed to simulate the registers.
        **         BASE_ADDRESS  - The device base address used when in
        **                         simulation or compiled for the target.
        **                         Is simulation, BASE_ADDRESS is the
        **                         start of the memory array DrvMem.
        **
        ********************************END*********************************/

        //const  uint32 BASE_ADDRESS = UPCPLD_BASE_ADDR; // From chipSelects.h
        const  uint32 BASE_ADDRESS = 0xa0000000;
        const  int REGMAP_SIZE = 0x2000000;
        const  char DEVICE_NAME[] = "hgtmmcpld";

    /*********************************BEGIN**********************************/
    /**                                                                    **/
    /**  Name:  Pm5440SpecializedDevice                                    **/
    /**                                                                    **/
    /**  Description:                                                      **/
    /**         Declaration of the Pm5440SpecializedDevice class.          **/
    /**                                                                    **/
    /**         This class adds application specific extensions to the     **/
    /**         generic device class for ths device.                       **/
    /**                                                                    **/
    /**********************************END***********************************/
    class Pm5440SpecializedDevice

    {
      public:
        // Standard methods for all devices.
        static Pm5440SpecializedDevice &GetInstance();
        static void DeleteInstance();

      protected:
        // Note - Needs to be protected when the
        //        class is a singleton.
        Pm5440SpecializedDevice(uint32 baseAddress);
        // Destructor - Should be virtual if any methods are.
        virtual ~Pm5440SpecializedDevice() ;

      private:
        uint32 thisBaseAddress;
        static Pm5440SpecializedDevice *myInstance;
        static bool myDevicePresent;
        static void *myVirtBaseAddress;
        static int myFd;


    };
 }
}// namespace Devices
#endif // PM5440_SPECIALIZED_DEVICE_HH
