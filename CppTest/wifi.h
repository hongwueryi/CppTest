#pragma once
//netsh wlan show profile //���Բ鿴�������ӹ���wifi
//netsh wlan export profile key = clear //�����������ӹ���wifi��Ϣ
int Wlan_GetAvailableNetworkList();
int wlanscan();
void test_wifi();
bool connectwlan();
