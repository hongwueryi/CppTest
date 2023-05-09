#pragma once
class CMonitorTP
{
public:
    static CMonitorTP* GetInstance();

public:
    bool AssociateTPwithMonitor();

private:
    bool GetAllTouchInfo(std::map<int, std::wstring>& TouchMap);
    int SetDrvStatusByName(std::wstring strDesName, bool bSetAll);

private:
    CMonitorTP() {};
    CMonitorTP(const CMonitorTP& other) = delete;
    CMonitorTP& operator=(const CMonitorTP& other) = delete;
};
