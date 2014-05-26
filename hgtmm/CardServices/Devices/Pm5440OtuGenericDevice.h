#ifndef PM5440_OTU_GENERIC_DEVICE_HH
#define PM5440_OTU_GENERIC_DEVICE_HH

/***********************************BEGIN************************************/
/**                      CONFIDENTIAL AND PROPRIETARY                      **/
/**         Copyright (C) 2003-2007 Tellabs, All Rights Reserved           **/
/****************************************************************************/
/**                                                                        **/
/**  File:    Pm5440OtuGenericDevice.h                                     **/
/**  Type:    C++ include                                                  **/
/**  Description:                                                          **/
/**     Declaration for the Pm5440OtuGenericDevice class (layer 2)         **/
/**                                                                        **/
/**     This class adds specialized (application specific) functions       **/
/**     to the Pm5440OtuGenericDevice class.                               **/
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

    /*********************************BEGIN**********************************/
    /**                                                                    **/
    /**  Name:  Pm5440OtuGenericDevice                                     **/
    /**                                                                    **/
    /**  Description:                                                      **/
    /**         Declaration of the Pm5440OtuGenericDevice class.           **/
    /**                                                                    **/
    /**         This class adds generic utilities and interrupt support    **/
    /**         to the primitive "MemoryMappedAccessibleDevice" class.     **/
    /**                                                                    **/
    /**         To support interrupts, this class provides the method      **/
    /**         'handleInterrupt()' which is to be called by the ISR       **/
    /**         handler which is vectored to by the processor.  This       **/
    /**         method determines the specific cause of the interrupt      **/
    /**         given multiple possibilities within this device.           **/
    /**                                                                    **/
    /**         A static wrapper method called 'staticHandleInterrupt()'   **/
    /**         is also provided which may be needed when registering      **/
    /**         the interrput handler with the operating system.           **/
    /**                                                                    **/
    /**********************************END***********************************/
    class Pm5440OtuGenericDevice
    {
      public:
        // Public data
        // Constructor - Construct device object at a base address
        //               in memory.  Notice default argument of 0
        //               to allow this method to function as a
        //               default constructor also.
        Pm5440OtuGenericDevice();

        // Destructor - Should be virtual if any methods are.
        virtual ~Pm5440OtuGenericDevice();


        uint32 getFecCorr0BitCnt();
        uint32 getFecCorr1BitCnt();
        uint32 getFecUncorrBlkCnt();
        uint32 getOtuBip8Cnt();
        uint32 getOtuBeiCnt();



      private:
        uint32 myPortNum;


    };
  } // Pm5440
} // Devices

#endif // PM5440_OTU_GENERIC_DEVICE_HH
