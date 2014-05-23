#ifndef TSPII_HGTMM_UTILS_H
#define TSPII_HGTMM_UTILS_H

/***********************************BEGIN**********************************
**                      CONFIDENTIAL AND PROPRIETARY
**         Copyright (C) 2003-2011 Tellabs, All Rights Reserved
**************************************************************************
**
**  File:    TSPII_HgtmmUtils.h
**  Type:    C++ include
**  Description:
**
************************************END*************************************/
#include <map>


typedef char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef long int32;
typedef unsigned long uint32;
typedef unsigned long long int uint64;

const uint16 TSPII_FIRST_PORT     = 0;
const uint16 TSPII_LAST_PORT      = 12;
const uint16 TSPII_FIRST_CFP_PORT = 0;
const uint16 TSPII_LAST_CFP_PORT  = 1;
const uint16 TSPII_FIRST_SFPP_PORT = 2;
const uint16 TSPII_LAST_SFPP_PORT  = 11;
const uint16 TSPII_FIRST_MSA_PORT  = 12;
const uint16 TSPII_LAST_MSA_PORT   = 12;
const uint16 TSPII_LAST_ODUF_INDEX  = 19;
const uint16 TSPII_LAST_ODU2_INDEX  = 19;
const uint16 TSPII_LAST_ODU3_INDEX  = 3;
const uint16 TSPII_LAST_ODU4_INDEX  = 0;
const uint16 TSPII_SEQ_DW_SIZE = ((TSPII_LAST_ODUF_INDEX + 1) + (TSPII_LAST_ODU2_INDEX + 1) +
                                  (TSPII_LAST_ODU3_INDEX + 1) + (TSPII_LAST_ODU4_INDEX + 1)); 
const uint16 TSPII_SEQ_RS_SIZE = (TSPII_LAST_SFPP_PORT + 1);
const uint16 TSPII_FW_STEP          = 3;
const uint16 TSPII_OTN_ODUk_TRIBPORT_MAX                = 80;
const uint16 TSPII_OTN_ODUk_TRIBPORT_MIN                = 1;
const uint16 TSPII_XC_HGTMM_BITMAP_EMPTY                = 0;
const uint16 TSPII_XC_HGTMM_INVALID_PORT                = 0xFFFF;
const uint16 TSPII_XC_HGTMM_INVALID_TSLOT               = 0xFFFF;
const uint16 TSPII_XC_HGTMM_INVALID_TBLINDEX            = 0xFFFF;


#define  DM_RETRY_COUNTER   3
#define  DM_DELAY_FW_ERROR     0xFFFFFFFF
#define  DM_DELAY_FW_PENDING   0xFFFFFFFE
#define  HGTMM_PM5440_INVALID_PORT  0xFFFFFFFF
#define  HGTMM_PM5440_CLIENT_PORT   9

enum DEV_OduFlexType
{
   DEV_OduflexCBR,
   DEV_OduflexGFP,
   DEV_OduflexUNKNOWN
};

/////////////////// OTN MODULE - ODU MUX LEVEL CROSSCONNECTION /////////////////////////////////////////////////////
#define TSPII_XC_ODU3_CLIENT_0                        (1)
#define TSPII_XC_ODU3_CLIENT_1                        (2)
#define TSPII_XC_ODU2_CLIENT_0                        (3)
#define TSPII_XC_ODU2_CLIENT_1                        (4)
#define TSPII_XC_ODU2_CLIENT_2                        (5)
#define TSPII_XC_ODU2_CLIENT_3                        (6)
#define TSPII_XC_ODU2_CLIENT_4                        (7)
#define TSPII_XC_ODU2_CLIENT_5                        (8)
#define TSPII_XC_ODU2_CLIENT_6                        (9)
#define TSPII_XC_ODU2_CLIENT_7                       (10)
#define TSPII_XC_ODU2_CLIENT_8                       (11)
#define TSPII_XC_ODU2_CLIENT_9                       (12)
#define TSPII_XC_ODU4_LINE_FACILITY_ID               (13)
#define TSPII_XC_ODU2_LINE_0                         (14)
#define TSPII_XC_ODU2_LINE_79                        (93)

#define TSPII_XC_ODU4_MUX_FACILITY_ID                (94)
#define TSPII_XC_ODU4_DEMUX_ODU2_FACILITY_ID         (95)
#define TSPII_XC_ODU4_DEMUX_ODUF_FACILITY_ID         (96)
#define TSPII_XC_ODU4_DEMUX_ODU3_FACILITY_ID         (97)
#define TSPII_XC_MAX_XC_CLIENT_FACILITY	             (12)
#define TSPII_XC_MAX_XC_TRIB_PORT_COUNT              (80)
#define TSPII_XC_MAX_XC_TRIB_SLOT_COUNT              (80)
#define TSPII_XC_MAX_XC_COUNT                        (24)


enum TSPII_HGTMM_OTN_XC_TYPE
{
    TSPII_HGTMM_OTN_MUX42       = 0,  /* ODU4 - ODU2    */
    TSPII_HGTMM_OTN_MUX42E      = 1,  /* ODU4 - ODU2E   */
    TSPII_HGTMM_OTN_MUX41E      = 2,  /* ODU4 - ODU1E   */
    TSPII_HGTMM_OTN_MUX41F      = 3,  /* ODU4 - ODU1F   */
    TSPII_HGTMM_OTN_MUX4F       = 4,  /* ODU4 - ODUF    */
    TSPII_HGTMM_OTN_MUX43       = 5,  /* ODU4 - ODU3    */
    TSPII_HGTMM_OTN_ODU2XC      = 6,  /* ODU2 - ODU2    */
    TSPII_HGTMM_OTN_ODU2EXC     = 7,  /* ODU2E - ODU2E    */
    TSPII_HGTMM_OTN_ODU1EXC     = 8,  /* ODU1E - ODU1E    */
    TSPII_HGTMM_OTN_ODU1FXC     = 9,  /* ODU1F - ODU1F    */
    TSPII_HGTMM_OTN_ODUFXC      = 10,  /* ODUF - ODUF    */
    TSPII_HGTMM_OTN_ODU3XC      = 11,  /* ODU3 - ODU3    */
    TSPII_HGTMM_OTN_UNKNOWN     = 12,  /* UNKOWN         */   
    TSPII_HGTMM_OTN_MUX         = 13,
    TSPII_HGTMM_OTN_XC          = 14,
};

enum TSPII_HGTMM_ODU_SIDE
{
    TSPII_HGTMM_CLIENTODU_SIDE   = 0x0,
    TSPII_HGTMM_LINEODU_SIDE,
    TSPII_HGTMM_ODU4_SIDE,
    TSPII_HGTMM_SIDE_UNKNOWN, /* this is for out of range values error handling */
};

#define HGTMM_XC_TYPE_DISPLAY(type) \
    ((type) == TSPII_HGTMM_OTN_MUX42        ? "MUX42 "   : \
     (type) == TSPII_HGTMM_OTN_MUX42E       ? "MUX42E"     : \
     (type) == TSPII_HGTMM_OTN_MUX41E       ? "MUX41E"     : \
     (type) == TSPII_HGTMM_OTN_MUX41F       ? "MUX41F"     : \
     (type) == TSPII_HGTMM_OTN_MUX4F        ? "MUX4F "     : \
     (type) == TSPII_HGTMM_OTN_MUX43        ? "MUX43 "    : \
     (type) == TSPII_HGTMM_OTN_ODU2XC       ? "ODU2XC "    : \
     (type) == TSPII_HGTMM_OTN_ODU2EXC      ? "ODU2EXC"    : \
     (type) == TSPII_HGTMM_OTN_ODU1EXC      ? "ODU1EXC"    : \
     (type) == TSPII_HGTMM_OTN_ODU1FXC      ? "ODU1FXC"    : \
     (type) == TSPII_HGTMM_OTN_ODUFXC       ? "ODUFXC "     : \
     (type) == TSPII_HGTMM_OTN_ODU3XC       ? "ODU3XC "  : \
     (type) == TSPII_HGTMM_OTN_MUX          ? "ODUMUX "  : \
     (type) == TSPII_HGTMM_OTN_XC           ? "ODUXC "  : "UNKNOWN")
    

#define TSPII_XC_NAME_SIZE   30

// Structure of the Crossconnect Table Record
class Tspii_HgtmmXcRecord
{
public:
    uint16        InPort;    
    uint16        InTslot;    
    uint16        OutPort;   
    uint16        OutTslot;
    bool          IsUsed;
    TSPII_HGTMM_OTN_XC_TYPE    TspiiXcType;
};


class TSPII_HgtmmUtils
{
    public:
    virtual                  ~TSPII_HgtmmUtils();
    static TSPII_HgtmmUtils  & GetInstance();
    static void              DeleteInstance();
    static bool              IsClientPort(uint16 thePort);
    static bool              IsLinePort(uint16 thePort);
    static unsigned int      ConvertTspPort2RegionId(uint16 thePort);
    static uint32            ConvertTspiiPort2Pm5440Port(uint16 thePort);
    static void              ConvertTspiiOduPort2Pm5440Port(uint16 thePort, uint32 &theFwPort, uint32 &theFwType);
    //static bool              FindLineOduIndex(CT_ODU_Layer theOduLayer, CT_IntfId aClientPortId, uint16& theLineOduIndex);
    //static uint16            ConvertIntfPort2TspiiPort(CT_IntfId theIntfPort);
    static char*             GetTimeStamp();
private:
                                TSPII_HgtmmUtils();
    static TSPII_HgtmmUtils      * ourInstance;
};

#endif // TSPII_HGTM_UTILIS_H
