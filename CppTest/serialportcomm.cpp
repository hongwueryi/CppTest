#include <Windows.h>
#include <vector>
#include "SerialPort/EnumSerial.h"
#include "SerialPort/SerialPort.h"
#include "stdio.h"
#include <tchar.h>
#include <string>

using namespace std;

#define DEV_DESC_LEN 512
#define ALS_DEVDESC L"USB-SERIAL CH341A"
#define MAX_SERIALPORT_RW_CATCH_SIZE		1024

#define ALS_WRITE 0
#define ALS_READ 1

#define Enable_ALS 0x01

UINT8 ALS_I2C_ADR = 0x38;
#define REG_SYSM_CTRL  0x00
#define REG_Product_ID_L 0xBC
#define REG_Product_ID_H 0xBD

CSerial cs;
UINT I2CgetRegData(uint8_t Dev_Address, uint8_t reg)
{
#if 0
    Wire.beginTransmission(Dev_Address);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(Dev_Address, 1);

    if (Wire.available() <= 1) {
        return Wire.read();
    }
#endif

    uint8_t txBuffer[32] = { 0 };
    uint8_t twi_slaw = 0;
    twi_slaw = (uint8_t)ALS_WRITE;
    twi_slaw |= (uint8_t)ALS_I2C_ADR << 1;
    txBuffer[0] = twi_slaw;
    txBuffer[1] = reg;
    uint8_t twi_slar = 0;
    twi_slar = (uint8_t)ALS_READ;
    twi_slar |= (uint8_t)ALS_I2C_ADR << 1;
    txBuffer[2] = twi_slar;

    UINT uData = (txBuffer[0] << 16) | (txBuffer[1] << 8) | txBuffer[2];
    DWORD dWrite = 0;
    LONG lRet = cs.Write(&uData, 4, &dWrite);
    Sleep(100);
    UINT uReadData = 0;
    DWORD dRead = 0;
    lRet = cs.Read(&uReadData, 4, &dRead);
    return uReadData;
}

LONG I2CsetReg(uint8_t Dev_Address, uint8_t reg, uint8_t data)
{
    uint8_t txBuffer[32] = { 0 };
    uint8_t twi_slaw = 0;
    twi_slaw = (uint8_t)ALS_WRITE;
    twi_slaw |= (uint8_t)Dev_Address << 1;
    txBuffer[0] = twi_slaw;
    txBuffer[1] = reg;
    txBuffer[2] = data;
    UINT uData = (txBuffer[0] << 16) | (txBuffer[1] << 8) | txBuffer[2];
    DWORD dWrite = 0;
    LONG lRet = cs.Write(&uData, 4, &dWrite);
    Sleep(100);
    return lRet;
}

void I2CwriteByteMask(UINT16 Dev_Address, UINT16 u16Reg, UINT8 u8Value, UINT8 u8Mask)
{
    I2CsetReg(Dev_Address, u16Reg, ((I2CgetRegData(Dev_Address, u16Reg) & (~u8Mask)) | (u8Value & u8Mask)));
}

#if 1
void Get_Product_No(void)
{
    UINT16 DevId_L = I2CgetRegData(ALS_I2C_ADR, REG_Product_ID_L);
    UINT16 DevId_H = I2CgetRegData(ALS_I2C_ADR, REG_Product_ID_H);
    UINT16 DevId = (DevId_H << 8) | DevId_L;

    if (DevId != 0x1614)
        printf("DevID error\n");
    else
    {
        printf("DevID=0x%x\n", DevId);
    }
}
#endif

int main()
{
    //wstring ALSPortName = L"USB - SERIAL CH340(COM3)";
    wstring ALSPortName = L"";
    std::vector<SSerInfo> m_vecSerialPortInfo;
    if (!EnumSerialPorts(m_vecSerialPortInfo, FALSE))
    {
        printf("Error EnumSerialPorts\n");
        system("pause");
        return 0;
    }
    for (std::vector<SSerInfo>::iterator iter = m_vecSerialPortInfo.begin(); iter != m_vecSerialPortInfo.end(); iter++)
    {
        std::wstring strFriName = iter->stFriendlyName;
        if (strFriName.find(ALS_DEVDESC) != std::string::npos)
        {
            ALSPortName = iter->stPortName;
            wprintf(L"ALSPortName:%s\n", ALSPortName.c_str());
            break;
        }  
    }

    LONG lRet = cs.Open(ALSPortName.c_str(), MAX_SERIALPORT_RW_CATCH_SIZE, MAX_SERIALPORT_RW_CATCH_SIZE, true);
    if (lRet != ERROR_SUCCESS)
    {
        printf("open ALS comport failed, err=%d\n", GetLastError());
        system("pause");
        return 0;
    }
    else
    {
        printf("open ALS comport ok\n");
    }

#if 0
    if (cs.IsOpen())
    {
        printf("ALS PORT is open\n");
        printf("close=%d\n", cs.Close());
    }
    if (cs.IsOpen())
    {
        printf("close ALS PORT failed\n");
    }
#endif
#if 0
    lRet = cs.Setup(CSerial::EBaud115200, CSerial::EData8, CSerial::EParNone, CSerial::EStop1);
    if (lRet != ERROR_SUCCESS)
    {
        printf("setup ALS comport failed, err=%d\n", GetLastError());
        return 0;
    }
    
    //Get_Product_No();
    I2CwriteByteMask(ALS_I2C_ADR, REG_SYSM_CTRL, 0x01, Enable_ALS);
#endif
exit:
    cs.Close();
    system("pause");
    return 0;
}