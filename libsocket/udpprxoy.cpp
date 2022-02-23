#include "pch.h"
#include <string>
#include "udpprxoy.h"
#define DTEN_SERVICE_PORT   56231
#define SIO_UDP_CONNRESET _WSAIOW(IOC_VENDOR, 12)

CUDPCnt* CUDPCnt::m_pInstance = NULL;
CUDPCnt* CUDPCnt::GetInstance()
{
    if (NULL == m_pInstance)
    {
        m_pInstance = new CUDPCnt;
    }

    return m_pInstance;
}

void CUDPCnt::DelInstance()
{
    if (NULL == m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = NULL;
    }
}

CUDPCnt::CUDPCnt()
{
    m_sck = INVALID_SOCKET;
    Init();
}

CUDPCnt::~CUDPCnt()
{
    WSACleanup();
}

bool CUDPCnt::Init()
{
    WORD wVersionRequested;//用于保存WinSock库的版本号
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);

    if (err != 0)
    {
        //WriteLogE("WSAStartup() called failed!");
        return false;
    }

    if (LOBYTE(wsaData.wVersion) != 2 ||
        HIBYTE(wsaData.wVersion) != 2)
    {
        //若不是所请求的版本号2.2，则终止WinSock库的使用
        WSACleanup();
        return false;
    }

    //创建Socket对象
    sockaddr_in RecvAddr;//服务器地址
    m_sck = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    //设置服务器地址
    RecvAddr.sin_family = AF_INET;
    RecvAddr.sin_port = htons(DTEN_SERVICE_PORT);
    RecvAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    BOOL bNewBehavior = FALSE;
    DWORD dwBytesReturned = 0;

    WSAIoctl(m_sck, SIO_UDP_CONNRESET, &bNewBehavior, sizeof bNewBehavior, NULL, 0, &dwBytesReturned, NULL, NULL);
    int re_len = sizeof(int);
    int re_flag = 1;
    setsockopt(m_sck, SOL_SOCKET, SO_REUSEADDR, (const char*)(&re_flag), re_len);

    int bRet = ::bind(m_sck, (SOCKADDR*)&RecvAddr, sizeof(RecvAddr));

    if (0 != bRet)
    {
        //WriteLogE("udp server bind %d failed! error code is: %d", DTEN_SERVICE_PORT, WSAGetLastError());
        return false;
    }

    return true;
}


void CUDPCnt::run(CallbackFun callback)
{
    while (true)
    {
        bool bRet = false;
        char strTemp[1024] = { 0 };
        int nRecvLen = 1024;
        bRet = RecvData(strTemp, nRecvLen);

        if (true == bRet)
        {
            //ParseData(strTemp, nRecvLen);
            callback(strTemp, nRecvLen);
        }
    }
}

bool CUDPCnt::SendData(unsigned short uPort, void* pData, unsigned int nSendLen, const char* pAddr)
{
    bool bRet = true;
    sockaddr_in SvrAddr;
    SvrAddr.sin_family = AF_INET;
    SvrAddr.sin_port = htons(uPort);
    SvrAddr.sin_addr.s_addr = inet_addr(pAddr);

    int nTryTimes = 3;
    int nRet = 0;
    int nCount = 0;

    while (nCount++ < nTryTimes)
    {
        nRet = sendto(m_sck, (const char*)pData, nSendLen, 0, (SOCKADDR*)&SvrAddr, sizeof(SvrAddr));

        if (SOCKET_ERROR == nRet)
        {
            bRet = false;
            //WriteLogE("sendto error, code is %d, try %d", WSAGetLastError(), nCount);
            continue;
        }
        else
        {
            break;
        }
    }

    return bRet;
}

bool CUDPCnt::RecvData(void* pBuf, int& nRecvLen) //block recv
{
    sockaddr_in SenderAddr;
    int SenderAddrSize = sizeof(SenderAddr);
    int nRet = ::recvfrom(m_sck, (char*)(pBuf), nRecvLen, 0, (SOCKADDR*)&SenderAddr, &SenderAddrSize);

    if (SOCKET_ERROR == nRet)
    {
        //WriteLogE("recvfrom error, code is %d", WSAGetLastError());
        return false;
    }

    nRecvLen = nRet;
    //WriteLogD("recv data Len is %d.", nRet);
    return true;
}

bool CUDPCnt::ParseData(void* pData, unsigned int uDataLen)
{
    if (0 == pData)
    {
        return false;
    }
#if 0
    char* szBuffer = (char*)pData;
    char recevie_event[2] = { 0 };
    recevie_event[0] = szBuffer[0];
    recevie_event[1] = '\0';
    //WriteLogD("Server Receive : %s", szBuffer);
    int category = atoi(recevie_event);

    switch (category)
    {
    case MIC:
        check_mic(szBuffer[2]);
        break;
    case HDMI:
        check_hdmi(szBuffer[2]);
        break;
    case CAM:
        check_cam(szBuffer[2]);
        break;
    case MONITOR:
        check_monitor(szBuffer[2]);
        break;
    case WIFI:
    case FIRMWARE_VERSION:
    case FIRMWARE_STATUS:
        SavetoPo(static_cast<char*>(&szBuffer[2]), false);
        break;
    case LOG:
    case LOCATION:
        SavetoPo(static_cast<char*>(&szBuffer[2]), true);
        break;
    default:
        break;
    }
#endif
}