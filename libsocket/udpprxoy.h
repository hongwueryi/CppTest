#pragma once
#ifndef __C_UDP_OBJECT_H__
#define __C_UDP_OBJECT_H__
#include <Ws2tcpip.h>
#pragma comment(lib ,"ws2_32.lib")
typedef void (*CallbackFun)(void* pData, unsigned int uDataLen);

class CUDPCnt
{
public:
    static CUDPCnt* m_pInstance;
    static CUDPCnt* GetInstance();
    static void DelInstance();

private:
    CUDPCnt();
    ~CUDPCnt();

public:
    bool Init();
    void run(CallbackFun callback);

    bool SendData(unsigned short uPort, void* pData, unsigned int nSendLen, const char* pAddr = "127.0.0.1");

private:
    bool RecvData(void* pBuf, int& nRecvLen);
    bool ParseData(void* pData, unsigned int uDataLen);

private:
    SOCKET m_sck;
};

#endif // !__C_UDP_OBJECT_H__