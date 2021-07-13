#pragma once
#ifdef EXPORTFLAG
    #ifdef __cplusplus
        #define EXPORTFUNC  extern "C" __declspec(dllexport)
    #else
        #define EXPORTFUNC __declspec(dllexport)
    #endif
#else
    #ifdef __cplusplus
        #define EXPORTFUNC  extern "C" __declspec(dllimport)
    #else
        #define EXPORTFUNC __declspec(dllimport)
    #endif
#endif

EXPORTFUNC void EnableHook();