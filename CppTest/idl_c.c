

/* this ALWAYS GENERATED file contains the RPC client stubs */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Fri Oct 11 17:46:14 2019
 */
/* Compiler settings for idl.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#if !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#include <string.h>

#include "idl_h.h"

#define TYPE_FORMAT_STRING_SIZE   1097                              
#define PROC_FORMAT_STRING_SIZE   4211                              
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   2            

typedef struct _idl_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } idl_MIDL_TYPE_FORMAT_STRING;

typedef struct _idl_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } idl_MIDL_PROC_FORMAT_STRING;

typedef struct _idl_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } idl_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const idl_MIDL_TYPE_FORMAT_STRING idl__MIDL_TypeFormatString;
extern const idl_MIDL_PROC_FORMAT_STRING idl__MIDL_ProcFormatString;
extern const idl_MIDL_EXPR_FORMAT_STRING idl__MIDL_ExprFormatString;

#define GENERIC_BINDING_TABLE_SIZE   0            


/* Standard interface: RpcInterface, ver. 1.0,
   GUID={0x906B0CE0,0xC70B,0x1067,{0xB3,0x17,0x00,0xDD,0x01,0x06,0x62,0xDA}} */


extern const MIDL_SERVER_INFO RpcInterface_ServerInfo;


extern const RPC_DISPATCH_TABLE RpcInterface_v1_0_DispatchTable;

static const RPC_CLIENT_INTERFACE RpcInterface___RpcClientInterface =
    {
    sizeof(RPC_CLIENT_INTERFACE),
    {{0x906B0CE0,0xC70B,0x1067,{0xB3,0x17,0x00,0xDD,0x01,0x06,0x62,0xDA}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    (RPC_DISPATCH_TABLE*)&RpcInterface_v1_0_DispatchTable,
    0,
    0,
    0,
    &RpcInterface_ServerInfo,
    0x04000000
    };
RPC_IF_HANDLE RpcInterface_v1_0_c_ifspec = (RPC_IF_HANDLE)& RpcInterface___RpcClientInterface;

extern const MIDL_STUB_DESC RpcInterface_StubDesc;

static RPC_BINDING_HANDLE RpcInterface__MIDL_AutoBindHandle;


void RemoteOpen( 
    /* [in] */ handle_t hBinding,
    /* [out] */ PPCONTEXT_HANDLE_TYPE pphContext)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[0],
                  ( unsigned char * )&hBinding);
    
}


void RemoteClose( 
    /* [out][in] */ PPCONTEXT_HANDLE_TYPE pphContext)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[34],
                  ( unsigned char * )&pphContext);
    
}


void GetVersionNumber( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pV1,
    /* [out] */ long *pV2,
    /* [out] */ long *pV3,
    /* [out] */ long *pV4)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[70],
                  ( unsigned char * )&phContext);
    
}


void WaitForEventCallback( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [optional][in] */ __int64 context)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[130],
                  ( unsigned char * )&phContext);
    
}


void InitializeDAX( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ BSTR userName,
    /* [out] */ VARIANT_BOOL *__MIDL__RpcInterface0000)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[172],
                  ( unsigned char * )&phContext);
    
}


void GetDolbyEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ VARIANT_BOOL *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[220],
                  ( unsigned char * )&phContext);
    
}


void SetDolbyEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ VARIANT_BOOL value)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[262],
                  ( unsigned char * )&phContext);
    
}


void GetActiveProfile( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[304],
                  ( unsigned char * )&phContext);
    
}


void SetActiveProfile( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[346],
                  ( unsigned char * )&phContext);
    
}


void GetSurroundVirtualizerEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[388],
                  ( unsigned char * )&phContext);
    
}


void SetSurroundVirtualizerEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[430],
                  ( unsigned char * )&phContext);
    
}


void GetDialogEnhancerEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[472],
                  ( unsigned char * )&phContext);
    
}


void SetDialogEnhancerEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[514],
                  ( unsigned char * )&phContext);
    
}


void GetVolumeLevelerEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[556],
                  ( unsigned char * )&phContext);
    
}


void SetVolumeLevelerEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[598],
                  ( unsigned char * )&phContext);
    
}


void GetBassEnhancerEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[640],
                  ( unsigned char * )&phContext);
    
}


void SetBassEnhancerEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[682],
                  ( unsigned char * )&phContext);
    
}


void GetGEQLevels( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ SAFEARRAY * *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[724],
                  ( unsigned char * )&phContext);
    
}


void SetGEQLevels( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ SAFEARRAY * pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[766],
                  ( unsigned char * )&phContext);
    
}


void ResetGEQ( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[808],
                  ( unsigned char * )&phContext);
    
}


void GetDeviceMode( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[844],
                  ( unsigned char * )&phContext);
    
}


void GetDeviceModeCount( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[886],
                  ( unsigned char * )&phContext);
    
}


void GetDeviceModeName( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long index,
    /* [out] */ BSTR *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[928],
                  ( unsigned char * )&phContext);
    
}


void GetDeviceModeIcon( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long index,
    /* [out] */ BSTR *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[976],
                  ( unsigned char * )&phContext);
    
}


void GetOperatorInfo( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ BSTR *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[1024],
                  ( unsigned char * )&phContext);
    
}


void GetSystemCapabilities( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ short *MediaIntelligenceEnabled,
    /* [out] */ short *VolumeLevelerEnabled,
    /* [out] */ short *DialogEnchancerEnabled,
    /* [out] */ short *VirtualBassEnabled,
    /* [out] */ short *BassEnchancerEnabled,
    /* [out] */ short *SpeakerVirtualizerEnabled,
    /* [out] */ short *HeadphoneVirtualizerEnabled,
    /* [out] */ short *GEQEnabled,
    /* [out] */ short *IEQEnabled,
    /* [out] */ short *AudioOptimizerEnabled,
    /* [out] */ short *AudioRegulatorEnabled,
    /* [out] */ short *SurroundDecoderEnabled,
    /* [out] */ short *VolumeMaximizerEnabled)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[1066],
                  ( unsigned char * )&phContext);
    
}


void GetGEQMaximumRange( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[1180],
                  ( unsigned char * )&phContext);
    
}


void GetAPIStatus( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[1222],
                  ( unsigned char * )&phContext);
    
}


void GetEndpointCount( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[1264],
                  ( unsigned char * )&phContext);
    
}


void GetEndpointData( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long nIndex,
    /* [out] */ BSTR *friendlyName,
    /* [out] */ unsigned long *formFactor,
    /* [out] */ VARIANT_BOOL *offloaded,
    /* [out] */ VARIANT_BOOL *defaultDevice)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[1306],
                  ( unsigned char * )&phContext);
    
}


void GetPeripheralCount( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[1372],
                  ( unsigned char * )&phContext);
    
}


void GetPeripheralData( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long index,
    /* [out] */ BSTR *brand,
    /* [out] */ BSTR *model,
    /* [out] */ SAFEARRAY * *deviceBitmap)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[1414],
                  ( unsigned char * )&phContext);
    
}


void SelectPeripheral( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long endpointIndex,
    /* [in] */ long periferalIndex)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[1474],
                  ( unsigned char * )&phContext);
    
}


void GetSelectedPeripheral( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long endpointIndex,
    /* [out] */ long *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[1522],
                  ( unsigned char * )&phContext);
    
}


void IsSpatialAudioSupported( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ VARIANT_BOOL *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[1570],
                  ( unsigned char * )&phContext);
    
}


void GetSpatialAudioStatus( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[1612],
                  ( unsigned char * )&phContext);
    
}


void GetDefaultUITheme( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ BSTR *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2050],
                  ( unsigned char * )&phContext);
    
}


void GetSKU( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ BSTR *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2092],
                  ( unsigned char * )&phContext);
    
}


void GetActiveSubProfile( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2134],
                  ( unsigned char * )&phContext);
    
}


void SetActiveSubProfile( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2176],
                  ( unsigned char * )&phContext);
    
}


void GetSubProfileDirty( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ VARIANT_BOOL *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2218],
                  ( unsigned char * )&phContext);
    
}


void ResetSubProfile( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2260],
                  ( unsigned char * )&phContext);
    
}


void GetIEQ( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2296],
                  ( unsigned char * )&phContext);
    
}


void SetIEQ( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2338],
                  ( unsigned char * )&phContext);
    
}


void ResetIEQ( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2380],
                  ( unsigned char * )&phContext);
    
}


void GetSurroundVirtualizerValue( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ float *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2416],
                  ( unsigned char * )&phContext);
    
}


void SetSurroundVirtualizerValue( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ float pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2458],
                  ( unsigned char * )&phContext);
    
}


void GetDialogEnhancerValue( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ float *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2500],
                  ( unsigned char * )&phContext);
    
}


void SetDialogEnhancerValue( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ float pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2542],
                  ( unsigned char * )&phContext);
    
}


void GetVolumeLevelerValue( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ float *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2584],
                  ( unsigned char * )&phContext);
    
}


void SetVolumeLevelerValue( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ float pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2626],
                  ( unsigned char * )&phContext);
    
}


void GetRadarEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ VARIANT_BOOL *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2668],
                  ( unsigned char * )&phContext);
    
}


void SetRadarEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ VARIANT_BOOL pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2710],
                  ( unsigned char * )&phContext);
    
}


void GetVisualizerEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ VARIANT_BOOL *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2752],
                  ( unsigned char * )&phContext);
    
}


void SetVisualizerEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ VARIANT_BOOL pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2794],
                  ( unsigned char * )&phContext);
    
}


void GetHotkey( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long index,
    /* [out] */ BSTR *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2836],
                  ( unsigned char * )&phContext);
    
}


void SetHotkey( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long index,
    /* [in] */ BSTR hotkey,
    /* [out] */ long *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2884],
                  ( unsigned char * )&phContext);
    
}


void GetRadarSize( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ float *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2938],
                  ( unsigned char * )&phContext);
    
}


void SetRadarSize( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ float pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[2980],
                  ( unsigned char * )&phContext);
    
}


void GetRadarTransparency( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ float *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[3022],
                  ( unsigned char * )&phContext);
    
}


void SetRadarTransparency( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ float pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[3064],
                  ( unsigned char * )&phContext);
    
}


void GetRadarSkin( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ unsigned long *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[3106],
                  ( unsigned char * )&phContext);
    
}


void SetRadarSkin( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ unsigned long pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[3148],
                  ( unsigned char * )&phContext);
    
}


void GetRadarMaxDirection( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ unsigned long *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[3190],
                  ( unsigned char * )&phContext);
    
}


void SetRadarMaxDirection( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ unsigned long pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[3232],
                  ( unsigned char * )&phContext);
    
}


void GetRadarPosition( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ float *x,
    /* [out] */ float *y)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[3274],
                  ( unsigned char * )&phContext);
    
}


void SetRadarPosition( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ float x,
    /* [in] */ float y)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[3322],
                  ( unsigned char * )&phContext);
    
}


void SetRadarRefreshRate( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ unsigned long pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[3370],
                  ( unsigned char * )&phContext);
    
}


void GetRadarRefreshRate( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ unsigned long *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[3412],
                  ( unsigned char * )&phContext);
    
}


void GetSoundMap( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ SAFEARRAY * *sectEdges,
    /* [out] */ SAFEARRAY * *strengths)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[3454],
                  ( unsigned char * )&phContext);
    
}


void SetVisualizerRefreshRate( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ unsigned long pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[3502],
                  ( unsigned char * )&phContext);
    
}


void GetVisualizerRefreshRate( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ unsigned long *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[3544],
                  ( unsigned char * )&phContext);
    
}


void GetVisualizerData( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ SAFEARRAY * *pRetVal)
{

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RpcInterface_StubDesc,
                  (PFORMAT_STRING) &idl__MIDL_ProcFormatString.Format[3586],
                  ( unsigned char * )&phContext);
    
}

extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const idl_MIDL_PROC_FORMAT_STRING idl__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure RemoteOpen */

			0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x0 ),	/* 0 */
/*  8 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 10 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 12 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 14 */	NdrFcShort( 0x0 ),	/* 0 */
/* 16 */	NdrFcShort( 0x38 ),	/* 56 */
/* 18 */	0x40,		/* Oi2 Flags:  has ext, */
			0x1,		/* 1 */
/* 20 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */
/* 26 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hBinding */

/* 28 */	NdrFcShort( 0x110 ),	/* Flags:  out, simple ref, */
/* 30 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 32 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Procedure RemoteClose */


	/* Parameter pphContext */

/* 34 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 36 */	NdrFcLong( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0x1 ),	/* 1 */
/* 42 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 44 */	0x30,		/* FC_BIND_CONTEXT */
			0xe0,		/* Ctxt flags:  via ptr, in, out, */
/* 46 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 48 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 50 */	NdrFcShort( 0x38 ),	/* 56 */
/* 52 */	NdrFcShort( 0x38 ),	/* 56 */
/* 54 */	0x40,		/* Oi2 Flags:  has ext, */
			0x1,		/* 1 */
/* 56 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */
/* 60 */	NdrFcShort( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pphContext */

/* 64 */	NdrFcShort( 0x118 ),	/* Flags:  in, out, simple ref, */
/* 66 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 68 */	NdrFcShort( 0xe ),	/* Type Offset=14 */

	/* Procedure GetVersionNumber */

/* 70 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 72 */	NdrFcLong( 0x0 ),	/* 0 */
/* 76 */	NdrFcShort( 0x2 ),	/* 2 */
/* 78 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 80 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 82 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 84 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 86 */	NdrFcShort( 0x24 ),	/* 36 */
/* 88 */	NdrFcShort( 0x70 ),	/* 112 */
/* 90 */	0x40,		/* Oi2 Flags:  has ext, */
			0x5,		/* 5 */
/* 92 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 94 */	NdrFcShort( 0x0 ),	/* 0 */
/* 96 */	NdrFcShort( 0x0 ),	/* 0 */
/* 98 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 100 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 102 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 104 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pV1 */

/* 106 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 108 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 110 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pV2 */

/* 112 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 114 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 116 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pV3 */

/* 118 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 120 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 122 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pV4 */

/* 124 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 126 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 128 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure WaitForEventCallback */

/* 130 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 132 */	NdrFcLong( 0x0 ),	/* 0 */
/* 136 */	NdrFcShort( 0x3 ),	/* 3 */
/* 138 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 140 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 142 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 144 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 146 */	NdrFcShort( 0x34 ),	/* 52 */
/* 148 */	NdrFcShort( 0x0 ),	/* 0 */
/* 150 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 152 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 154 */	NdrFcShort( 0x0 ),	/* 0 */
/* 156 */	NdrFcShort( 0x0 ),	/* 0 */
/* 158 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 160 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 162 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 164 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter context */

/* 166 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 168 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 170 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure InitializeDAX */

/* 172 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 174 */	NdrFcLong( 0x0 ),	/* 0 */
/* 178 */	NdrFcShort( 0x4 ),	/* 4 */
/* 180 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 182 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 184 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 186 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 188 */	NdrFcShort( 0x24 ),	/* 36 */
/* 190 */	NdrFcShort( 0x1a ),	/* 26 */
/* 192 */	0x42,		/* Oi2 Flags:  clt must size, has ext, */
			0x3,		/* 3 */
/* 194 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 196 */	NdrFcShort( 0x0 ),	/* 0 */
/* 198 */	NdrFcShort( 0x1 ),	/* 1 */
/* 200 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 202 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 204 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 206 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter userName */

/* 208 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 210 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 212 */	NdrFcShort( 0x34 ),	/* Type Offset=52 */

	/* Parameter __MIDL__RpcInterface0000 */

/* 214 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 216 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 218 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Procedure GetDolbyEnable */

/* 220 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 222 */	NdrFcLong( 0x0 ),	/* 0 */
/* 226 */	NdrFcShort( 0x5 ),	/* 5 */
/* 228 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 230 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 232 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 234 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 236 */	NdrFcShort( 0x24 ),	/* 36 */
/* 238 */	NdrFcShort( 0x1a ),	/* 26 */
/* 240 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 242 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 244 */	NdrFcShort( 0x0 ),	/* 0 */
/* 246 */	NdrFcShort( 0x0 ),	/* 0 */
/* 248 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 250 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 252 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 254 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 256 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 258 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 260 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Procedure SetDolbyEnable */

/* 262 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 264 */	NdrFcLong( 0x0 ),	/* 0 */
/* 268 */	NdrFcShort( 0x6 ),	/* 6 */
/* 270 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 272 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 274 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 276 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 278 */	NdrFcShort( 0x2a ),	/* 42 */
/* 280 */	NdrFcShort( 0x0 ),	/* 0 */
/* 282 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 284 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 286 */	NdrFcShort( 0x0 ),	/* 0 */
/* 288 */	NdrFcShort( 0x0 ),	/* 0 */
/* 290 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 292 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 294 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 296 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter value */

/* 298 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 300 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 302 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Procedure GetActiveProfile */

/* 304 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 306 */	NdrFcLong( 0x0 ),	/* 0 */
/* 310 */	NdrFcShort( 0x7 ),	/* 7 */
/* 312 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 314 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 316 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 318 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 320 */	NdrFcShort( 0x24 ),	/* 36 */
/* 322 */	NdrFcShort( 0x1c ),	/* 28 */
/* 324 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 326 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 328 */	NdrFcShort( 0x0 ),	/* 0 */
/* 330 */	NdrFcShort( 0x0 ),	/* 0 */
/* 332 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 334 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 336 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 338 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 340 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 342 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 344 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetActiveProfile */

/* 346 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 348 */	NdrFcLong( 0x0 ),	/* 0 */
/* 352 */	NdrFcShort( 0x8 ),	/* 8 */
/* 354 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 356 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 358 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 360 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 362 */	NdrFcShort( 0x2c ),	/* 44 */
/* 364 */	NdrFcShort( 0x0 ),	/* 0 */
/* 366 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 368 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 370 */	NdrFcShort( 0x0 ),	/* 0 */
/* 372 */	NdrFcShort( 0x0 ),	/* 0 */
/* 374 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 376 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 378 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 380 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 382 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 384 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 386 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetSurroundVirtualizerEnable */

/* 388 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 390 */	NdrFcLong( 0x0 ),	/* 0 */
/* 394 */	NdrFcShort( 0x9 ),	/* 9 */
/* 396 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 398 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 400 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 402 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 404 */	NdrFcShort( 0x24 ),	/* 36 */
/* 406 */	NdrFcShort( 0x1c ),	/* 28 */
/* 408 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 410 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 412 */	NdrFcShort( 0x0 ),	/* 0 */
/* 414 */	NdrFcShort( 0x0 ),	/* 0 */
/* 416 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 418 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 420 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 422 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 424 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 426 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 428 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetSurroundVirtualizerEnable */

/* 430 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 432 */	NdrFcLong( 0x0 ),	/* 0 */
/* 436 */	NdrFcShort( 0xa ),	/* 10 */
/* 438 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 440 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 442 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 444 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 446 */	NdrFcShort( 0x2c ),	/* 44 */
/* 448 */	NdrFcShort( 0x0 ),	/* 0 */
/* 450 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 452 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 454 */	NdrFcShort( 0x0 ),	/* 0 */
/* 456 */	NdrFcShort( 0x0 ),	/* 0 */
/* 458 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 460 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 462 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 464 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 466 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 468 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 470 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetDialogEnhancerEnable */

/* 472 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 474 */	NdrFcLong( 0x0 ),	/* 0 */
/* 478 */	NdrFcShort( 0xb ),	/* 11 */
/* 480 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 482 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 484 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 486 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 488 */	NdrFcShort( 0x24 ),	/* 36 */
/* 490 */	NdrFcShort( 0x1c ),	/* 28 */
/* 492 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 494 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 496 */	NdrFcShort( 0x0 ),	/* 0 */
/* 498 */	NdrFcShort( 0x0 ),	/* 0 */
/* 500 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 502 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 504 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 506 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 508 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 510 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 512 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetDialogEnhancerEnable */

/* 514 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 516 */	NdrFcLong( 0x0 ),	/* 0 */
/* 520 */	NdrFcShort( 0xc ),	/* 12 */
/* 522 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 524 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 526 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 528 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 530 */	NdrFcShort( 0x2c ),	/* 44 */
/* 532 */	NdrFcShort( 0x0 ),	/* 0 */
/* 534 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 536 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 538 */	NdrFcShort( 0x0 ),	/* 0 */
/* 540 */	NdrFcShort( 0x0 ),	/* 0 */
/* 542 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 544 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 546 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 548 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 550 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 552 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 554 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetVolumeLevelerEnable */

/* 556 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 558 */	NdrFcLong( 0x0 ),	/* 0 */
/* 562 */	NdrFcShort( 0xd ),	/* 13 */
/* 564 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 566 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 568 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 570 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 572 */	NdrFcShort( 0x24 ),	/* 36 */
/* 574 */	NdrFcShort( 0x1c ),	/* 28 */
/* 576 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 578 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 580 */	NdrFcShort( 0x0 ),	/* 0 */
/* 582 */	NdrFcShort( 0x0 ),	/* 0 */
/* 584 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 586 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 588 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 590 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 592 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 594 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 596 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetVolumeLevelerEnable */

/* 598 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 600 */	NdrFcLong( 0x0 ),	/* 0 */
/* 604 */	NdrFcShort( 0xe ),	/* 14 */
/* 606 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 608 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 610 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 612 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 614 */	NdrFcShort( 0x2c ),	/* 44 */
/* 616 */	NdrFcShort( 0x0 ),	/* 0 */
/* 618 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 620 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 622 */	NdrFcShort( 0x0 ),	/* 0 */
/* 624 */	NdrFcShort( 0x0 ),	/* 0 */
/* 626 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 628 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 630 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 632 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 634 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 636 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 638 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetBassEnhancerEnable */

/* 640 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 642 */	NdrFcLong( 0x0 ),	/* 0 */
/* 646 */	NdrFcShort( 0xf ),	/* 15 */
/* 648 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 650 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 652 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 654 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 656 */	NdrFcShort( 0x24 ),	/* 36 */
/* 658 */	NdrFcShort( 0x1c ),	/* 28 */
/* 660 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 662 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 664 */	NdrFcShort( 0x0 ),	/* 0 */
/* 666 */	NdrFcShort( 0x0 ),	/* 0 */
/* 668 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 670 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 672 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 674 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 676 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 678 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 680 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetBassEnhancerEnable */

/* 682 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 684 */	NdrFcLong( 0x0 ),	/* 0 */
/* 688 */	NdrFcShort( 0x10 ),	/* 16 */
/* 690 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 692 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 694 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 696 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 698 */	NdrFcShort( 0x2c ),	/* 44 */
/* 700 */	NdrFcShort( 0x0 ),	/* 0 */
/* 702 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 704 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 706 */	NdrFcShort( 0x0 ),	/* 0 */
/* 708 */	NdrFcShort( 0x0 ),	/* 0 */
/* 710 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 712 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 714 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 716 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 718 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 720 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 722 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetGEQLevels */

/* 724 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 726 */	NdrFcLong( 0x0 ),	/* 0 */
/* 730 */	NdrFcShort( 0x11 ),	/* 17 */
/* 732 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 734 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 736 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 738 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 740 */	NdrFcShort( 0x24 ),	/* 36 */
/* 742 */	NdrFcShort( 0x0 ),	/* 0 */
/* 744 */	0x41,		/* Oi2 Flags:  srv must size, has ext, */
			0x2,		/* 2 */
/* 746 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 748 */	NdrFcShort( 0x1 ),	/* 1 */
/* 750 */	NdrFcShort( 0x0 ),	/* 0 */
/* 752 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 754 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 756 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 758 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 760 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 762 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 764 */	NdrFcShort( 0x436 ),	/* Type Offset=1078 */

	/* Procedure SetGEQLevels */

/* 766 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 768 */	NdrFcLong( 0x0 ),	/* 0 */
/* 772 */	NdrFcShort( 0x12 ),	/* 18 */
/* 774 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 776 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 778 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 780 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 782 */	NdrFcShort( 0x24 ),	/* 36 */
/* 784 */	NdrFcShort( 0x0 ),	/* 0 */
/* 786 */	0x42,		/* Oi2 Flags:  clt must size, has ext, */
			0x2,		/* 2 */
/* 788 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 790 */	NdrFcShort( 0x0 ),	/* 0 */
/* 792 */	NdrFcShort( 0x1 ),	/* 1 */
/* 794 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 796 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 798 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 800 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 802 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 804 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 806 */	NdrFcShort( 0x436 ),	/* Type Offset=1078 */

	/* Procedure ResetGEQ */

/* 808 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 810 */	NdrFcLong( 0x0 ),	/* 0 */
/* 814 */	NdrFcShort( 0x13 ),	/* 19 */
/* 816 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 818 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 820 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 822 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 824 */	NdrFcShort( 0x24 ),	/* 36 */
/* 826 */	NdrFcShort( 0x0 ),	/* 0 */
/* 828 */	0x40,		/* Oi2 Flags:  has ext, */
			0x1,		/* 1 */
/* 830 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 832 */	NdrFcShort( 0x0 ),	/* 0 */
/* 834 */	NdrFcShort( 0x0 ),	/* 0 */
/* 836 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 838 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 840 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 842 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Procedure GetDeviceMode */

/* 844 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 846 */	NdrFcLong( 0x0 ),	/* 0 */
/* 850 */	NdrFcShort( 0x14 ),	/* 20 */
/* 852 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 854 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 856 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 858 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 860 */	NdrFcShort( 0x24 ),	/* 36 */
/* 862 */	NdrFcShort( 0x1c ),	/* 28 */
/* 864 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 866 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 868 */	NdrFcShort( 0x0 ),	/* 0 */
/* 870 */	NdrFcShort( 0x0 ),	/* 0 */
/* 872 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 874 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 876 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 878 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 880 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 882 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 884 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetDeviceModeCount */

/* 886 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 888 */	NdrFcLong( 0x0 ),	/* 0 */
/* 892 */	NdrFcShort( 0x15 ),	/* 21 */
/* 894 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 896 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 898 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 900 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 902 */	NdrFcShort( 0x24 ),	/* 36 */
/* 904 */	NdrFcShort( 0x1c ),	/* 28 */
/* 906 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 908 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 910 */	NdrFcShort( 0x0 ),	/* 0 */
/* 912 */	NdrFcShort( 0x0 ),	/* 0 */
/* 914 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 916 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 918 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 920 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 922 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 924 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 926 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetDeviceModeName */

/* 928 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 930 */	NdrFcLong( 0x0 ),	/* 0 */
/* 934 */	NdrFcShort( 0x16 ),	/* 22 */
/* 936 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 938 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 940 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 942 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 944 */	NdrFcShort( 0x2c ),	/* 44 */
/* 946 */	NdrFcShort( 0x0 ),	/* 0 */
/* 948 */	0x41,		/* Oi2 Flags:  srv must size, has ext, */
			0x3,		/* 3 */
/* 950 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 952 */	NdrFcShort( 0x1 ),	/* 1 */
/* 954 */	NdrFcShort( 0x0 ),	/* 0 */
/* 956 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 958 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 960 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 962 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter index */

/* 964 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 966 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 968 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pRetVal */

/* 970 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 972 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 974 */	NdrFcShort( 0x34 ),	/* Type Offset=52 */

	/* Procedure GetDeviceModeIcon */

/* 976 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 978 */	NdrFcLong( 0x0 ),	/* 0 */
/* 982 */	NdrFcShort( 0x17 ),	/* 23 */
/* 984 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 986 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 988 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 990 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 992 */	NdrFcShort( 0x2c ),	/* 44 */
/* 994 */	NdrFcShort( 0x0 ),	/* 0 */
/* 996 */	0x41,		/* Oi2 Flags:  srv must size, has ext, */
			0x3,		/* 3 */
/* 998 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1000 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1002 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1004 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 1006 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1008 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1010 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter index */

/* 1012 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1014 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1016 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pRetVal */

/* 1018 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1020 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1022 */	NdrFcShort( 0x34 ),	/* Type Offset=52 */

	/* Procedure GetOperatorInfo */

/* 1024 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1026 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1030 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1032 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1034 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1036 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1038 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1040 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1042 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1044 */	0x41,		/* Oi2 Flags:  srv must size, has ext, */
			0x2,		/* 2 */
/* 1046 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1048 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1050 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1052 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 1054 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1056 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1058 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 1060 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1062 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1064 */	NdrFcShort( 0x34 ),	/* Type Offset=52 */

	/* Procedure GetSystemCapabilities */

/* 1066 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1068 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1072 */	NdrFcShort( 0x19 ),	/* 25 */
/* 1074 */	NdrFcShort( 0x38 ),	/* x86 Stack size/offset = 56 */
/* 1076 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1078 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1080 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1082 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1084 */	NdrFcShort( 0x152 ),	/* 338 */
/* 1086 */	0x40,		/* Oi2 Flags:  has ext, */
			0xe,		/* 14 */
/* 1088 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1090 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1092 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1094 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 1096 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1098 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1100 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter MediaIntelligenceEnabled */

/* 1102 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1104 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1106 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter VolumeLevelerEnabled */

/* 1108 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1110 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1112 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter DialogEnchancerEnabled */

/* 1114 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1116 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1118 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter VirtualBassEnabled */

/* 1120 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1122 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1124 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter BassEnchancerEnabled */

/* 1126 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1128 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1130 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter SpeakerVirtualizerEnabled */

/* 1132 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1134 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1136 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter HeadphoneVirtualizerEnabled */

/* 1138 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1140 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 1142 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter GEQEnabled */

/* 1144 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1146 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 1148 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter IEQEnabled */

/* 1150 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1152 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 1154 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter AudioOptimizerEnabled */

/* 1156 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1158 */	NdrFcShort( 0x28 ),	/* x86 Stack size/offset = 40 */
/* 1160 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter AudioRegulatorEnabled */

/* 1162 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1164 */	NdrFcShort( 0x2c ),	/* x86 Stack size/offset = 44 */
/* 1166 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter SurroundDecoderEnabled */

/* 1168 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1170 */	NdrFcShort( 0x30 ),	/* x86 Stack size/offset = 48 */
/* 1172 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter VolumeMaximizerEnabled */

/* 1174 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1176 */	NdrFcShort( 0x34 ),	/* x86 Stack size/offset = 52 */
/* 1178 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Procedure GetGEQMaximumRange */

/* 1180 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1182 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1186 */	NdrFcShort( 0x1a ),	/* 26 */
/* 1188 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1190 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1192 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1194 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1196 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1198 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1200 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 1202 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1204 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1206 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1208 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 1210 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1212 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1214 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 1216 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1218 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1220 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetAPIStatus */

/* 1222 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1224 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1228 */	NdrFcShort( 0x1b ),	/* 27 */
/* 1230 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1232 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1234 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1236 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1238 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1240 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1242 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 1244 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1246 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1248 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1250 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 1252 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1254 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1256 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 1258 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1260 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1262 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetEndpointCount */

/* 1264 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1266 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1270 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1272 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1274 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1276 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1278 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1280 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1282 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1284 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 1286 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1288 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1290 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1292 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 1294 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1296 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1298 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 1300 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1302 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1304 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetEndpointData */

/* 1306 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1308 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1312 */	NdrFcShort( 0x1d ),	/* 29 */
/* 1314 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1316 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1318 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1320 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1322 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1324 */	NdrFcShort( 0x50 ),	/* 80 */
/* 1326 */	0x41,		/* Oi2 Flags:  srv must size, has ext, */
			0x6,		/* 6 */
/* 1328 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1330 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1332 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1334 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 1336 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1338 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1340 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter nIndex */

/* 1342 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1344 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1346 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter friendlyName */

/* 1348 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1350 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1352 */	NdrFcShort( 0x34 ),	/* Type Offset=52 */

	/* Parameter formFactor */

/* 1354 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1356 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1358 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter offloaded */

/* 1360 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1362 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1364 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter defaultDevice */

/* 1366 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1368 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1370 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Procedure GetPeripheralCount */

/* 1372 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1374 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1378 */	NdrFcShort( 0x1e ),	/* 30 */
/* 1380 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1382 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1384 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1386 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1388 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1390 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1392 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 1394 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1396 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1398 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1400 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 1402 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1404 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1406 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 1408 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1410 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1412 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetPeripheralData */

/* 1414 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1416 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1420 */	NdrFcShort( 0x1f ),	/* 31 */
/* 1422 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1424 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1426 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1428 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1430 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1432 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1434 */	0x41,		/* Oi2 Flags:  srv must size, has ext, */
			0x5,		/* 5 */
/* 1436 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1438 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1440 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1442 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 1444 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1446 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1448 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter index */

/* 1450 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1452 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1454 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter brand */

/* 1456 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1458 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1460 */	NdrFcShort( 0x34 ),	/* Type Offset=52 */

	/* Parameter model */

/* 1462 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1464 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1466 */	NdrFcShort( 0x34 ),	/* Type Offset=52 */

	/* Parameter deviceBitmap */

/* 1468 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1470 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1472 */	NdrFcShort( 0x436 ),	/* Type Offset=1078 */

	/* Procedure SelectPeripheral */

/* 1474 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1476 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1480 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1482 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1484 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1486 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1488 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1490 */	NdrFcShort( 0x34 ),	/* 52 */
/* 1492 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1494 */	0x40,		/* Oi2 Flags:  has ext, */
			0x3,		/* 3 */
/* 1496 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1498 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1500 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1502 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 1504 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1506 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1508 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter endpointIndex */

/* 1510 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1512 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1514 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter periferalIndex */

/* 1516 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1518 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1520 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetSelectedPeripheral */

/* 1522 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1524 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1528 */	NdrFcShort( 0x21 ),	/* 33 */
/* 1530 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1532 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1534 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1536 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1538 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1540 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1542 */	0x40,		/* Oi2 Flags:  has ext, */
			0x3,		/* 3 */
/* 1544 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1546 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1548 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1550 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 1552 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1554 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1556 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter endpointIndex */

/* 1558 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1560 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1562 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pRetVal */

/* 1564 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1566 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1568 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IsSpatialAudioSupported */

/* 1570 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1572 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1576 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1578 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1580 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1582 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1584 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1586 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1588 */	NdrFcShort( 0x1a ),	/* 26 */
/* 1590 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 1592 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1594 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1596 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1598 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 1600 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1602 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1604 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 1606 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1608 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1610 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Procedure GetSpatialAudioStatus */

/* 1612 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 1614 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1618 */	NdrFcShort( 0x23 ),	/* 35 */
/* 1620 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1622 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 1624 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1626 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1628 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1630 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1632 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 1634 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1636 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1638 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1640 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 1642 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 1644 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1646 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 1648 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1650 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1652 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure OnDolbyEnableChanged */

/* 1654 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 1656 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1660 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1662 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1664 */	NdrFcShort( 0x16 ),	/* 22 */
/* 1666 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1668 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 1670 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1672 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1674 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1676 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 1678 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1680 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1682 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter context */

/* 1684 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1686 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1688 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnActiveProfileChanged */

/* 1690 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 1692 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1696 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1698 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1700 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1704 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 1706 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1708 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1710 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1712 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 1714 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1716 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1718 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter context */

/* 1720 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1722 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1724 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnSurroundVirtualizerEnableChanged */

/* 1726 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 1728 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1732 */	NdrFcShort( 0x2 ),	/* 2 */
/* 1734 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1736 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1738 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1740 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 1742 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1744 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1746 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1748 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 1750 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1752 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1754 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter context */

/* 1756 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1758 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1760 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnDialogEnhancerEnableChanged */

/* 1762 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 1764 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1768 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1770 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1772 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1774 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1776 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 1778 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1780 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1782 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1784 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 1786 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1788 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1790 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter context */

/* 1792 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1794 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1796 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnVolumeLevelerEnableChanged */

/* 1798 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 1800 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1804 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1806 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1808 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1810 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1812 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 1814 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1816 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1818 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1820 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 1822 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1824 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1826 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter context */

/* 1828 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1830 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1832 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnBassEnhancerEnableChanged */

/* 1834 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 1836 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1840 */	NdrFcShort( 0x5 ),	/* 5 */
/* 1842 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1844 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1846 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1848 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 1850 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1852 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1854 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1856 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 1858 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1860 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1862 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter context */

/* 1864 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1866 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1868 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnGEQLevelsChanged */

/* 1870 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 1872 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1876 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1878 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1880 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1882 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1884 */	0x42,		/* Oi2 Flags:  clt must size, has ext, */
			0x2,		/* 2 */
/* 1886 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1888 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1890 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1892 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 1894 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1896 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1898 */	NdrFcShort( 0x436 ),	/* Type Offset=1078 */

	/* Parameter context */

/* 1900 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1902 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1904 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnDefaultEndpointChanged */

/* 1906 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 1908 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1912 */	NdrFcShort( 0x7 ),	/* 7 */
/* 1914 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1916 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1918 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1920 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 1922 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1924 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1926 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1928 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 1930 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1932 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1934 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter context */

/* 1936 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1938 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1940 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnDeviceModeChanged */

/* 1942 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 1944 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1948 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1950 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1952 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1954 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1956 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 1958 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1960 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1962 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1964 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 1966 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1968 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 1970 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter context */

/* 1972 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1974 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1976 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnAPIStatusChanged */

/* 1978 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 1980 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1984 */	NdrFcShort( 0x9 ),	/* 9 */
/* 1986 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1988 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1990 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1992 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 1994 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1996 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1998 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2000 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 2002 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2004 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2006 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter context */

/* 2008 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2010 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2012 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnSpatialAudioStatusChanged */

/* 2014 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 2016 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2020 */	NdrFcShort( 0xa ),	/* 10 */
/* 2022 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2024 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2026 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2028 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 2030 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2032 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2034 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2036 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 2038 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2040 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2042 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter context */

/* 2044 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2046 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2048 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure GetDefaultUITheme */

/* 2050 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2052 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2056 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2058 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2060 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2062 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2064 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2066 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2068 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2070 */	0x41,		/* Oi2 Flags:  srv must size, has ext, */
			0x2,		/* 2 */
/* 2072 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2074 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2076 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2078 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 2080 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 2082 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2084 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 2086 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2088 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2090 */	NdrFcShort( 0x34 ),	/* Type Offset=52 */

	/* Procedure GetSKU */

/* 2092 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2094 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2098 */	NdrFcShort( 0x25 ),	/* 37 */
/* 2100 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2102 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2104 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2106 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2108 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2110 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2112 */	0x41,		/* Oi2 Flags:  srv must size, has ext, */
			0x2,		/* 2 */
/* 2114 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2116 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2118 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2120 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 2122 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 2124 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2126 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 2128 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2130 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2132 */	NdrFcShort( 0x34 ),	/* Type Offset=52 */

	/* Procedure GetActiveSubProfile */

/* 2134 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2136 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2140 */	NdrFcShort( 0x26 ),	/* 38 */
/* 2142 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2144 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2146 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2148 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2150 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2152 */	NdrFcShort( 0x1c ),	/* 28 */
/* 2154 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 2156 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2158 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2160 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2162 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 2164 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 2166 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2168 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 2170 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2172 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2174 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetActiveSubProfile */

/* 2176 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2178 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2182 */	NdrFcShort( 0x27 ),	/* 39 */
/* 2184 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2186 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2188 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2190 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2192 */	NdrFcShort( 0x2c ),	/* 44 */
/* 2194 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2196 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 2198 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2200 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2202 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2204 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 2206 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 2208 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2210 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 2212 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2214 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2216 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetSubProfileDirty */

/* 2218 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2220 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2224 */	NdrFcShort( 0x28 ),	/* 40 */
/* 2226 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2228 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2230 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2232 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2234 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2236 */	NdrFcShort( 0x1a ),	/* 26 */
/* 2238 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 2240 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2242 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2244 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2246 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 2248 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 2250 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2252 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 2254 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2256 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2258 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Procedure ResetSubProfile */

/* 2260 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2262 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2266 */	NdrFcShort( 0x29 ),	/* 41 */
/* 2268 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2270 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2272 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2274 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2276 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2278 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2280 */	0x40,		/* Oi2 Flags:  has ext, */
			0x1,		/* 1 */
/* 2282 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2284 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2286 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2288 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 2290 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 2292 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2294 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Procedure GetIEQ */

/* 2296 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2298 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2302 */	NdrFcShort( 0x2a ),	/* 42 */
/* 2304 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2306 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2308 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2310 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2312 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2314 */	NdrFcShort( 0x1c ),	/* 28 */
/* 2316 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 2318 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2320 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2322 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2324 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 2326 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 2328 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2330 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 2332 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2334 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2336 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetIEQ */

/* 2338 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2340 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2344 */	NdrFcShort( 0x2b ),	/* 43 */
/* 2346 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2348 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2350 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2352 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2354 */	NdrFcShort( 0x2c ),	/* 44 */
/* 2356 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2358 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 2360 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2362 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2364 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2366 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 2368 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 2370 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2372 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 2374 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2376 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2378 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ResetIEQ */

/* 2380 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2382 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2386 */	NdrFcShort( 0x2c ),	/* 44 */
/* 2388 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2390 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2392 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2394 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2396 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2398 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2400 */	0x40,		/* Oi2 Flags:  has ext, */
			0x1,		/* 1 */
/* 2402 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2404 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2406 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2408 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 2410 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 2412 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2414 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Procedure GetSurroundVirtualizerValue */

/* 2416 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2418 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2422 */	NdrFcShort( 0x2d ),	/* 45 */
/* 2424 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2426 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2428 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2430 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2432 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2434 */	NdrFcShort( 0x1c ),	/* 28 */
/* 2436 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 2438 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2440 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2442 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2444 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 2446 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 2448 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2450 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 2452 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2454 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2456 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Procedure SetSurroundVirtualizerValue */

/* 2458 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2460 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2464 */	NdrFcShort( 0x2e ),	/* 46 */
/* 2466 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2468 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2470 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2472 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2474 */	NdrFcShort( 0x2c ),	/* 44 */
/* 2476 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2478 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 2480 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2482 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2484 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2486 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 2488 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 2490 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2492 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 2494 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2496 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2498 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Procedure GetDialogEnhancerValue */

/* 2500 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2502 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2506 */	NdrFcShort( 0x2f ),	/* 47 */
/* 2508 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2510 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2512 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2514 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2516 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2518 */	NdrFcShort( 0x1c ),	/* 28 */
/* 2520 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 2522 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2524 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2526 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2528 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 2530 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 2532 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2534 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 2536 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2538 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2540 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Procedure SetDialogEnhancerValue */

/* 2542 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2544 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2548 */	NdrFcShort( 0x30 ),	/* 48 */
/* 2550 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2552 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2554 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2556 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2558 */	NdrFcShort( 0x2c ),	/* 44 */
/* 2560 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2562 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 2564 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2566 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2568 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2570 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 2572 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 2574 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2576 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 2578 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2580 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2582 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Procedure GetVolumeLevelerValue */

/* 2584 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2586 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2590 */	NdrFcShort( 0x31 ),	/* 49 */
/* 2592 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2594 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2596 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2598 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2600 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2602 */	NdrFcShort( 0x1c ),	/* 28 */
/* 2604 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 2606 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2608 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2610 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2612 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 2614 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 2616 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2618 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 2620 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2622 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2624 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Procedure SetVolumeLevelerValue */

/* 2626 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2628 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2632 */	NdrFcShort( 0x32 ),	/* 50 */
/* 2634 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2636 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2638 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2640 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2642 */	NdrFcShort( 0x2c ),	/* 44 */
/* 2644 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2646 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 2648 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2650 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2652 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2654 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 2656 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 2658 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2660 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 2662 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2664 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2666 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Procedure GetRadarEnable */

/* 2668 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2670 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2674 */	NdrFcShort( 0x33 ),	/* 51 */
/* 2676 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2678 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2680 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2682 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2684 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2686 */	NdrFcShort( 0x1a ),	/* 26 */
/* 2688 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 2690 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2692 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2694 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2696 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 2698 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 2700 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2702 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 2704 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2706 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2708 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Procedure SetRadarEnable */

/* 2710 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2712 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2716 */	NdrFcShort( 0x34 ),	/* 52 */
/* 2718 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2720 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2722 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2724 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2726 */	NdrFcShort( 0x2a ),	/* 42 */
/* 2728 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2730 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 2732 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2734 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2736 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2738 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 2740 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 2742 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2744 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 2746 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2748 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2750 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Procedure GetVisualizerEnable */

/* 2752 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2754 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2758 */	NdrFcShort( 0x35 ),	/* 53 */
/* 2760 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2762 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2764 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2766 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2768 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2770 */	NdrFcShort( 0x1a ),	/* 26 */
/* 2772 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 2774 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2776 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2778 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2780 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 2782 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 2784 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2786 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 2788 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2790 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2792 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Procedure SetVisualizerEnable */

/* 2794 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2796 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2800 */	NdrFcShort( 0x36 ),	/* 54 */
/* 2802 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2804 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2806 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2808 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2810 */	NdrFcShort( 0x2a ),	/* 42 */
/* 2812 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2814 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 2816 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2818 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2820 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2822 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 2824 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 2826 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2828 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 2830 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2832 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2834 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Procedure GetHotkey */

/* 2836 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2838 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2842 */	NdrFcShort( 0x37 ),	/* 55 */
/* 2844 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2846 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2848 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2850 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2852 */	NdrFcShort( 0x2c ),	/* 44 */
/* 2854 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2856 */	0x41,		/* Oi2 Flags:  srv must size, has ext, */
			0x3,		/* 3 */
/* 2858 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2860 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2862 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2864 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 2866 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 2868 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2870 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter index */

/* 2872 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2874 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2876 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pRetVal */

/* 2878 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2880 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2882 */	NdrFcShort( 0x34 ),	/* Type Offset=52 */

	/* Procedure SetHotkey */

/* 2884 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2886 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2890 */	NdrFcShort( 0x38 ),	/* 56 */
/* 2892 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2894 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2896 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2898 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2900 */	NdrFcShort( 0x2c ),	/* 44 */
/* 2902 */	NdrFcShort( 0x1c ),	/* 28 */
/* 2904 */	0x42,		/* Oi2 Flags:  clt must size, has ext, */
			0x4,		/* 4 */
/* 2906 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2908 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2910 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2912 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 2914 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 2916 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2918 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter index */

/* 2920 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2922 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2924 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter hotkey */

/* 2926 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2928 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2930 */	NdrFcShort( 0x34 ),	/* Type Offset=52 */

	/* Parameter pRetVal */

/* 2932 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2934 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2936 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetRadarSize */

/* 2938 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2940 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2944 */	NdrFcShort( 0x39 ),	/* 57 */
/* 2946 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2948 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2950 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2952 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2954 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2956 */	NdrFcShort( 0x1c ),	/* 28 */
/* 2958 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 2960 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2962 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2964 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2966 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 2968 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 2970 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2972 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 2974 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2976 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2978 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Procedure SetRadarSize */

/* 2980 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 2982 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2986 */	NdrFcShort( 0x3a ),	/* 58 */
/* 2988 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2990 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 2992 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 2994 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2996 */	NdrFcShort( 0x2c ),	/* 44 */
/* 2998 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3000 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 3002 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3004 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3006 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3008 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 3010 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 3012 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3014 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 3016 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3018 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3020 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Procedure GetRadarTransparency */

/* 3022 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 3024 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3028 */	NdrFcShort( 0x3b ),	/* 59 */
/* 3030 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3032 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 3034 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3036 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 3038 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3040 */	NdrFcShort( 0x1c ),	/* 28 */
/* 3042 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 3044 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3046 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3048 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3050 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 3052 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 3054 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3056 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 3058 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3060 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3062 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Procedure SetRadarTransparency */

/* 3064 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 3066 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3070 */	NdrFcShort( 0x3c ),	/* 60 */
/* 3072 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3074 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 3076 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3078 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 3080 */	NdrFcShort( 0x2c ),	/* 44 */
/* 3082 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3084 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 3086 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3088 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3090 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3092 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 3094 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 3096 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3098 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 3100 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3102 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3104 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Procedure GetRadarSkin */

/* 3106 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 3108 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3112 */	NdrFcShort( 0x3d ),	/* 61 */
/* 3114 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3116 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 3118 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3120 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 3122 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3124 */	NdrFcShort( 0x1c ),	/* 28 */
/* 3126 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 3128 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3130 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3132 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3134 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 3136 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 3138 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3140 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 3142 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3144 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3146 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetRadarSkin */

/* 3148 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 3150 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3154 */	NdrFcShort( 0x3e ),	/* 62 */
/* 3156 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3158 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 3160 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3162 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 3164 */	NdrFcShort( 0x2c ),	/* 44 */
/* 3166 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3168 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 3170 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3172 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3174 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3176 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 3178 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 3180 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3182 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 3184 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3186 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3188 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetRadarMaxDirection */

/* 3190 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 3192 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3196 */	NdrFcShort( 0x3f ),	/* 63 */
/* 3198 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3200 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 3202 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3204 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 3206 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3208 */	NdrFcShort( 0x1c ),	/* 28 */
/* 3210 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 3212 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3214 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3216 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3218 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 3220 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 3222 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3224 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 3226 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3228 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3230 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetRadarMaxDirection */

/* 3232 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 3234 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3238 */	NdrFcShort( 0x40 ),	/* 64 */
/* 3240 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3242 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 3244 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3246 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 3248 */	NdrFcShort( 0x2c ),	/* 44 */
/* 3250 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3252 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 3254 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3256 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3258 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3260 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 3262 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 3264 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3266 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 3268 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3270 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3272 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetRadarPosition */

/* 3274 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 3276 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3280 */	NdrFcShort( 0x41 ),	/* 65 */
/* 3282 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3284 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 3286 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3288 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 3290 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3292 */	NdrFcShort( 0x38 ),	/* 56 */
/* 3294 */	0x40,		/* Oi2 Flags:  has ext, */
			0x3,		/* 3 */
/* 3296 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3298 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3300 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3302 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 3304 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 3306 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3308 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter x */

/* 3310 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3312 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3314 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter y */

/* 3316 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3318 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3320 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Procedure SetRadarPosition */

/* 3322 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 3324 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3328 */	NdrFcShort( 0x42 ),	/* 66 */
/* 3330 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3332 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 3334 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3336 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 3338 */	NdrFcShort( 0x34 ),	/* 52 */
/* 3340 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3342 */	0x40,		/* Oi2 Flags:  has ext, */
			0x3,		/* 3 */
/* 3344 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3346 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3348 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3350 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 3352 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 3354 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3356 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter x */

/* 3358 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3360 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3362 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter y */

/* 3364 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3366 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3368 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Procedure SetRadarRefreshRate */

/* 3370 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 3372 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3376 */	NdrFcShort( 0x43 ),	/* 67 */
/* 3378 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3380 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 3382 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3384 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 3386 */	NdrFcShort( 0x2c ),	/* 44 */
/* 3388 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3390 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 3392 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3394 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3396 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3398 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 3400 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 3402 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3404 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 3406 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3408 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3410 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetRadarRefreshRate */

/* 3412 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 3414 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3418 */	NdrFcShort( 0x44 ),	/* 68 */
/* 3420 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3422 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 3424 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3426 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 3428 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3430 */	NdrFcShort( 0x1c ),	/* 28 */
/* 3432 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 3434 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3436 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3438 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3440 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 3442 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 3444 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3446 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 3448 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3450 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3452 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetSoundMap */

/* 3454 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 3456 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3460 */	NdrFcShort( 0x45 ),	/* 69 */
/* 3462 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3464 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 3466 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3468 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 3470 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3472 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3474 */	0x41,		/* Oi2 Flags:  srv must size, has ext, */
			0x3,		/* 3 */
/* 3476 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3478 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3480 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3482 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 3484 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 3486 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3488 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter sectEdges */

/* 3490 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3492 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3494 */	NdrFcShort( 0x436 ),	/* Type Offset=1078 */

	/* Parameter strengths */

/* 3496 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3498 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3500 */	NdrFcShort( 0x436 ),	/* Type Offset=1078 */

	/* Procedure SetVisualizerRefreshRate */

/* 3502 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 3504 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3508 */	NdrFcShort( 0x46 ),	/* 70 */
/* 3510 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3512 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 3514 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3516 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 3518 */	NdrFcShort( 0x2c ),	/* 44 */
/* 3520 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3522 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 3524 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3526 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3528 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3530 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 3532 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 3534 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3536 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 3538 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3540 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3542 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetVisualizerRefreshRate */

/* 3544 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 3546 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3550 */	NdrFcShort( 0x47 ),	/* 71 */
/* 3552 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3554 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 3556 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3558 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 3560 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3562 */	NdrFcShort( 0x1c ),	/* 28 */
/* 3564 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 3566 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3568 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3570 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3572 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 3574 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 3576 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3578 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 3580 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3582 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3584 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetVisualizerData */

/* 3586 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 3588 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3592 */	NdrFcShort( 0x48 ),	/* 72 */
/* 3594 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3596 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* Ctxt flags:  in, */
/* 3598 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3600 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 3602 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3604 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3606 */	0x41,		/* Oi2 Flags:  srv must size, has ext, */
			0x2,		/* 2 */
/* 3608 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3610 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3612 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3614 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter phContext */

/* 3616 */	NdrFcShort( 0x8 ),	/* Flags:  in, */
/* 3618 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3620 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter pRetVal */

/* 3622 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3624 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3626 */	NdrFcShort( 0x436 ),	/* Type Offset=1078 */

	/* Procedure OnActiveSubProfileChanged */

/* 3628 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 3630 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3634 */	NdrFcShort( 0xb ),	/* 11 */
/* 3636 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3638 */	NdrFcShort( 0x18 ),	/* 24 */
/* 3640 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3642 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 3644 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3646 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3648 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3650 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 3652 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3654 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3656 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter context */

/* 3658 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3660 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3662 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnSubProfileReset */

/* 3664 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 3666 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3670 */	NdrFcShort( 0xc ),	/* 12 */
/* 3672 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3674 */	NdrFcShort( 0x10 ),	/* 16 */
/* 3676 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3678 */	0x40,		/* Oi2 Flags:  has ext, */
			0x1,		/* 1 */
/* 3680 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3682 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3684 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3686 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter context */

/* 3688 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3690 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3692 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnIEQChanged */

/* 3694 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 3696 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3700 */	NdrFcShort( 0xd ),	/* 13 */
/* 3702 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3704 */	NdrFcShort( 0x18 ),	/* 24 */
/* 3706 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3708 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 3710 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3712 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3714 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3716 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 3718 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3720 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3722 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter context */

/* 3724 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3726 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3728 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnSurroundVirtualizerValueChanged */

/* 3730 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 3732 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3736 */	NdrFcShort( 0xe ),	/* 14 */
/* 3738 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3740 */	NdrFcShort( 0x18 ),	/* 24 */
/* 3742 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3744 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 3746 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3748 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3750 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3752 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 3754 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3756 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3758 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter context */

/* 3760 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3762 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3764 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnDialogEnhancerValueChanged */

/* 3766 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 3768 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3772 */	NdrFcShort( 0xf ),	/* 15 */
/* 3774 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3776 */	NdrFcShort( 0x18 ),	/* 24 */
/* 3778 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3780 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 3782 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3784 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3786 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3788 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 3790 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3792 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3794 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter context */

/* 3796 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3798 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3800 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnVolumeLevelerValueChanged */

/* 3802 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 3804 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3808 */	NdrFcShort( 0x10 ),	/* 16 */
/* 3810 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3812 */	NdrFcShort( 0x18 ),	/* 24 */
/* 3814 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3816 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 3818 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3820 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3822 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3824 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 3826 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3828 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3830 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter context */

/* 3832 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3834 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3836 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnRadarEnableChanged */

/* 3838 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 3840 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3844 */	NdrFcShort( 0x11 ),	/* 17 */
/* 3846 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3848 */	NdrFcShort( 0x16 ),	/* 22 */
/* 3850 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3852 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 3854 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3856 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3858 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3860 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 3862 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3864 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3866 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter context */

/* 3868 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3870 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3872 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnSubProfileDirtyChanged */

/* 3874 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 3876 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3880 */	NdrFcShort( 0x12 ),	/* 18 */
/* 3882 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3884 */	NdrFcShort( 0x16 ),	/* 22 */
/* 3886 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3888 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 3890 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3892 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3894 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3896 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 3898 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3900 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3902 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter context */

/* 3904 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3906 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3908 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnHotkeyChanged */

/* 3910 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 3912 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3916 */	NdrFcShort( 0x13 ),	/* 19 */
/* 3918 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3920 */	NdrFcShort( 0x18 ),	/* 24 */
/* 3922 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3924 */	0x42,		/* Oi2 Flags:  clt must size, has ext, */
			0x3,		/* 3 */
/* 3926 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3928 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3930 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3932 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 3934 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3936 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3938 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter hotkey */

/* 3940 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3942 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3944 */	NdrFcShort( 0x34 ),	/* Type Offset=52 */

	/* Parameter context */

/* 3946 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3948 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3950 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnRadarSizeChanged */

/* 3952 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 3954 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3958 */	NdrFcShort( 0x14 ),	/* 20 */
/* 3960 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3962 */	NdrFcShort( 0x18 ),	/* 24 */
/* 3964 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3966 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 3968 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3970 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3972 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3974 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 3976 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3978 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 3980 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter context */

/* 3982 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3984 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3986 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnRadarTransparencyChanged */

/* 3988 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 3990 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3994 */	NdrFcShort( 0x15 ),	/* 21 */
/* 3996 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3998 */	NdrFcShort( 0x18 ),	/* 24 */
/* 4000 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4002 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 4004 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4006 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4008 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4010 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 4012 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4014 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 4016 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter context */

/* 4018 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4020 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4022 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnRadarPositionChanged */

/* 4024 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 4026 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4030 */	NdrFcShort( 0x16 ),	/* 22 */
/* 4032 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4034 */	NdrFcShort( 0x20 ),	/* 32 */
/* 4036 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4038 */	0x40,		/* Oi2 Flags:  has ext, */
			0x3,		/* 3 */
/* 4040 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4042 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4044 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4046 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter x */

/* 4048 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4050 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 4052 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter y */

/* 4054 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4056 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4058 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter context */

/* 4060 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4062 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4064 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnRadarSkinChanged */

/* 4066 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 4068 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4072 */	NdrFcShort( 0x17 ),	/* 23 */
/* 4074 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4076 */	NdrFcShort( 0x18 ),	/* 24 */
/* 4078 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4080 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 4082 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4084 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4086 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4088 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 4090 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4092 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 4094 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter context */

/* 4096 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4098 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4100 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnRadarMaxDirectionChanged */

/* 4102 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 4104 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4108 */	NdrFcShort( 0x18 ),	/* 24 */
/* 4110 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4112 */	NdrFcShort( 0x18 ),	/* 24 */
/* 4114 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4116 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 4118 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4120 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4122 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4124 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 4126 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4128 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 4130 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter context */

/* 4132 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4134 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4136 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnVisualizerEnableChanged */

/* 4138 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 4140 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4144 */	NdrFcShort( 0x19 ),	/* 25 */
/* 4146 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4148 */	NdrFcShort( 0x16 ),	/* 22 */
/* 4150 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4152 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 4154 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4156 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4158 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4160 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 4162 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4164 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 4166 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter context */

/* 4168 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4170 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4172 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure OnVisualizerRefreshRateChanged */

/* 4174 */	0x34,		/* FC_CALLBACK_HANDLE */
			0x48,		/* Old Flags:  */
/* 4176 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4180 */	NdrFcShort( 0x1a ),	/* 26 */
/* 4182 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4184 */	NdrFcShort( 0x18 ),	/* 24 */
/* 4186 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4188 */	0x40,		/* Oi2 Flags:  has ext, */
			0x2,		/* 2 */
/* 4190 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4192 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4194 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4196 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newValue */

/* 4198 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4200 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 4202 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter context */

/* 4204 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4206 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4208 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

			0x0
        }
    };

static const idl_MIDL_TYPE_FORMAT_STRING idl__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/*  4 */	NdrFcShort( 0x2 ),	/* Offset= 2 (6) */
/*  6 */	0x30,		/* FC_BIND_CONTEXT */
			0xa0,		/* Ctxt flags:  via ptr, out, */
/*  8 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 10 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 12 */	NdrFcShort( 0x2 ),	/* Offset= 2 (14) */
/* 14 */	0x30,		/* FC_BIND_CONTEXT */
			0xe1,		/* Ctxt flags:  via ptr, in, out, can't be null */
/* 16 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 18 */	0x30,		/* FC_BIND_CONTEXT */
			0x41,		/* Ctxt flags:  in, can't be null */
/* 20 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 22 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 24 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 26 */	
			0x12, 0x0,	/* FC_UP */
/* 28 */	NdrFcShort( 0xe ),	/* Offset= 14 (42) */
/* 30 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 32 */	NdrFcShort( 0x2 ),	/* 2 */
/* 34 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 36 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 38 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 40 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 42 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 44 */	NdrFcShort( 0x8 ),	/* 8 */
/* 46 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (30) */
/* 48 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 50 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 52 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x4 ),	/* 4 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */
/* 60 */	NdrFcShort( 0xffde ),	/* Offset= -34 (26) */
/* 62 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 64 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 66 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 68 */	NdrFcShort( 0x3f2 ),	/* Offset= 1010 (1078) */
/* 70 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 72 */	NdrFcShort( 0x2 ),	/* Offset= 2 (74) */
/* 74 */	
			0x12, 0x0,	/* FC_UP */
/* 76 */	NdrFcShort( 0x3d8 ),	/* Offset= 984 (1060) */
/* 78 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 80 */	NdrFcShort( 0x18 ),	/* 24 */
/* 82 */	NdrFcShort( 0xa ),	/* 10 */
/* 84 */	NdrFcLong( 0x8 ),	/* 8 */
/* 88 */	NdrFcShort( 0x5a ),	/* Offset= 90 (178) */
/* 90 */	NdrFcLong( 0xd ),	/* 13 */
/* 94 */	NdrFcShort( 0x90 ),	/* Offset= 144 (238) */
/* 96 */	NdrFcLong( 0x9 ),	/* 9 */
/* 100 */	NdrFcShort( 0xc2 ),	/* Offset= 194 (294) */
/* 102 */	NdrFcLong( 0xc ),	/* 12 */
/* 106 */	NdrFcShort( 0x2bc ),	/* Offset= 700 (806) */
/* 108 */	NdrFcLong( 0x24 ),	/* 36 */
/* 112 */	NdrFcShort( 0x2e6 ),	/* Offset= 742 (854) */
/* 114 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 118 */	NdrFcShort( 0x302 ),	/* Offset= 770 (888) */
/* 120 */	NdrFcLong( 0x10 ),	/* 16 */
/* 124 */	NdrFcShort( 0x31c ),	/* Offset= 796 (920) */
/* 126 */	NdrFcLong( 0x2 ),	/* 2 */
/* 130 */	NdrFcShort( 0x336 ),	/* Offset= 822 (952) */
/* 132 */	NdrFcLong( 0x3 ),	/* 3 */
/* 136 */	NdrFcShort( 0x350 ),	/* Offset= 848 (984) */
/* 138 */	NdrFcLong( 0x14 ),	/* 20 */
/* 142 */	NdrFcShort( 0x36a ),	/* Offset= 874 (1016) */
/* 144 */	NdrFcShort( 0xffff ),	/* Offset= -1 (143) */
/* 146 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 148 */	NdrFcShort( 0x4 ),	/* 4 */
/* 150 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 152 */	NdrFcShort( 0x0 ),	/* 0 */
/* 154 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 156 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 158 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 160 */	NdrFcShort( 0x4 ),	/* 4 */
/* 162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 164 */	NdrFcShort( 0x1 ),	/* 1 */
/* 166 */	NdrFcShort( 0x0 ),	/* 0 */
/* 168 */	NdrFcShort( 0x0 ),	/* 0 */
/* 170 */	0x12, 0x0,	/* FC_UP */
/* 172 */	NdrFcShort( 0xff7e ),	/* Offset= -130 (42) */
/* 174 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 176 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 178 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 180 */	NdrFcShort( 0x8 ),	/* 8 */
/* 182 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 184 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 186 */	NdrFcShort( 0x4 ),	/* 4 */
/* 188 */	NdrFcShort( 0x4 ),	/* 4 */
/* 190 */	0x11, 0x0,	/* FC_RP */
/* 192 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (146) */
/* 194 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 196 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 198 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 200 */	NdrFcLong( 0x0 ),	/* 0 */
/* 204 */	NdrFcShort( 0x0 ),	/* 0 */
/* 206 */	NdrFcShort( 0x0 ),	/* 0 */
/* 208 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 210 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 212 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 214 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 216 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 218 */	NdrFcShort( 0x0 ),	/* 0 */
/* 220 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 222 */	NdrFcShort( 0x0 ),	/* 0 */
/* 224 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 226 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 230 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 232 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 234 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (198) */
/* 236 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 238 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 240 */	NdrFcShort( 0x8 ),	/* 8 */
/* 242 */	NdrFcShort( 0x0 ),	/* 0 */
/* 244 */	NdrFcShort( 0x6 ),	/* Offset= 6 (250) */
/* 246 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 248 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 250 */	
			0x11, 0x0,	/* FC_RP */
/* 252 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (216) */
/* 254 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 256 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 260 */	NdrFcShort( 0x0 ),	/* 0 */
/* 262 */	NdrFcShort( 0x0 ),	/* 0 */
/* 264 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 266 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 268 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 270 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 272 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 274 */	NdrFcShort( 0x0 ),	/* 0 */
/* 276 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 278 */	NdrFcShort( 0x0 ),	/* 0 */
/* 280 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 282 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 286 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 288 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 290 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (254) */
/* 292 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 294 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 296 */	NdrFcShort( 0x8 ),	/* 8 */
/* 298 */	NdrFcShort( 0x0 ),	/* 0 */
/* 300 */	NdrFcShort( 0x6 ),	/* Offset= 6 (306) */
/* 302 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 304 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 306 */	
			0x11, 0x0,	/* FC_RP */
/* 308 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (272) */
/* 310 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 312 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 314 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 316 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 318 */	NdrFcShort( 0x2 ),	/* Offset= 2 (320) */
/* 320 */	NdrFcShort( 0x10 ),	/* 16 */
/* 322 */	NdrFcShort( 0x2f ),	/* 47 */
/* 324 */	NdrFcLong( 0x14 ),	/* 20 */
/* 328 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 330 */	NdrFcLong( 0x3 ),	/* 3 */
/* 334 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 336 */	NdrFcLong( 0x11 ),	/* 17 */
/* 340 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 342 */	NdrFcLong( 0x2 ),	/* 2 */
/* 346 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 348 */	NdrFcLong( 0x4 ),	/* 4 */
/* 352 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 354 */	NdrFcLong( 0x5 ),	/* 5 */
/* 358 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 360 */	NdrFcLong( 0xb ),	/* 11 */
/* 364 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 366 */	NdrFcLong( 0xa ),	/* 10 */
/* 370 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 372 */	NdrFcLong( 0x6 ),	/* 6 */
/* 376 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (608) */
/* 378 */	NdrFcLong( 0x7 ),	/* 7 */
/* 382 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 384 */	NdrFcLong( 0x8 ),	/* 8 */
/* 388 */	NdrFcShort( 0xfe96 ),	/* Offset= -362 (26) */
/* 390 */	NdrFcLong( 0xd ),	/* 13 */
/* 394 */	NdrFcShort( 0xff3c ),	/* Offset= -196 (198) */
/* 396 */	NdrFcLong( 0x9 ),	/* 9 */
/* 400 */	NdrFcShort( 0xff6e ),	/* Offset= -146 (254) */
/* 402 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 406 */	NdrFcShort( 0xd0 ),	/* Offset= 208 (614) */
/* 408 */	NdrFcLong( 0x24 ),	/* 36 */
/* 412 */	NdrFcShort( 0xd2 ),	/* Offset= 210 (622) */
/* 414 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 418 */	NdrFcShort( 0xcc ),	/* Offset= 204 (622) */
/* 420 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 424 */	NdrFcShort( 0xfc ),	/* Offset= 252 (676) */
/* 426 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 430 */	NdrFcShort( 0xfa ),	/* Offset= 250 (680) */
/* 432 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 436 */	NdrFcShort( 0xf8 ),	/* Offset= 248 (684) */
/* 438 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 442 */	NdrFcShort( 0xf6 ),	/* Offset= 246 (688) */
/* 444 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 448 */	NdrFcShort( 0xf4 ),	/* Offset= 244 (692) */
/* 450 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 454 */	NdrFcShort( 0xf2 ),	/* Offset= 242 (696) */
/* 456 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 460 */	NdrFcShort( 0xdc ),	/* Offset= 220 (680) */
/* 462 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 466 */	NdrFcShort( 0xda ),	/* Offset= 218 (684) */
/* 468 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 472 */	NdrFcShort( 0xe4 ),	/* Offset= 228 (700) */
/* 474 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 478 */	NdrFcShort( 0xda ),	/* Offset= 218 (696) */
/* 480 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 484 */	NdrFcShort( 0xdc ),	/* Offset= 220 (704) */
/* 486 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 490 */	NdrFcShort( 0xda ),	/* Offset= 218 (708) */
/* 492 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 496 */	NdrFcShort( 0xd8 ),	/* Offset= 216 (712) */
/* 498 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 502 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (716) */
/* 504 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 508 */	NdrFcShort( 0xdc ),	/* Offset= 220 (728) */
/* 510 */	NdrFcLong( 0x10 ),	/* 16 */
/* 514 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 516 */	NdrFcLong( 0x12 ),	/* 18 */
/* 520 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 522 */	NdrFcLong( 0x13 ),	/* 19 */
/* 526 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 528 */	NdrFcLong( 0x15 ),	/* 21 */
/* 532 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 534 */	NdrFcLong( 0x16 ),	/* 22 */
/* 538 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 540 */	NdrFcLong( 0x17 ),	/* 23 */
/* 544 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 546 */	NdrFcLong( 0xe ),	/* 14 */
/* 550 */	NdrFcShort( 0xba ),	/* Offset= 186 (736) */
/* 552 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 556 */	NdrFcShort( 0xbe ),	/* Offset= 190 (746) */
/* 558 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 562 */	NdrFcShort( 0xbc ),	/* Offset= 188 (750) */
/* 564 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 568 */	NdrFcShort( 0x70 ),	/* Offset= 112 (680) */
/* 570 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 574 */	NdrFcShort( 0x6e ),	/* Offset= 110 (684) */
/* 576 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 580 */	NdrFcShort( 0x6c ),	/* Offset= 108 (688) */
/* 582 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 586 */	NdrFcShort( 0x62 ),	/* Offset= 98 (684) */
/* 588 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 592 */	NdrFcShort( 0x5c ),	/* Offset= 92 (684) */
/* 594 */	NdrFcLong( 0x0 ),	/* 0 */
/* 598 */	NdrFcShort( 0x0 ),	/* Offset= 0 (598) */
/* 600 */	NdrFcLong( 0x1 ),	/* 1 */
/* 604 */	NdrFcShort( 0x0 ),	/* Offset= 0 (604) */
/* 606 */	NdrFcShort( 0xffff ),	/* Offset= -1 (605) */
/* 608 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 610 */	NdrFcShort( 0x8 ),	/* 8 */
/* 612 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 614 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 616 */	NdrFcShort( 0x2 ),	/* Offset= 2 (618) */
/* 618 */	
			0x12, 0x0,	/* FC_UP */
/* 620 */	NdrFcShort( 0x1b8 ),	/* Offset= 440 (1060) */
/* 622 */	
			0x12, 0x0,	/* FC_UP */
/* 624 */	NdrFcShort( 0x20 ),	/* Offset= 32 (656) */
/* 626 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 628 */	NdrFcLong( 0x2f ),	/* 47 */
/* 632 */	NdrFcShort( 0x0 ),	/* 0 */
/* 634 */	NdrFcShort( 0x0 ),	/* 0 */
/* 636 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 638 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 640 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 642 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 644 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 646 */	NdrFcShort( 0x1 ),	/* 1 */
/* 648 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 650 */	NdrFcShort( 0x4 ),	/* 4 */
/* 652 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 654 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 656 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 658 */	NdrFcShort( 0x10 ),	/* 16 */
/* 660 */	NdrFcShort( 0x0 ),	/* 0 */
/* 662 */	NdrFcShort( 0xa ),	/* Offset= 10 (672) */
/* 664 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 666 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 668 */	NdrFcShort( 0xffd6 ),	/* Offset= -42 (626) */
/* 670 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 672 */	
			0x12, 0x0,	/* FC_UP */
/* 674 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (644) */
/* 676 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 678 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 680 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 682 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 684 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 686 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 688 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 690 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 692 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 694 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 696 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 698 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 700 */	
			0x12, 0x0,	/* FC_UP */
/* 702 */	NdrFcShort( 0xffa2 ),	/* Offset= -94 (608) */
/* 704 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 706 */	NdrFcShort( 0xfd58 ),	/* Offset= -680 (26) */
/* 708 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 710 */	NdrFcShort( 0xfe00 ),	/* Offset= -512 (198) */
/* 712 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 714 */	NdrFcShort( 0xfe34 ),	/* Offset= -460 (254) */
/* 716 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 718 */	NdrFcShort( 0x2 ),	/* Offset= 2 (720) */
/* 720 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 722 */	NdrFcShort( 0x2 ),	/* Offset= 2 (724) */
/* 724 */	
			0x12, 0x0,	/* FC_UP */
/* 726 */	NdrFcShort( 0x14e ),	/* Offset= 334 (1060) */
/* 728 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 730 */	NdrFcShort( 0x2 ),	/* Offset= 2 (732) */
/* 732 */	
			0x12, 0x0,	/* FC_UP */
/* 734 */	NdrFcShort( 0x14 ),	/* Offset= 20 (754) */
/* 736 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 738 */	NdrFcShort( 0x10 ),	/* 16 */
/* 740 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 742 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 744 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 746 */	
			0x12, 0x0,	/* FC_UP */
/* 748 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (736) */
/* 750 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 752 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 754 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 756 */	NdrFcShort( 0x20 ),	/* 32 */
/* 758 */	NdrFcShort( 0x0 ),	/* 0 */
/* 760 */	NdrFcShort( 0x0 ),	/* Offset= 0 (760) */
/* 762 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 764 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 766 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 768 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 770 */	NdrFcShort( 0xfe34 ),	/* Offset= -460 (310) */
/* 772 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 774 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 776 */	NdrFcShort( 0x4 ),	/* 4 */
/* 778 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 780 */	NdrFcShort( 0x0 ),	/* 0 */
/* 782 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 784 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 786 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 788 */	NdrFcShort( 0x4 ),	/* 4 */
/* 790 */	NdrFcShort( 0x0 ),	/* 0 */
/* 792 */	NdrFcShort( 0x1 ),	/* 1 */
/* 794 */	NdrFcShort( 0x0 ),	/* 0 */
/* 796 */	NdrFcShort( 0x0 ),	/* 0 */
/* 798 */	0x12, 0x0,	/* FC_UP */
/* 800 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (754) */
/* 802 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 804 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 806 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 808 */	NdrFcShort( 0x8 ),	/* 8 */
/* 810 */	NdrFcShort( 0x0 ),	/* 0 */
/* 812 */	NdrFcShort( 0x6 ),	/* Offset= 6 (818) */
/* 814 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 816 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 818 */	
			0x11, 0x0,	/* FC_RP */
/* 820 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (774) */
/* 822 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 824 */	NdrFcShort( 0x4 ),	/* 4 */
/* 826 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 828 */	NdrFcShort( 0x0 ),	/* 0 */
/* 830 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 832 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 834 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 836 */	NdrFcShort( 0x4 ),	/* 4 */
/* 838 */	NdrFcShort( 0x0 ),	/* 0 */
/* 840 */	NdrFcShort( 0x1 ),	/* 1 */
/* 842 */	NdrFcShort( 0x0 ),	/* 0 */
/* 844 */	NdrFcShort( 0x0 ),	/* 0 */
/* 846 */	0x12, 0x0,	/* FC_UP */
/* 848 */	NdrFcShort( 0xff40 ),	/* Offset= -192 (656) */
/* 850 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 852 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 854 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 856 */	NdrFcShort( 0x8 ),	/* 8 */
/* 858 */	NdrFcShort( 0x0 ),	/* 0 */
/* 860 */	NdrFcShort( 0x6 ),	/* Offset= 6 (866) */
/* 862 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 864 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 866 */	
			0x11, 0x0,	/* FC_RP */
/* 868 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (822) */
/* 870 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 872 */	NdrFcShort( 0x8 ),	/* 8 */
/* 874 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 876 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 878 */	NdrFcShort( 0x10 ),	/* 16 */
/* 880 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 882 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 884 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (870) */
			0x5b,		/* FC_END */
/* 888 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 890 */	NdrFcShort( 0x18 ),	/* 24 */
/* 892 */	NdrFcShort( 0x0 ),	/* 0 */
/* 894 */	NdrFcShort( 0xa ),	/* Offset= 10 (904) */
/* 896 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 898 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 900 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (876) */
/* 902 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 904 */	
			0x11, 0x0,	/* FC_RP */
/* 906 */	NdrFcShort( 0xfd4e ),	/* Offset= -690 (216) */
/* 908 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 910 */	NdrFcShort( 0x1 ),	/* 1 */
/* 912 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 914 */	NdrFcShort( 0x0 ),	/* 0 */
/* 916 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 918 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 920 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 922 */	NdrFcShort( 0x8 ),	/* 8 */
/* 924 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 926 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 928 */	NdrFcShort( 0x4 ),	/* 4 */
/* 930 */	NdrFcShort( 0x4 ),	/* 4 */
/* 932 */	0x12, 0x0,	/* FC_UP */
/* 934 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (908) */
/* 936 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 938 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 940 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 942 */	NdrFcShort( 0x2 ),	/* 2 */
/* 944 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 946 */	NdrFcShort( 0x0 ),	/* 0 */
/* 948 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 950 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 952 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 954 */	NdrFcShort( 0x8 ),	/* 8 */
/* 956 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 958 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 960 */	NdrFcShort( 0x4 ),	/* 4 */
/* 962 */	NdrFcShort( 0x4 ),	/* 4 */
/* 964 */	0x12, 0x0,	/* FC_UP */
/* 966 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (940) */
/* 968 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 970 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 972 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 974 */	NdrFcShort( 0x4 ),	/* 4 */
/* 976 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 978 */	NdrFcShort( 0x0 ),	/* 0 */
/* 980 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 982 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 984 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 986 */	NdrFcShort( 0x8 ),	/* 8 */
/* 988 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 990 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 992 */	NdrFcShort( 0x4 ),	/* 4 */
/* 994 */	NdrFcShort( 0x4 ),	/* 4 */
/* 996 */	0x12, 0x0,	/* FC_UP */
/* 998 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (972) */
/* 1000 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1002 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 1004 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 1006 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1008 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1010 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1012 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1014 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 1016 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1018 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1020 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1022 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1024 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1026 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1028 */	0x12, 0x0,	/* FC_UP */
/* 1030 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (1004) */
/* 1032 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1034 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 1036 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 1038 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1040 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1042 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1044 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 1046 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1048 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 1050 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 1052 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1054 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1056 */	NdrFcShort( 0xffec ),	/* Offset= -20 (1036) */
/* 1058 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1060 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1062 */	NdrFcShort( 0x28 ),	/* 40 */
/* 1064 */	NdrFcShort( 0xffec ),	/* Offset= -20 (1044) */
/* 1066 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1066) */
/* 1068 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1070 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1072 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1074 */	NdrFcShort( 0xfc1c ),	/* Offset= -996 (78) */
/* 1076 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1078 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1080 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1082 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1084 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1086 */	NdrFcShort( 0xfc08 ),	/* Offset= -1016 (70) */
/* 1088 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1090 */	NdrFcShort( 0xfbf2 ),	/* Offset= -1038 (52) */
/* 1092 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1094 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            },
            {
            LPSAFEARRAY_UserSize
            ,LPSAFEARRAY_UserMarshal
            ,LPSAFEARRAY_UserUnmarshal
            ,LPSAFEARRAY_UserFree
            }

        };


static const unsigned short RpcInterface_FormatStringOffsetTable[] =
    {
    0,
    34,
    70,
    130,
    172,
    220,
    262,
    304,
    346,
    388,
    430,
    472,
    514,
    556,
    598,
    640,
    682,
    724,
    766,
    808,
    844,
    886,
    928,
    976,
    1024,
    1066,
    1180,
    1222,
    1264,
    1306,
    1372,
    1414,
    1474,
    1522,
    1570,
    1612,
    2050,
    2092,
    2134,
    2176,
    2218,
    2260,
    2296,
    2338,
    2380,
    2416,
    2458,
    2500,
    2542,
    2584,
    2626,
    2668,
    2710,
    2752,
    2794,
    2836,
    2884,
    2938,
    2980,
    3022,
    3064,
    3106,
    3148,
    3190,
    3232,
    3274,
    3322,
    3370,
    3412,
    3454,
    3502,
    3544,
    3586,
    };


static const unsigned short _callbackRpcInterface_FormatStringOffsetTable[] =
    {
    1654,
    1690,
    1726,
    1762,
    1798,
    1834,
    1870,
    1906,
    1942,
    1978,
    2014,
    3628,
    3664,
    3694,
    3730,
    3766,
    3802,
    3838,
    3874,
    3910,
    3952,
    3988,
    4024,
    4066,
    4102,
    4138,
    4174
    };


static const MIDL_STUB_DESC RpcInterface_StubDesc = 
    {
    (void *)& RpcInterface___RpcClientInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    &RpcInterface__MIDL_AutoBindHandle,
    0,
    0,
    0,
    0,
    idl__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x800025b, /* MIDL Version 8.0.603 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

static const RPC_DISPATCH_FUNCTION RpcInterface_table[] =
    {
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    0
    };
static const RPC_DISPATCH_TABLE RpcInterface_v1_0_DispatchTable = 
    {
    27,
    (RPC_DISPATCH_FUNCTION*)RpcInterface_table
    };

static const SERVER_ROUTINE RpcInterface_ServerRoutineTable[] = 
    {
    (SERVER_ROUTINE)OnDolbyEnableChanged,
    (SERVER_ROUTINE)OnActiveProfileChanged,
    (SERVER_ROUTINE)OnSurroundVirtualizerEnableChanged,
    (SERVER_ROUTINE)OnDialogEnhancerEnableChanged,
    (SERVER_ROUTINE)OnVolumeLevelerEnableChanged,
    (SERVER_ROUTINE)OnBassEnhancerEnableChanged,
    (SERVER_ROUTINE)OnGEQLevelsChanged,
    (SERVER_ROUTINE)OnDefaultEndpointChanged,
    (SERVER_ROUTINE)OnDeviceModeChanged,
    (SERVER_ROUTINE)OnAPIStatusChanged,
    (SERVER_ROUTINE)OnSpatialAudioStatusChanged,
    (SERVER_ROUTINE)OnActiveSubProfileChanged,
    (SERVER_ROUTINE)OnSubProfileReset,
    (SERVER_ROUTINE)OnIEQChanged,
    (SERVER_ROUTINE)OnSurroundVirtualizerValueChanged,
    (SERVER_ROUTINE)OnDialogEnhancerValueChanged,
    (SERVER_ROUTINE)OnVolumeLevelerValueChanged,
    (SERVER_ROUTINE)OnRadarEnableChanged,
    (SERVER_ROUTINE)OnSubProfileDirtyChanged,
    (SERVER_ROUTINE)OnHotkeyChanged,
    (SERVER_ROUTINE)OnRadarSizeChanged,
    (SERVER_ROUTINE)OnRadarTransparencyChanged,
    (SERVER_ROUTINE)OnRadarPositionChanged,
    (SERVER_ROUTINE)OnRadarSkinChanged,
    (SERVER_ROUTINE)OnRadarMaxDirectionChanged,
    (SERVER_ROUTINE)OnVisualizerEnableChanged,
    (SERVER_ROUTINE)OnVisualizerRefreshRateChanged
    };

static const MIDL_SERVER_INFO RpcInterface_ServerInfo = 
    {
    &RpcInterface_StubDesc,
    RpcInterface_ServerRoutineTable,
    idl__MIDL_ProcFormatString.Format,
    _callbackRpcInterface_FormatStringOffsetTable,
    0,
    0,
    0,
    0};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_) */

