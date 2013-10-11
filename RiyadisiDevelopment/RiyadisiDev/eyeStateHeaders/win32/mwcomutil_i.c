

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Fri Jan 18 08:10:26 2008
 */
/* Compiler settings for mwcomutil.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IMWUtil,0xC47EA90E,0x56D1,0x11d5,0xB1,0x59,0x00,0xD0,0xB7,0xBA,0x75,0x44);


MIDL_DEFINE_GUID(IID, LIBID_MWComUtil,0xA7F86ECA,0x4BED,0x414B,0x96,0xC6,0xB4,0x98,0x37,0x1D,0xF6,0x25);


MIDL_DEFINE_GUID(CLSID, CLSID_MWField,0x56015C68,0x18EE,0x4BFD,0xB6,0x13,0x28,0xB8,0xB3,0x3B,0x47,0xB6);


MIDL_DEFINE_GUID(CLSID, CLSID_MWStruct,0x2B82F5AF,0x2871,0x487B,0x9C,0xE1,0xEC,0x87,0x2C,0x46,0xD7,0x9E);


MIDL_DEFINE_GUID(CLSID, CLSID_MWComplex,0xF11B13DD,0xA245,0x470B,0xB0,0x64,0xA9,0xAA,0x98,0x81,0x1F,0xCB);


MIDL_DEFINE_GUID(CLSID, CLSID_MWSparse,0x2E3A5097,0xEB97,0x4506,0xB0,0xB3,0xF0,0x01,0x2A,0x25,0xC5,0xB8);


MIDL_DEFINE_GUID(CLSID, CLSID_MWArg,0xF08495BF,0x06E3,0x4FC0,0x8B,0x8F,0x5A,0x42,0xAC,0x59,0xCA,0xAF);


MIDL_DEFINE_GUID(CLSID, CLSID_MWArrayFormatFlags,0x73A5FAF2,0x9032,0x45E9,0xB6,0x78,0x24,0x3A,0xBE,0x61,0x4A,0x89);


MIDL_DEFINE_GUID(CLSID, CLSID_MWDataConversionFlags,0xD1F72C48,0x52BF,0x4999,0x8E,0x11,0xE1,0xE5,0x12,0x83,0xB3,0x0D);


MIDL_DEFINE_GUID(CLSID, CLSID_MWUtil,0x76ECF641,0x6517,0x4B6E,0xBF,0x3E,0x91,0x20,0xCB,0xEB,0x96,0xDF);


MIDL_DEFINE_GUID(CLSID, CLSID_MWFlags,0xE47E12D0,0x8C0B,0x41B3,0x9B,0x37,0x6C,0xA3,0xDE,0x22,0x64,0x58);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



