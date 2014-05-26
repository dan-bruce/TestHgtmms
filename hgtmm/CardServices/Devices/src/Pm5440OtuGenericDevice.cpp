/***********************************BEGIN**********************************
**                      CONFIDENTIAL AND PROPRIETARY
**         Copyright (C) 2003-2007 Tellabs, All Rights Reserved
**************************************************************************
**
**  File:    Pm5440OtuGenericDevice.cpp
**  Type:    C++ source
**  Description:
**     Implementation of the Pm5440OtuGenericDevice class (layer 2).
**
**     This class adds generic (non-application specific) functions
**     to the MemoryMappedAccessibleDevice class.
**
************************************END*************************************/

#include "../Pm5440OtuGenericDevice.h"         // Generic device.




// Everything in the devices library will be contained in this namspace.
namespace Devices
{
  namespace Pm5440
  {

    // Initialize the number of instances of this device - start with none.


    /*********************************BEGIN**********************************/
    /**                                                                    **/
    /**  Function:  Pm5440OtuGenericDevice                                 **/
    /**                                                                    **/
    /**  Description:                                                      **/
    /**      Constructor for Pm5440OtuGenericDevice class.  Increases      **/
    /**      the number of instances of this device type by 1.             **/
    /**                                                                    **/
    /**  Inputs:                                                           **/
    /**    Formal:                                                         **/
    /**      bus      - A pointer to the card and bus specific             **/
    /**                 bus interface class.                               **/
    /**      deviceId - The device identifier for this device.             **/
    /**                                                                    **/
    /**    Class Data:                                                     **/
    /**      numInstances - The number of devices instantiated so far.     **/
    /**                     Used to assign the next available device ID    **/
    /**                     number for this instantiation.                 **/
    /**                                                                    **/
    /**  Outputs:                                                          **/
    /**    Class Data:                                                     **/
    /**      myInstanceNumber - The unique device ID for this object       **/
    /**                         instantiation.                             **/
    /**      numInstances     - The number of devices instantiated so far. **/
    /**                                                                    **/
    /**  Returns:                                                          **/
    /**      None.                                                         **/
    /**                                                                    **/
    /**********************************END***********************************/
    Pm5440OtuGenericDevice::Pm5440OtuGenericDevice()
    {
        myPortNum = 0;
    }

    /*********************************BEGIN**********************************/
    /**                                                                    **/
    /**  Function:  ~Pm5440OtuGenericDevice                                **/
    /**                                                                    **/
    /**  Description:                                                      **/
    /**      Destructor for Pm5440OtuGenericDevice class.  Decreases       **/
    /**      the number of instances of this device type by 1.             **/
    /**                                                                    **/
    /**  Inputs:                                                           **/
    /**      None.                                                         **/
    /**                                                                    **/
    /**  Outputs:                                                          **/
    /**    Class Data:                                                     **/
    /**      numInstances - The number of devices instantiated.            **/
    /**                                                                    **/
    /**  Returns:                                                          **/
    /**      None.                                                         **/
    /**                                                                    **/
    /**********************************END***********************************/
    Pm5440OtuGenericDevice::~Pm5440OtuGenericDevice()
    {

    }

    /*********************************BEGIN**********************************/
    /**                                                                    **/
    /**  Function:  getInstanceNumber                                      **/
    /**                                                                    **/
    /**  Description:                                                      **/
    /**                                                                    **/
    /**  Inputs:                                                           **/
    /**      None.                                                         **/
    /**                                                                    **/
    /**  Outputs:                                                          **/
    /**      None.                                                         **/
    /**                                                                    **/
    /**  Returns:                                                          **/
    /**      myInstanceNumber                                              **/
    /**                                                                    **/
    /**********************************END***********************************/



    /**********************************BEGIN***********************************
    *
    * Function: getFecCorr0BitCnt
    *
    * Description:
    *
    * Inputs:      none
    *
    * Outputs:     none
    *
    * Returns:     uint32
    *
    ***********************************END************************************/
    uint32 Pm5440OtuGenericDevice::getFecCorr0BitCnt()
    {
        return 0;
    }

    /**********************************BEGIN***********************************
    *
    * Function: getFecCorr1BitCnt
    *
    * Description:
    *
    * Inputs:      none
    *
    * Outputs:     none
    *
    * Returns:     uint32
    *
    ***********************************END************************************/
    uint32 Pm5440OtuGenericDevice::getFecCorr1BitCnt()
    {
        return 0;
    }

    /**********************************BEGIN***********************************
    *
    * Function: getFecUncorrBlkCnt
    *
    * Description:
    *
    * Inputs:      none
    *
    * Outputs:     none
    *
    * Returns:     uint32
    *
    ***********************************END************************************/
    uint32 Pm5440OtuGenericDevice::getFecUncorrBlkCnt()
    {
        return 0;
    }

    /**********************************BEGIN***********************************
    *
    * Function: getOtuBip8Cnt
    *
    * Description:
    *
    * Inputs:      none
    *
    * Outputs:     none
    *
    * Returns:     uint32
    *
    ***********************************END************************************/
    uint32 Pm5440OtuGenericDevice::getOtuBip8Cnt()
    {
        return 0;
    }

    /**********************************BEGIN***********************************
    *
    * Function: getOtuBeiCnt
    *
    * Description:
    *
    * Inputs:      none
    *
    * Outputs:     none
    *
    * Returns:     uint32
    *
    ***********************************END************************************/
    uint32 Pm5440OtuGenericDevice::getOtuBeiCnt()
    {
        return 0;
    }


  }
}
