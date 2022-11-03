#ifndef __C_TCP_OBJECT_H__
#define __C_TCP_OBJECT_H__
#include <Ws2tcpip.h>
#pragma comment(lib ,"ws2_32.lib")
typedef void (*CallbackFun)(void* pData, unsigned int uDataLen);

class CTCPCnt
{
public:
    static CTCPCnt* m_pInstance;
    static CTCPCnt* GetInstance();
    static void DelInstance();

private:
    CTCPCnt();
    ~CTCPCnt();

public:
    bool InitServer(bool nServer);
    void run(CallbackFun callback);

    bool SendData(unsigned short uPort, void* pData, unsigned int nSendLen, const char* pAddr = "127.0.0.1", int nTryTimes = 3);

private:
    SOCKET m_sck;
};

#endif // !__C_UDP_OBJECT_H__#pragma once
