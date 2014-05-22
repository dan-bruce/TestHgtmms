/* Copyright(c) Tellabs Transport Group. All rights reserved */

#ifndef CT_G709TRACE_H
#define CT_G709TRACE_H


#include <string.h>


typedef          char  int8;
typedef unsigned char  uint8;
typedef          short int16;
typedef unsigned short uint16;
typedef          long  int32;
typedef unsigned long  uint32;

const uint8 CT_MAX_G709_OPERATOR_SPECIFIC_SIZE = 28;
const uint8 CT_MAX_G709_OPERATOR_SPECIFIC_SIZE_STD = 32;
const uint8 CT_MAX_G709_API_SIZE  = 15;
const uint8 CT_MAX_G709_TTI_SIZE  = 64;
const uint32 CT_G709_SAPI_0_POS   = 0;
const uint32 CT_G709_SAPI_POS     = 1;
const uint32 CT_G709_DAPI_0_POS   = 16;
const uint32 CT_G709_DAPI_POS     = 17;
const uint32 CT_G709_OPER_POS     = 32;
const uint32 CT_G709_TRACE_ID_POS = 60;
const uint32 CT_G709_RESERVED_POS = 62;
const uint32 CT_G709_CRC7_POS     = 63;


//This object contains all the generic optical configuration 
//for one port.
class CT_G709Trace 
{

public:

};

#endif /* CT_G709TRACE_H */

