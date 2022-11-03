#include "pch.h"
#include <string>
#include "tcpprxoy.h"
#include <iostream>
#include <thread>

#define MESSAGE_LEN 1024
#define DTEN_MY_PORT   56333
#define SIO_UDP_CONNRESET _WSAIOW(IOC_VENDOR, 12)

int backlog = 2;   // 监听队列中允许保持的尚未处理的最大连接数量

CTCPCnt* CTCPCnt::m_pInstance = NULL;
CTCPCnt* CTCPCnt::GetInstance()
{
    if (NULL == m_pInstance)
    {
        m_pInstance = new CTCPCnt;
    }

    return m_pInstance;
}

void CTCPCnt::DelInstance()
{
    if (NULL == m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = NULL;
    }
}

CTCPCnt::CTCPCnt()
{
    m_sck = INVALID_SOCKET;
    //InitServer(true);
}

CTCPCnt::~CTCPCnt()
{
    WSACleanup();
}

bool CTCPCnt::InitServer(bool nServer)
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
    sockaddr_in LocalAddr;//服务器地址
    m_sck = socket(AF_INET, SOCK_STREAM, 0);
    //设置服务器地址
    LocalAddr.sin_family = AF_INET;
    LocalAddr.sin_port = htons(DTEN_MY_PORT);
    LocalAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int re_len = sizeof(int);
    int re_flag = 1;
    setsockopt(m_sck, SOL_SOCKET, SO_REUSEADDR, (const char*)(&re_flag), re_len);

    int iRet = ::bind(m_sck, (SOCKADDR*)&LocalAddr, sizeof(LocalAddr));

    if (0 != iRet)
    {
        //WriteLogE("udp server bind %d failed! error code is: %d", DTEN_SERVICE_PORT, WSAGetLastError());
        return false;
    }

    iRet = listen(m_sck, backlog);
    if (iRet == SOCKET_ERROR) {
        std::cout << "failed to listen addr" << std::endl;
        return false;

    }
    
    return true;
}

void CTCPCnt::run(CallbackFun callback)
{
    SOCKET AcceptSocket;
    struct sockaddr_in remoteaddr;
    while (backlog > 0)
    {       
        socklen_t  addr_len = sizeof(struct sockaddr);
        AcceptSocket = accept(m_sck, (struct sockaddr*)&remoteaddr, &addr_len);
        if (AcceptSocket != SOCKET_ERROR)
        {
            backlog--;
            std::thread tRecv([](SOCKET AcceptSocket) {
                while (true)
                {
                    char in_buff[MESSAGE_LEN] = { 0 };
                    int iRet = recv(AcceptSocket, in_buff, MESSAGE_LEN, 0);
                    if (iRet == 0) {
                        std::cout << "quit" << std::endl;
                        break;
                    }
                    else if (iRet > 0) {
                        std::cout << "recv: " << in_buff << std::endl;
                        /*if (strcmp(in_buff, "11") == 0)
                        {
                            CTCPCnt::GetInstance()->SendData(56334, (void*)"123", 3);
                        }*/
                    }
                }
                }, AcceptSocket);
            tRecv.detach();
        }
    }
}

bool CTCPCnt::SendData(unsigned short uPort, void* pData, unsigned int nSendLen, const char* pAddr, int nTryTimes)
{
    //----------------------
    // Declare and initialize variables.
    int iResult;
    WSADATA wsaData;

    SOCKET ConnectSocket = INVALID_SOCKET;
    struct sockaddr_in clientService;
    //const char* sendbuf = "Client: sending data test";

    //----------------------
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    //----------------------
    // Create a SOCKET for connecting to server
    ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET) {
        wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    //----------------------
    // The sockaddr_in structure specifies the address family,
    // IP address, and port of the server to be connected to.
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientService.sin_port = htons(DTEN_MY_PORT);

    //----------------------
    // Connect to server.
    iResult = connect(ConnectSocket, (SOCKADDR*)&clientService, sizeof(clientService));
    if (iResult == SOCKET_ERROR) {
        wprintf(L"connect failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    //----------------------
    // Send an initial buffer
    iResult = send(ConnectSocket, (const char*)pData, nSendLen, 0);
    if (iResult == SOCKET_ERROR) {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("Bytes Sent: %d\n", iResult);

    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        wprintf(L"shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // Receive until the peer closes the connection
    /*do {

        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0)
            wprintf(L"Bytes received: %d\n", iResult);
        else if (iResult == 0)
            wprintf(L"Connection closed\n");
        else
            wprintf(L"recv failed with error: %d\n", WSAGetLastError());

    } while (iResult > 0);*/


    // close the socket
    iResult = closesocket(ConnectSocket);
    if (iResult == SOCKET_ERROR) {
        wprintf(L"close failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    WSACleanup();
    return 0;
}

/*
int main()
{
    CTCPCnt::GetInstance()->run(callback_parse_udp_data);
}
*/