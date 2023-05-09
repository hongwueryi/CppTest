#pragma once
//netsh wlan show profile //可以查看所有连接过的wifi
//netsh wlan export profile key = clear //导出所有连接过的wifi信息
int Wlan_GetAvailableNetworkList();
int wlanscan();
void test_wifi();
bool connectwlan();
