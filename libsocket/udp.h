#pragma once
#include <WinSock2.h>
class DtenUdp
{
public:
	static DtenUdp* GetInstance();

public:
	bool InitUdpServer();
	void Run();
	bool bDealRecvData(char* pData, UINT len, SOCKADDR_IN* addr_from);
	void vShutDownSocket();
	bool SendtoClient();

public:
	bool InitUdpClient();
	bool SendTOServer();
	void ClientRun();

private:
	DtenUdp() {}
	~DtenUdp(){}

private:
	SOCKET m_SocketServer;
	SOCKET m_SocketClient;
	bool m_running;
};
