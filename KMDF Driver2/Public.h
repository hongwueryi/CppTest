/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/

//
// Define an Interface Guid so that apps can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_KMDFDriver2,
    0x034d6770,0x3383,0x44ee,0xa5,0x2d,0xfc,0xa1,0x2b,0x39,0xe9,0x82);
// {034d6770-3383-44ee-a52d-fca12b39e982}
