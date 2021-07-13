

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __idl_h_h__
#define __idl_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

/* header files for imported files */
#include "oaidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __RpcInterface_INTERFACE_DEFINED__
#define __RpcInterface_INTERFACE_DEFINED__

/* interface RpcInterface */
/* [unique][version][uuid] */ 

typedef /* [context_handle] */ void *PCONTEXT_HANDLE_TYPE;

typedef /* [ref] */ PCONTEXT_HANDLE_TYPE *PPCONTEXT_HANDLE_TYPE;

void RemoteOpen( 
    /* [in] */ handle_t hBinding,
    /* [out] */ PPCONTEXT_HANDLE_TYPE pphContext);

void RemoteClose( 
    /* [out][in] */ PPCONTEXT_HANDLE_TYPE pphContext);

void GetVersionNumber( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pV1,
    /* [out] */ long *pV2,
    /* [out] */ long *pV3,
    /* [out] */ long *pV4);

void WaitForEventCallback( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [optional][in] */ __int64 context);

void InitializeDAX( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ BSTR userName,
    /* [out] */ VARIANT_BOOL *__MIDL__RpcInterface0000);

void GetDolbyEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ VARIANT_BOOL *pRetVal);

void SetDolbyEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ VARIANT_BOOL value);

void GetActiveProfile( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal);

void SetActiveProfile( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long pRetVal);

void GetSurroundVirtualizerEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal);

void SetSurroundVirtualizerEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long pRetVal);

void GetDialogEnhancerEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal);

void SetDialogEnhancerEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long pRetVal);

void GetVolumeLevelerEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal);

void SetVolumeLevelerEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long pRetVal);

void GetBassEnhancerEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal);

void SetBassEnhancerEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long pRetVal);

void GetGEQLevels( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ SAFEARRAY * *pRetVal);

void SetGEQLevels( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ SAFEARRAY * pRetVal);

void ResetGEQ( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext);

void GetDeviceMode( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal);

void GetDeviceModeCount( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal);

void GetDeviceModeName( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long index,
    /* [out] */ BSTR *pRetVal);

void GetDeviceModeIcon( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long index,
    /* [out] */ BSTR *pRetVal);

void GetOperatorInfo( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ BSTR *pRetVal);

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
    /* [out] */ short *VolumeMaximizerEnabled);

void GetGEQMaximumRange( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal);

void GetAPIStatus( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal);

void GetEndpointCount( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal);

void GetEndpointData( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long nIndex,
    /* [out] */ BSTR *friendlyName,
    /* [out] */ unsigned long *formFactor,
    /* [out] */ VARIANT_BOOL *offloaded,
    /* [out] */ VARIANT_BOOL *defaultDevice);

void GetPeripheralCount( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal);

void GetPeripheralData( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long index,
    /* [out] */ BSTR *brand,
    /* [out] */ BSTR *model,
    /* [out] */ SAFEARRAY * *deviceBitmap);

void SelectPeripheral( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long endpointIndex,
    /* [in] */ long periferalIndex);

void GetSelectedPeripheral( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long endpointIndex,
    /* [out] */ long *pRetVal);

void IsSpatialAudioSupported( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ VARIANT_BOOL *pRetVal);

void GetSpatialAudioStatus( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal);

/* [callback] */ void OnDolbyEnableChanged( 
    /* [in] */ VARIANT_BOOL newValue,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnActiveProfileChanged( 
    /* [in] */ long newValue,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnSurroundVirtualizerEnableChanged( 
    /* [in] */ long newValue,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnDialogEnhancerEnableChanged( 
    /* [in] */ long newValue,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnVolumeLevelerEnableChanged( 
    /* [in] */ long newValue,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnBassEnhancerEnableChanged( 
    /* [in] */ long newValue,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnGEQLevelsChanged( 
    /* [in] */ SAFEARRAY * newValue,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnDefaultEndpointChanged( 
    /* [in] */ long newValue,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnDeviceModeChanged( 
    /* [in] */ long newValue,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnAPIStatusChanged( 
    /* [in] */ long newValue,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnSpatialAudioStatusChanged( 
    /* [in] */ long newValue,
    /* [optional][in] */ __int64 context);

void GetDefaultUITheme( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ BSTR *pRetVal);

void GetSKU( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ BSTR *pRetVal);

void GetActiveSubProfile( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal);

void SetActiveSubProfile( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long pRetVal);

void GetSubProfileDirty( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ VARIANT_BOOL *pRetVal);

void ResetSubProfile( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext);

void GetIEQ( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ long *pRetVal);

void SetIEQ( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long pRetVal);

void ResetIEQ( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext);

void GetSurroundVirtualizerValue( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ float *pRetVal);

void SetSurroundVirtualizerValue( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ float pRetVal);

void GetDialogEnhancerValue( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ float *pRetVal);

void SetDialogEnhancerValue( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ float pRetVal);

void GetVolumeLevelerValue( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ float *pRetVal);

void SetVolumeLevelerValue( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ float pRetVal);

void GetRadarEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ VARIANT_BOOL *pRetVal);

void SetRadarEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ VARIANT_BOOL pRetVal);

void GetVisualizerEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ VARIANT_BOOL *pRetVal);

void SetVisualizerEnable( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ VARIANT_BOOL pRetVal);

void GetHotkey( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long index,
    /* [out] */ BSTR *pRetVal);

void SetHotkey( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ long index,
    /* [in] */ BSTR hotkey,
    /* [out] */ long *pRetVal);

void GetRadarSize( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ float *pRetVal);

void SetRadarSize( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ float pRetVal);

void GetRadarTransparency( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ float *pRetVal);

void SetRadarTransparency( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ float pRetVal);

void GetRadarSkin( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ unsigned long *pRetVal);

void SetRadarSkin( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ unsigned long pRetVal);

void GetRadarMaxDirection( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ unsigned long *pRetVal);

void SetRadarMaxDirection( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ unsigned long pRetVal);

void GetRadarPosition( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ float *x,
    /* [out] */ float *y);

void SetRadarPosition( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ float x,
    /* [in] */ float y);

void SetRadarRefreshRate( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ unsigned long pRetVal);

void GetRadarRefreshRate( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ unsigned long *pRetVal);

void GetSoundMap( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ SAFEARRAY * *sectEdges,
    /* [out] */ SAFEARRAY * *strengths);

void SetVisualizerRefreshRate( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [in] */ unsigned long pRetVal);

void GetVisualizerRefreshRate( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ unsigned long *pRetVal);

void GetVisualizerData( 
    /* [in] */ PCONTEXT_HANDLE_TYPE phContext,
    /* [out] */ SAFEARRAY * *pRetVal);

/* [callback] */ void OnActiveSubProfileChanged( 
    /* [in] */ long newValue,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnSubProfileReset( 
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnIEQChanged( 
    /* [in] */ long newValue,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnSurroundVirtualizerValueChanged( 
    /* [in] */ float newValue,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnDialogEnhancerValueChanged( 
    /* [in] */ float newValue,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnVolumeLevelerValueChanged( 
    /* [in] */ float newValue,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnRadarEnableChanged( 
    /* [in] */ VARIANT_BOOL newValue,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnSubProfileDirtyChanged( 
    /* [in] */ VARIANT_BOOL newValue,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnHotkeyChanged( 
    /* [in] */ long newValue,
    /* [in] */ BSTR hotkey,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnRadarSizeChanged( 
    /* [in] */ float newValue,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnRadarTransparencyChanged( 
    /* [in] */ float newValue,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnRadarPositionChanged( 
    /* [in] */ float x,
    /* [in] */ float y,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnRadarSkinChanged( 
    /* [in] */ unsigned long newValue,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnRadarMaxDirectionChanged( 
    /* [in] */ unsigned long newValue,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnVisualizerEnableChanged( 
    /* [in] */ VARIANT_BOOL newValue,
    /* [optional][in] */ __int64 context);

/* [callback] */ void OnVisualizerRefreshRateChanged( 
    /* [in] */ unsigned long newValue,
    /* [optional][in] */ __int64 context);



extern RPC_IF_HANDLE RpcInterface_v1_0_c_ifspec;
extern RPC_IF_HANDLE RpcInterface_v1_0_s_ifspec;
#endif /* __RpcInterface_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

void __RPC_USER PCONTEXT_HANDLE_TYPE_rundown( PCONTEXT_HANDLE_TYPE );

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


