#include "pch.h"
#include "udp.h"
#include <ws2tcpip.h>
#include "stdio.h"
#define SIO_UDP_CONNRESET _WSAIOW(IOC_VENDOR, 12)

#define UDP_PORT_SERVER    4499
#define UDP_BUFFER_SIZE	   1024
#define CMD_SERVER  0x99
#define CMD_CLIENT 0x98

typedef struct DTEN_HEADER
{
	char sign[4]; //"DTEN"
	unsigned char uVer; //默认为0
	unsigned char uStatu;
	unsigned char uActionTag;//0xF0:关机;0xF1-休眠;0xF2-设置音量;0xF3-唤醒;0xF4-升级;0xF5-tracking数据；
	unsigned short uLength;	//后续数据长度
} DTEN_PROCESS_ACTION_HEADER;

DtenUdp* DtenUdp::GetInstance()
{
	static DtenUdp pUdp;
	return &pUdp;
}

void DtenUdp::Run()
{
	m_running = true;
	if (!InitUdpServer())
		return;
	sockaddr_in addr_from;
	int recvlen = 0, err = 0;
	int fromlen = sizeof(sockaddr);
	char recvbuffer[UDP_BUFFER_SIZE] = { 0 };
	while (m_running)
	{
		recvlen = recvfrom(m_SocketServer, recvbuffer, UDP_BUFFER_SIZE, 0, (sockaddr*)&addr_from, &fromlen);
		if (recvlen == SOCKET_ERROR)
		{
			err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK)
			{
				continue;
			}
			else if (err == WSAETIMEDOUT)
			{
				continue;
			}
			else if (err == WSAENETDOWN)
			{
				int num = 0;
			}
			else
			{
				break;
			}
		}
		else if (recvlen <= 0)
		{
			break;
		}

		if (!bDealRecvData(recvbuffer, recvlen, (sockaddr_in*)&addr_from))
		{
			continue;
		}
	}

	vShutDownSocket();
}

bool DtenUdp::InitUdpServer()
{
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		return false;
	}
	m_SocketServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_SocketServer <= 0)
		return false;

	BOOL bInbuffer = FALSE;
	DWORD BytesReturned = 0;
	//WSAIoctl(m_SocketServer, SIO_UDP_CONNRESET, &bInbuffer, sizeof(bInbuffer),
			//NULL, 0, &BytesReturned, NULL, NULL);
	int flag = 1, nTimeOut = 3000;
	setsockopt(m_SocketServer, SOL_SOCKET, SO_REUSEADDR, (char*)&flag, sizeof(flag));
	SOCKADDR_IN addr_Server;
	memset(&addr_Server, 0, sizeof(addr_Server));
	addr_Server.sin_family = AF_INET;
	addr_Server.sin_port = htons(UDP_PORT_SERVER);
	addr_Server.sin_addr.s_addr = htonl(INADDR_ANY);
	setsockopt(m_SocketServer, SOL_SOCKET, SO_RCVTIMEO, (char*)&nTimeOut, sizeof(nTimeOut));

	if (bind(m_SocketServer, (sockaddr*)&addr_Server, sizeof(addr_Server)) == SOCKET_ERROR)
	{
		int err = WSAGetLastError();
		return false;
	}

	return true;
}

bool DtenUdp::bDealRecvData(char* pData, UINT len, SOCKADDR_IN* addr_from)
{
	if (pData == NULL || len < sizeof(DTEN_PROCESS_ACTION_HEADER))
		return false;

	DTEN_PROCESS_ACTION_HEADER* pHeader = (DTEN_PROCESS_ACTION_HEADER*)pData;
	USHORT uHeaderLen = sizeof(DTEN_PROCESS_ACTION_HEADER);
	if (memcmp(pHeader->sign, "DTEN", 4) != 0)
	{
		return false;
	}

	switch (pHeader->uActionTag)
	{
	case CMD_SERVER:
	{
		printf("recive msg from client.\n");
		Sleep(2000);
		SendtoClient();
	}
		break;
	case CMD_CLIENT:
	{
		printf("recive msg from server.\n");
		Sleep(2000);
		SendTOServer();
	}
		break;
	default:
		break;
	}

	return true;
}

void DtenUdp::vShutDownSocket()
{
	if (m_SocketServer != 0)
	{
		shutdown(m_SocketServer, 2);
		closesocket(m_SocketServer);
	}

	m_SocketServer = 0;
}

bool DtenUdp::SendtoClient()
{
	SOCKADDR_IN addr_Client;
	memset(&addr_Client, 0, sizeof(addr_Client));
	addr_Client.sin_family = AF_INET;
	addr_Client.sin_port = htons(UDP_PORT_SERVER);
	inet_pton(AF_INET, "127.0.0.1", (void*)&addr_Client.sin_addr);
	//addr_Server.sin_addr.s_addr = inet_addr("127.0.0.1");

	char szbufferSend[512] = { 0 };
	DTEN_PROCESS_ACTION_HEADER mHeader;
	memcpy(mHeader.sign, "DTEN", 4);
	mHeader.uVer = 0;
	mHeader.uStatu = 1;
	mHeader.uActionTag = CMD_CLIENT;
	mHeader.uLength = 0;
	memcpy(szbufferSend, &mHeader, sizeof(DTEN_PROCESS_ACTION_HEADER));
	int iResult = sendto(m_SocketServer, szbufferSend, sizeof(DTEN_PROCESS_ACTION_HEADER), 0, (SOCKADDR*)&addr_Client, sizeof(SOCKADDR));
	if (iResult == SOCKET_ERROR)
	{
		int err = WSAGetLastError();
	}

	return true;
}

/// ////////////////////////////////////////////////////////////////////////////////////////////
bool DtenUdp::InitUdpClient()
{
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		return false;
	}
	m_SocketClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_SocketClient <= 0)
	{
		WSACleanup();
		return false;
	}

	return true;
}

void DtenUdp::ClientRun()
{
	if (!InitUdpClient())
		return;


	SOCKADDR_IN sockaddrFrom;
	int recvlen = sizeof(sockaddr), err = 0;
	char recvBUffer[UDP_BUFFER_SIZE] = { 0 };
	while (m_running)
	{
		recvfrom(m_SocketClient, recvBUffer, UDP_BUFFER_SIZE, 0, (SOCKADDR*)&sockaddrFrom, &recvlen);
		if (recvlen == SOCKET_ERROR)
		{
			err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK)
			{
				continue;
			}
			else if (err == WSAETIMEDOUT)
			{
				continue;
			}
			else if (err == WSAENETDOWN)
			{
				int num = 0;
			}
			else
			{
				break;
			}
		}
		else if (recvlen <= 0)
		{
			break;
		}

		if (!bDealRecvData(recvBUffer, recvlen, (sockaddr_in*)&sockaddrFrom))
		{
			continue;
		}
	}
	vShutDownSocket();
}

bool DtenUdp::SendTOServer()
{
	if (!InitUdpClient())
		return false;

	SOCKADDR_IN addr_Server;
	memset(&addr_Server, 0, sizeof(addr_Server));
	addr_Server.sin_family = AF_INET;
	addr_Server.sin_port = htons(UDP_PORT_SERVER);
	inet_pton(AF_INET, "127.0.0.1", (void*)&addr_Server.sin_addr);
	//addr_Server.sin_addr.s_addr = inet_addr("127.0.0.1");

	char szbufferSend[512] = { 0 };
	DTEN_PROCESS_ACTION_HEADER mHeader;
	memcpy(mHeader.sign, "DTEN", 4);
	mHeader.uVer = 0;
	mHeader.uStatu = 1;
	mHeader.uActionTag = CMD_SERVER;
	mHeader.uLength = 0;
	memcpy(szbufferSend, &mHeader, sizeof(DTEN_PROCESS_ACTION_HEADER));
	int iResult = sendto(m_SocketClient, szbufferSend, sizeof(DTEN_PROCESS_ACTION_HEADER), 0, (SOCKADDR*)&addr_Server, sizeof(SOCKADDR));
	if (iResult == SOCKET_ERROR)
	{
		int err = WSAGetLastError();
	}

	return true;
}