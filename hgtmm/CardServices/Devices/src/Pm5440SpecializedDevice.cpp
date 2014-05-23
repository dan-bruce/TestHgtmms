/***********************************BEGIN************************************/
/**                      CONFIDENTIAL AND PROPRIETARY                      **/
/**       (C) Copyright 2004, 2009 Tellabs, Inc. All Rights Reserved       **/
/****************************************************************************/
/**                                                                        **/
/**  File:    Pm5440SpecializedDevice.cpp                                  **/
/**  Type:    C++ source                                                   **/
/**  Description:                                                          **/
/**     Implementation of the Pm5440SpecializedDevice class (layer 3).     **/
/**                                                                        **/
/**     This class adds specialized (application specific) functions       **/
/**     to the Pm5440GenericDevice class.                                  **/
/**                                                                        **/
/************************************END*************************************/


#include "../Pm5440SpecializedDevice.h"

#ifdef __TARGET__
#include "isr.h"
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#endif

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

namespace Devices
{
  namespace Pm5440
  {

    // Shorthand names for access to hardware device
    // Initialize the static members
    Pm5440SpecializedDevice *Pm5440SpecializedDevice::myInstance = NULL;
    bool Pm5440SpecializedDevice::myDevicePresent = true;
    void * Pm5440SpecializedDevice::myVirtBaseAddress = 0;
    int Pm5440SpecializedDevice::myFd = 0;

    /*********************************BEGIN**********************************/
    /**                                                                    **/
    /**  Function:  Pm5440SpecializedDevice                                **/
    /**                                                                    **/
    /**  Description:                                                      **/
    /**      Constructor for Pm5440SpecializedDevice class.  Simply        **/
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
    Pm5440SpecializedDevice::Pm5440SpecializedDevice(uint32 baseAddress)
    {
        thisBaseAddress = baseAddress;
    }

    /***************************************************BEGIN******************
    *
    * Function:    ~Pm5440SpecializedDevice
    *
    * Description:
    *      Destructor for Pm5440SpecializedDevice class.
    *
    *
    * Inputs:     None
    *
    * Outputs:    None
    *
    * Returns:    None
    *
    *****************************************************END******************/
    Pm5440SpecializedDevice::~Pm5440SpecializedDevice()
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
    /**      deviceNum [0,1].                                              **/
    /**                                                                    **/
    /**  Outputs:                                                          **/
    /**      None.                                                         **/
    /**                                                                    **/
    /**  Returns:                                                          **/
    /**      Returns a reference to this class.                            **/
    /**                                                                    **/
    /**********************************END***********************************/
    Pm5440SpecializedDevice &Pm5440SpecializedDevice::GetInstance()
    {
        uint32  theBaseAddress;
        if(myInstance == NULL)
        {


            // VXWORKS - Direct memory access...
            theBaseAddress = BASE_ADDRESS;
            myDevicePresent = true;

            //fc_cout << hex << "theBaseAddress: 0x" << theBaseAddress << dec << endl;
            myInstance = new Pm5440SpecializedDevice(theBaseAddress);
        }
        return(*myInstance);
    }

    /*********************************BEGIN**********************************/
    /**                                                                    **/
    /**  Function:  DeleteInstance                                         **/
    /**                                                                    **/
    /**  Description:                                                      **/
    /**      Deletes the instance of this class.                           **/
    /**                                                                    **/
    /**  Inputs:                                                           **/
    /**      deviceNum [0,1].                                              **/
    /**                                                                    **/
    /**  Outputs:                                                          **/
    /**      None.                                                         **/
    /**                                                                    **/
    /**  Returns:                                                          **/
    /**      None.                                                         **/
    /**                                                                    **/
    /**********************************END***********************************/
    void Pm5440SpecializedDevice::DeleteInstance()
    {
        if (myInstance != NULL)
        {

            // Delete the driver instance
            delete myInstance;
            myInstance = NULL;

        }
    }


  }
}// DEVICES namespace
