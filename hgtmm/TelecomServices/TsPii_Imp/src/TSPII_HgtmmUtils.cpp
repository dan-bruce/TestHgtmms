/***********************************BEGIN**********************************
**                      CONFIDENTIAL AND PROPRIETARY
**         Copyright (C) 2003-2011 Tellabs, All Rights Reserved
**************************************************************************
**
**  File:    TSPII_HgtmmUtils.cpp
**  Type:    C++ source
**  Description:
**
************************************END*************************************/

#include "../TSPII_HgtmmUtils.h"

#include <string.h>
#include <sstream>
#include <map>
#include <iomanip>
#include <cstdlib>
#include <stdio.h>

#include <algorithm>

#if defined(__TARGET__)
#include <sys/time.h>
#endif
//using  namespace Devices;
using std::map;

#define USS 1
#define NANO 2


// UNIT definition
const unsigned int TSPII_DONT_CARE   = 0;
const unsigned int TSPII_LINE_SIDE   = 1;
const unsigned int TSPII_PORT_SIDE   = 2;
const unsigned int TSPII_P2L         = 1;
const unsigned int TSPII_L2P         = 2;
const unsigned int TSPII_P2L_A_SIDE  = 1;
const unsigned int TSPII_P2L_B_SIDE  = 2;
const unsigned int TSPII_RX          = 1;
const unsigned int TSPII_TX          = 2;
const unsigned int TSPII_OSC1        = 1;
const unsigned int TSPII_OSC2        = 2;
const unsigned int TSPII_OSC3        = 3;
const unsigned int TSPII_OSC4        = 4;
const unsigned int TSPII_OSC5        = 5;
const unsigned int TSPII_OSC6        = 6;
const unsigned int TSPII_PUMP1       = 1;
const unsigned int TSPII_PUMP2       = 2;
const unsigned int TSPII_PUMP3       = 3;
const unsigned int TSPII_PUMP4       = 4;
const unsigned int TSPII_PRIMARY_A   = 1;
const unsigned int TSPII_SECONDARY_B = 2;
const unsigned int TSPII_OSA_P2L     = 1;
const unsigned int TSPII_OSA_L2P     = 2;
const unsigned int TSPII_DCCL_SECTION= 1;
const unsigned int TSPII_DCCL_LINE   = 2;
const unsigned int TSPII_BACKPLANE   = 3;
const unsigned int TSPII_OCH_P2L     = 0;
const unsigned int TSPII_OCH_L2P     = 1;
const unsigned int TSPII_OMS_P2L     = 2;
const unsigned int TSPII_OMS_L2P     = 3;

// UNIT definitions for modules with multiple
// interfaces on line side and port side.
// The number scheme is 1-based to be consistent with
// TSPII_LINE_SIDE and TSPII_PORT_SIDE above.
const unsigned int TSPII_LINE_SIDE_0  = 1;
const unsigned int TSPII_LINE_SIDE_1  = 2;
const unsigned int TSPII_LINE_SIDE_2  = 3;
const unsigned int TSPII_LINE_SIDE_3  = 4;
const unsigned int TSPII_LINE_SIDE_4  = 5;
const unsigned int TSPII_LINE_SIDE_5  = 6;
const unsigned int TSPII_LINE_SIDE_6  = 7;
const unsigned int TSPII_LINE_SIDE_7  = 8;
const unsigned int TSPII_LINE_SIDE_8  = 9;
const unsigned int TSPII_LINE_SIDE_9  = 10;
const unsigned int TSPII_LINE_SIDE_10 = 11;
const unsigned int TSPII_LINE_SIDE_11 = 12;
const unsigned int TSPII_LINE_SIDE_12 = 13;
const unsigned int TSPII_LINE_SIDE_13 = 14;
const unsigned int TSPII_LINE_SIDE_14 = 15;
const unsigned int TSPII_LINE_SIDE_15 = 16;

const unsigned int TSPII_PORT_SIDE_0  = 17;
const unsigned int TSPII_PORT_SIDE_1  = 18;
const unsigned int TSPII_PORT_SIDE_2  = 19;
const unsigned int TSPII_PORT_SIDE_3  = 20;
const unsigned int TSPII_PORT_SIDE_4  = 21;
const unsigned int TSPII_PORT_SIDE_5  = 22;
const unsigned int TSPII_PORT_SIDE_6  = 23;
const unsigned int TSPII_PORT_SIDE_7  = 24;
const unsigned int TSPII_PORT_SIDE_8  = 25;
const unsigned int TSPII_PORT_SIDE_9  = 26;
const unsigned int TSPII_PORT_SIDE_10 = 27;
const unsigned int TSPII_PORT_SIDE_11 = 28;
const unsigned int TSPII_PORT_SIDE_12 = 29;
const unsigned int TSPII_PORT_SIDE_13 = 30;
const unsigned int TSPII_PORT_SIDE_14 = 31;
const unsigned int TSPII_PORT_SIDE_15 = 32;
const unsigned int TSPII_PORT_SIDE_16 = 33;
const unsigned int TSPII_PORT_SIDE_17 = 34;
const unsigned int TSPII_PORT_SIDE_18 = 35;
const unsigned int TSPII_PORT_SIDE_19 = 36;
const unsigned int TSPII_PORT_SIDE_20 = 37;
const unsigned int TSPII_PORT_SIDE_21 = 38;
const unsigned int TSPII_PORT_SIDE_22 = 39;
const unsigned int TSPII_PORT_SIDE_23 = 40;
const unsigned int TSPII_PORT_SIDE_24 = 41;
const unsigned int TSPII_PORT_SIDE_25 = 42;
const unsigned int TSPII_PORT_SIDE_26 = 43;
const unsigned int TSPII_PORT_SIDE_27 = 44;
const unsigned int TSPII_PORT_SIDE_28 = 45;
const unsigned int TSPII_PORT_SIDE_29 = 46;
const unsigned int TSPII_PORT_SIDE_30 = 47;
const unsigned int TSPII_PORT_SIDE_31 = 48;


const unsigned int TSPII_1NSEL_SIDE_0  = 1;
const unsigned int TSPII_1NSEL_SIDE_1  = 2;
const unsigned int TSPII_1NSEL_SIDE_2  = 3;
const unsigned int TSPII_1NSEL_SIDE_3  = 4;

const unsigned int TSPII_LINES           = TSPII_LINE_SIDE_15;
const unsigned int TSPII_LINES_AND_PORTS = TSPII_PORT_SIDE_31;
const unsigned int TSPII_PORTS           = (TSPII_LINES_AND_PORTS - TSPII_LINES);



TSPII_HgtmmUtils       * TSPII_HgtmmUtils::ourInstance = 0;

static char myErrBuf[128];

////////////////////////////////////////////////////////////////////////////////
// Converts characters of a string into uppercase.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
TSPII_HgtmmUtils& TSPII_HgtmmUtils::GetInstance()
{
    if (ourInstance == NULL) ourInstance = new TSPII_HgtmmUtils;
    return *ourInstance;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void TSPII_HgtmmUtils::DeleteInstance()
{
    delete ourInstance;
    ourInstance = 0;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
TSPII_HgtmmUtils::~TSPII_HgtmmUtils()
{
    // Do nothing
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
TSPII_HgtmmUtils::TSPII_HgtmmUtils()
{
}

bool TSPII_HgtmmUtils::IsClientPort(uint16 thePort)
{
    if ((thePort <= TSPII_LAST_SFPP_PORT) && (thePort >= TSPII_FIRST_SFPP_PORT))
        // This is a client side port
        return true;
    else
        // This is a line side port
        return false;
}

bool TSPII_HgtmmUtils::IsLinePort(uint16 thePort)
{
    if (thePort == TSPII_LAST_MSA_PORT)
        // This is a line side port
        return true;
    else
        // This is a client side port
        return false;
}

/////////////////////////////////////////////////////////////////////////////////////////
unsigned int TSPII_HgtmmUtils::ConvertTspPort2RegionId(uint16 thePort)
{

    switch(thePort)
    {
    case 0:  return TSPII_PORT_SIDE_0;
    case 1:  return TSPII_PORT_SIDE_1;
    case 2:  return TSPII_PORT_SIDE_2;
    case 3:  return TSPII_PORT_SIDE_3;
    case 4:  return TSPII_PORT_SIDE_4;
    case 5:  return TSPII_PORT_SIDE_5;
    case 6:  return TSPII_PORT_SIDE_6;
    case 7:  return TSPII_PORT_SIDE_7;
    case 8:  return TSPII_PORT_SIDE_8;
    case 9:  return TSPII_PORT_SIDE_9;
    case 10: return TSPII_PORT_SIDE_10;
    case 11: return TSPII_PORT_SIDE_11;
    case 12: return TSPII_PORT_SIDE_12;
    default:
        // Oops - XcType Invalid - Should never happen
        sprintf(myErrBuf, "TSPII_HgtmmUtils::ConvertTspPort2RegionId Bad Port Id: %d", thePort);
        //FC_THROW_ERROR(FC_RuntimeError, myErrBuf);
        return 0;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
uint32 TSPII_HgtmmUtils::ConvertTspiiPort2Pm5440Port(uint16 thePort)
{

    switch(thePort)
    {
    case 2:  return 0;
    case 3:  return 1;
    case 4:  return 2;
    case 5:  return 3;
    case 6:  return 4;
    case 7:  return 5;
    case 8:  return 6;
    case 9:  return 7;
    case 10: return 8;
    case 11: return 9;
    case 12: return 12;   // Line port
    default:
        return HGTMM_PM5440_INVALID_PORT;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
void TSPII_HgtmmUtils::ConvertTspiiOduPort2Pm5440Port(uint16 thePort, uint32 &theFwPort, uint32 &theFwType)
{
    if ((thePort >= TSPII_XC_ODU3_CLIENT_0) && (thePort <= TSPII_XC_ODU2_CLIENT_9))
    {
        // This is a client ODU2/ODU3/ODUF port
        // from 1-12
        theFwPort = thePort - TSPII_FW_STEP;
        theFwType = TSPII_HGTMM_CLIENTODU_SIDE;
    }
    else if ((thePort >= TSPII_XC_ODU2_LINE_0) && (thePort <= TSPII_XC_ODU2_LINE_79))
    {
        // This is a line ODU2 port
        // from 14-93
        theFwPort = thePort - TSPII_FW_STEP;
        theFwType = TSPII_HGTMM_LINEODU_SIDE;
    }
    else if (thePort == (TSPII_XC_ODU4_LINE_FACILITY_ID))
    {
        // This is a line ODU4 port
        theFwPort = TSPII_XC_ODU4_LINE_FACILITY_ID - TSPII_FW_STEP;
        theFwType = TSPII_HGTMM_ODU4_SIDE;
    }
    else
    {
        theFwPort = HGTMM_PM5440_INVALID_PORT;
        theFwType = TSPII_HGTMM_SIDE_UNKNOWN;
    }
    return;
}


/****************************************************BEGIN*****************
*
* Function:    GetTimeStamp
*
* Description:
*     Gets string version of current time stamp
*
* Inputs:     none
*
* Outputs:    None
*
* Returns:   string
*
****************************************************END*******************/
char* TSPII_HgtmmUtils::GetTimeStamp()
{
#if defined(__TARGET__)
    static char s[21];
    struct timeval now;
    gettimeofday(&now, NULL);  
    sprintf(s, "%02d:%02d:%02d.%5d(usec)",  now.tv_sec/60/60 % 24, now.tv_sec/60 % 60, 
	    now.tv_sec % 60, now.tv_usec);
    return s;
#else
    static char s[21] = "00:00:00.000";
    return s;
#endif
}

