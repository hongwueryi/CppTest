#include <stdlib.h>
#include "udp.h"
#include <thread>

void Socket_udp_test()
{
	std::thread tUdp_s([] {
		DtenUdp::GetInstance()->Run();
		});

	std::thread tUdp_c([] {
		DtenUdp::GetInstance()->SendTOServer();
		});
	tUdp_c.detach();
	tUdp_s.detach();
}

BOOL CALLBACK DeskEnum(LPWSTR desk, LPARAM lParam)
{
	int bun = 0;
	return TRUE;
}

BOOL CALLBACK WorkStationEnum(LPTSTR lpszWindowStation, _In_ LPARAM lParam)
{
	return TRUE;
}

int main()
{
	//EnumWindowStations(WorkStationEnum, 0);
	//EnumDesktops(NULL, DeskEnum, 0);
	//Socket_udp_test();
	system("pause");
	return 0;
}