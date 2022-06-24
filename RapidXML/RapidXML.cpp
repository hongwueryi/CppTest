// RapidXML.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "xmlmanager.h"
using namespace std;

string UnicodeToAscii(const wstring& wstr)
{
    int ansiiLen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    char* pAssii = (char*)malloc(sizeof(char) * ansiiLen);
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
    string ret_str = pAssii;
    free(pAssii);
    return ret_str;
}

bool isMatchdVidPidFromPlugEvent(const char* NodePName, const char* NodeCName,
    wstring sourceData, vector<wstring>& v_vidpid_regex)
{
    if (v_vidpid_regex.empty())
        CXmlManager::GetInstance().GetNodeValue(NodePName, NodeCName, v_vidpid_regex);
    vector<wstring>::iterator it;
    for (it = v_vidpid_regex.begin(); it != v_vidpid_regex.end(); ++it)
    {
        wstring strTemp = *it;
        if (strTemp.empty())
            continue;
        wsmatch  matchResult;
        wregex PATTERN_REGEX_EV(*it);
        if (regex_match(sourceData, matchResult, PATTERN_REGEX_EV))
            return true;
    }

    return false;
}

bool GetVidPidInfoFromXML(const char* nodeRoot, const char* nodeType,
    const char* nodeName, vector<wstring>& vecNode)
{
    if (vecNode.empty())
    {
        CXmlManager::GetInstance().GetNodeValue(nodeRoot, nodeType, nodeName, vecNode);
    }

    if (vecNode.empty())
    {
        return false;
    }

    return true;
}

bool GetVidPidInfoFromXML(const char* nodeRoot, const char* nodeType, const char* nodeName, wchar_t** psMicIdRegex, int& nMicArrNum, vector<wstring>&vecNode)
{
    if (nullptr == psMicIdRegex)
    {
        return false;
    }
    if (vecNode.empty())
    {
        CXmlManager::GetInstance().GetNodeValue(nodeRoot, nodeType, nodeName, vecNode);
    }

    nMicArrNum = vecNode.size() + 1;
    for (int i = 1; i < nMicArrNum; i++)
    {

        wstring wstemp = vecNode[i - 1];
        int tempLen = wstemp.length() + 1;
        psMicIdRegex[i] = new wchar_t[tempLen + 1];
        memset(psMicIdRegex[i], 0, tempLen + 1);
        wcscpy_s(psMicIdRegex[i], tempLen, wstemp.c_str());
    }
    
    return true;
}

bool GetMicHardIDAndInfFile(std::string strMicVidPid, const char* deviceType, std::vector<wstring>& allvidpid, NODE_ATTRIBUTE_DEVICE& NodeInfo)
{
    if (!NodeInfo.hardid.empty() && !NodeInfo.inffile.empty())
    {
        return true;
    }
    if (allvidpid.empty())
    {
        CXmlManager::GetInstance().GetNodeValue("SETUPDRIVERS", "MIC", deviceType, "ALLVIDPID", allvidpid);
    }
    if (allvidpid.empty())
    {
        return false;
    }

    std::vector<wstring>::iterator itMic;
    for (itMic = allvidpid.begin(); itMic != allvidpid.end(); ++itMic)
    {
        string temp = UnicodeToAscii(*itMic);
        if (strMicVidPid.find(temp) != std::string::npos)
        {
            NODE_ATTRIBUTE_DEVICE Info;
            CXmlManager::GetInstance().GetNodeAttribute("SETUPDRIVERS", "MIC", deviceType, temp.c_str(), Info);
            NodeInfo = Info;
            return true;
        }
    }

    return false;
}

bool GetCamHardIDAndInfFile(std::string strMicVidPid, const char* deviceType, std::vector<wstring>& allvidpid, NODE_ATTRIBUTE_DEVICE& NodeInfo)
{
    if (!NodeInfo.hardid.empty() && !NodeInfo.inffile.empty())
    {
        return true;
    }
    if (allvidpid.empty())
    {
        CXmlManager::GetInstance().GetNodeValue("SETUPDRIVERS", "CAM", deviceType, "ALLVIDPID", allvidpid);
    }
    if (allvidpid.empty())
    {
        return false;
    }

    std::vector<wstring>::iterator itMic;
    for (itMic = allvidpid.begin(); itMic != allvidpid.end(); ++itMic)
    {
        string temp = UnicodeToAscii(*itMic);
        if (strMicVidPid.find(temp) != std::string::npos)
        {
            NODE_ATTRIBUTE_DEVICE Info;
            CXmlManager::GetInstance().GetNodeAttribute("SETUPDRIVERS", "CAM", deviceType, temp.c_str(), Info);
            NodeInfo = Info;
            return true;
        }
    }

    return false;
}

bool GetTPHardIDAndInfFile(std::string strTPVidPid, const char* deviceType, std::vector<wstring>& allvidpid, NODE_ATTRIBUTE_DEVICE& NodeInfo)
{
    if (!NodeInfo.hardid.empty() && !NodeInfo.inffile.empty())
    {
       return true;
    }
    if (allvidpid.empty())
    {
        CXmlManager::GetInstance().GetNodeValue("SETUPDRIVERS", "TOUCH", deviceType, "ALLVIDPID", allvidpid);
    }
    if (allvidpid.empty())
    {
        return false;
    }

    std::vector<wstring>::iterator itMic;
    for (itMic = allvidpid.begin(); itMic != allvidpid.end(); ++itMic)
    {
        string temp = UnicodeToAscii(*itMic);
        if (strTPVidPid.find(temp) != std::string::npos)
        {
            NODE_ATTRIBUTE_DEVICE Info;
            CXmlManager::GetInstance().GetNodeAttribute("SETUPDRIVERS", "TOUCH", deviceType, temp.c_str(), Info);
            NodeInfo = Info;
            return true;
        }
    }

    return false;
}

void Get_Node_MIC_55()
{
    std::string strMicPID = "usb\VID_4255&PID_0007#{rev";
    static std::vector<wstring> allvidpid_75;
    static NODE_ATTRIBUTE_DEVICE NodeInfo1;
    if (!GetMicHardIDAndInfFile(strMicPID, "MIC_75", allvidpid_75, NodeInfo1))
    {
        return;
    }

    strMicPID = "VID_4255&PID_1001#{rev";
    static std::vector<wstring> allvidpid_55;
    static NODE_ATTRIBUTE_DEVICE NodeInfo;
    if (!GetMicHardIDAndInfFile(strMicPID, "MIC_55", allvidpid_55, NodeInfo))
    {
        return;
    }
    return;
}

void GetTPHardidandInf()
{
    std::string strMicPID = "USB\\VID_222A&PID_0001&REV_70.*";
    static std::vector<wstring> allvidpid;
    static NODE_ATTRIBUTE_DEVICE NodeInfo1;
    if (!GetTPHardIDAndInfFile(strMicPID, "TOUCH_75", allvidpid, NodeInfo1))
    {
        return;
    }
}

void GetCamHardidandInf()
{
    std::string strMicPID = "USB\\VID_1D6B&PID_0100&REV_.*";
    static std::vector<wstring> allvidpid;
    static NODE_ATTRIBUTE_DEVICE NodeInfo1;
    if (!GetCamHardIDAndInfFile(strMicPID, "D7", allvidpid, NodeInfo1))
    {
        return;
    }
}

void SetUpTouchDevconByForce()
{
    static std::vector<NODE_ATTRIBUTE_DEVICE> allTPinf;
    if (allTPinf.empty())
    {
        CXmlManager::GetInstance().GetNodeAttribute("SETUPDRIVERS", "TOUCH", "SETUPALL", allTPinf);
    }
    if (allTPinf.empty())
    {
        return;
    }
    std::vector<NODE_ATTRIBUTE_DEVICE>::iterator it;
    for (it = allTPinf.begin(); it != allTPinf.end(); ++it)
    {
        string strinf = UnicodeToAscii(it->inffile);
        string strhardid = UnicodeToAscii(it->hardid);
    }
}

void SetUpCamByDevconByForce()
{
    static std::vector<NODE_ATTRIBUTE_DEVICE> allCaminf;
    if (allCaminf.empty())
    {
        CXmlManager::GetInstance().GetNodeAttribute("SETUPDRIVERS", "CAM", "D7", "SETUPALL", allCaminf);
    }
    if (allCaminf.empty())
    {
        return;
    }
    std::vector<NODE_ATTRIBUTE_DEVICE>::iterator it;
    for (it = allCaminf.begin(); it != allCaminf.end(); ++it)
    {
        string strinf = UnicodeToAscii(it->inffile);
        string strhardid = UnicodeToAscii(it->hardid);
    }
}

bool GetBuzzerHardIDAndInfFile(std::string strVidPid, std::vector<wstring>& allvidpid, NODE_ATTRIBUTE_DEVICE& NodeInfo)
{
    if (!NodeInfo.hardid.empty() && !NodeInfo.inffile.empty())
    {
        return true;
    }
    if (allvidpid.empty())
    {
        CXmlManager::GetInstance().GetNodeValue("SETUPDRIVERS", "BUZZER", "ALLVIDPID", allvidpid);
    }
    if (allvidpid.empty())
    {
        return false;
    }

    std::vector<wstring>::iterator itMic;
    for (itMic = allvidpid.begin(); itMic != allvidpid.end(); ++itMic)
    {
        string temp = UnicodeToAscii(*itMic);
        if (strVidPid.find(temp) != std::string::npos)
        {
            NODE_ATTRIBUTE_DEVICE Info;
            CXmlManager::GetInstance().GetNodeAttribute("SETUPDRIVERS", "BUZZER", temp.c_str(), Info);
            NodeInfo = Info;
            return true;
        }
    }

    return false;
}

void GetBuzzerHardidandInf()
{
    std::string strMicPID = "USB\VID_10C4&PID_EA60&REV_0100";
    static std::vector<wstring> allvidpid;
    static NODE_ATTRIBUTE_DEVICE NodeInfo1;
    if (!GetBuzzerHardIDAndInfFile(strMicPID, allvidpid, NodeInfo1))
    {
        return;
    }
}
int GetTouchVer(char* szBuf, int nBufLen)
{
    char szVer[128] = { 0 };
    bool bRet = false;
    string strHardId = "";
   
    static vector<wstring> vecTouchNode1;
    vector<wstring>::iterator it;
    if (!GetVidPidInfoFromXML("CHECKDEVICE", "TOUCH", "TOUCH_NODE_1", vecTouchNode1))
    {
        
        return 0;
    }

    for (it = vecTouchNode1.begin(); it != vecTouchNode1.end(); ++it)
    {
        std::wstring strRegex = *it;
        int num = 0;
    }

    return sprintf_s(szBuf, nBufLen, "%s", szVer);
}
#define CONFIG_INIFILE_NAME_A				"C:\\DTEN\\version\\version.ini"
int compareVersion(char* v1, char* v2) {
    int res = 0;
    //char* v1 = (char*)version1.c_str(), * v2 = (char*)version2.c_str();
    while (res == 0 && (*v1 != '\0' || *v2 != '\0')) {
        long d1 = *v1 == '\0' ? 0 : strtol(v1, &v1, 10);
        long d2 = *v2 == '\0' ? 0 : strtol(v2, &v2, 10);
        if (d1 > d2) return 1;
        else if (d1 < d2) return -1;
        else {
            if (*v1 != '\0') ++v1;
            if (*v2 != '\0') ++v2;
        }
    }
    return res;
}


bool GetSubCamHardIDAndInfFile(std::string strVidPid, const char* subcamType, const char* deviceType,
    std::vector<wstring>& allvidpid, NODE_ATTRIBUTE_DEVICE& NodeInfo)
{
    if (!NodeInfo.hardid.empty() && !NodeInfo.inffile.empty())
    {
                return true;
    }
    if (allvidpid.empty())
    {
        CXmlManager::GetInstance().GetNodeValue("SETUPDRIVERS", subcamType, deviceType, "ALLVIDPID", allvidpid);
    }
    if (allvidpid.empty())
    {
        
        return false;
    }

    std::vector<wstring>::iterator it;
    for (it = allvidpid.begin(); it != allvidpid.end(); ++it)
    {
        string temp = UnicodeToAscii(*it);
        if (strVidPid.find(temp) != std::string::npos)
        {
            NODE_ATTRIBUTE_DEVICE Info;
            CXmlManager::GetInstance().GetNodeAttribute("SETUPDRIVERS", subcamType, deviceType, temp.c_str(), Info);
            NodeInfo = Info;
            return true;
        }
    }

    return false;
}
void SetUpSubCamByDevconByForce(const char* deviceType)
{
    static std::vector<NODE_ATTRIBUTE_DEVICE> allSubCaminf;
    if (allSubCaminf.empty())
    {
        CXmlManager::GetInstance().GetNodeAttribute("SETUPDRIVERS", "CAM_SUB", deviceType, "SETUPALL", allSubCaminf);
    }
    if (allSubCaminf.empty())
    {
       
        return;
    }
    std::vector<NODE_ATTRIBUTE_DEVICE>::iterator it;
    for (it = allSubCaminf.begin(); it != allSubCaminf.end(); ++it)
    {
        string strinf = UnicodeToAscii(it->inffile);
        string strhardid = UnicodeToAscii(it->hardid);
    }
}


void GetSubCamHardidandInf()
{
    std::vector<wstring> vec2;
    isMatchdVidPidFromPlugEvent("HOTPLUGEVENT", "CAM_SUB_REGEX", L"USB#VID_2945&PID_2002#", vec2);

    std::string strMicPID = "USB\VID_351E&PID_00CA&REV_0409";
    static std::vector<wstring> allvidpid;
    static NODE_ATTRIBUTE_DEVICE NodeInfo1;
    if (!GetSubCamHardIDAndInfFile(strMicPID, "CAM_SUB_A", "D7PRO", allvidpid, NodeInfo1))
    {
        return;
    }
    static std::vector<wstring> allvidpid2;
    static NODE_ATTRIBUTE_DEVICE NodeInfo2;
    strMicPID = "USB\VID_351E&PID_00CB&REV_0409";
    if (!GetSubCamHardIDAndInfFile(strMicPID, "CAM_SUB_B", "D7PRO", allvidpid2, NodeInfo2))
    {
        return;
    }
    SetUpSubCamByDevconByForce("D7PRO");
    return;
}

void mainTest()
{

    vector<wstring> vecTPNode12;
    CXmlManager::GetInstance().GetNodeValue("CHECKDEVICE", "TOUCH", "TOUCH_NODE_1", vecTPNode12);
    CXmlManager::GetInstance().GetNodeValue("CHECKDEVICE", "TOUCH", "TOUCH_NODE_1", vecTPNode12);
    CXmlManager::GetInstance().GetNodeValue("CHECKDEVICE", "TOUCH", "TOUCH_NODE_1", vecTPNode12);
    CXmlManager::GetInstance().GetNodeValue("CHECKDEVICE", "TOUCH", "TOUCH_NODE_1", vecTPNode12);
}
int main()
{
#if 1
    mainTest();
    system("pause");
    return 0;
#endif
#if 0
    wstring wsmame;
    CXmlManager::GetInstance().GetNodeAttribute("SETUPDRIVERS", "CAM", "D7PRO", "name", wsmame);
    Sleep(1000);
    CXmlManager::GetInstance().Init(true);
    CXmlManager::GetInstance().GetNodeAttribute("SETUPDRIVERS", "CAM", "D7PRO", "name", wsmame);
    GetSubCamHardidandInf();
    int icmp = compareVersion((char*)"5.9.0.4", (char*)"5.10.0");
#endif
#if 0
    char szVID[256] = { 0 };
    char szPID[256] = { 0 };
    GetPrivateProfileStringA("DTEN", "cam_firm_upgrade_vid", "", szVID, 256, CONFIG_INIFILE_NAME_A);
    GetPrivateProfileStringA("DTEN", "cam_firm_upgrade_pid", "", szPID, 256, CONFIG_INIFILE_NAME_A);
    int HexVid = 0X1D6B;
    if (0 != strlen(szVID))
    {
        HexVid = stoi(szVID, 0, 16);
    }
    int HexPid = 0x0100;
    if (0 != strlen(szPID))
    {
        HexPid = stoi(szPID, 0, 16);
    }
#endif
    char buf[1000] = { 0 };
    GetTouchVer(buf,1000);
    static vector<wstring> vecTouchNode1;
    vector<wstring>::iterator it11 = vecTouchNode1.begin();
    int  i = 0;
    std::vector<wstring> arrHard = /*{ L"1.*" };//*/ { L"USB\\\\VID_067B&PID_2303&REV_0400", L"USB\\\\VID_067B&PID_2303&REV_0400.*" };
    std::vector<wstring>::iterator it;
    //arrHard[0] = L"USB\\\\VID_067B&PID_2303&REV_0400";
    for (it = arrHard.begin(); it != arrHard.end(); ++it, i++)
    {
        wstring wstrHardid = /*{L"1.11"}; //*/ L"USB\\VID_067B&PID_2303&REV_0400.1111_111";
        wregex pattern(*it);
        wsmatch  matchResult;
        //LOG(INFO) << "szHardWareID:" << SysUtil::ws2string(szHardWareID).c_str();

        //LOG(INFO) << "psRegex:" << SysUtil::ws2string(psRegex[i]).c_str();
        if (regex_match(wstrHardid, matchResult, pattern))
        {
            int num = 0;
            int n = 0;
        }
    }

    GetBuzzerHardidandInf();
    SetUpTouchDevconByForce();
    GetTPHardidandInf();
    SetUpCamByDevconByForce();
    GetCamHardidandInf();
    Get_Node_MIC_55();
    wstring value;
    std::vector<wstring> vec;
    std::vector<wstring> vec2;
    std::vector<wstring> vec5;
    std::vector<wstring> vec4;
    std::vector<NODE_ATTRIBUTE_DEVICE> vec3;
    
    CXmlManager::GetInstance().GetNodeValue("CHECKDEVICE", "CAM", "CAM_NODE_2", vec2);
    CXmlManager::GetInstance().GetNodeValue("CHECKDEVICE", "CAM", "CAM_NODE_1", vec);
    Sleep(1000);
    CXmlManager::GetInstance().Init();
    CXmlManager::GetInstance().GetNodeValue("CHECKDEVICE", "CAM", "CAM_NODE_2", vec5);
    CXmlManager::GetInstance().GetNodeValue("CHECKDEVICE", "CAM", "CAM_NODE_1", vec4);

    CXmlManager::GetInstance().GetNodeAttribute("SETUPDRIVERS", "MIC", "SETUPALL", "MIC_DRIVER_INF_FILE_55", "hardid", value);
    CXmlManager::GetInstance().GetNodeAttribute("CHECKDEVICE", "CAM", "VID_4255&PID_1001", "hardid", value);
    CXmlManager::GetInstance().GetNodeAttribute("SETUPDRIVERS", "MIC", "SETUPALL", vec3);
    vec2.shrink_to_fit();
    vec2.clear();
    CXmlManager::GetInstance().GetNodeAttribute("SETUPDRIVERS", "MIC", "MIC_55", "VID_4255&PID_1001", "inffile", value);
    CXmlManager::GetInstance().GetNodeValue("SETUPDRIVERS", "MIC", "MIC_55", "ALLVIDPID", vec2);
    CXmlManager::GetInstance().GetNodeAttribute("CHECKDEVICE", "CAM", "VID_4255&PID_1001", "inffile", value);
    CXmlManager::GetInstance().GetNodeValue("CHECKDEVICE", "CAM", "VID_4255&PID_1001", value);
    CXmlManager::GetInstance().GetNodeValue("CHECKDEVICE", "CAM", "NODE_VIDPID_6D", value);
    CXmlManager::GetInstance().GetNodeValue("CHECKDEVICE", "MIC", "MIC_NODE_1", vec2);
    int nMicArrNum = 1;
    wchar_t** psMicIdRegex = new wchar_t*[20];
   
    static vector<wstring> vecNode1;
    static vector<wstring> vecNode3;
    static vector<wstring> vecTPNode1;
    GetVidPidInfoFromXML("CHECKDEVICE", "TOUCH", "TOUCH_NODE_1", psMicIdRegex, nMicArrNum, vecTPNode1);
    wchar_t* pp = psMicIdRegex[1];
    GetVidPidInfoFromXML("SETUPDRIVERS", "MIC", "CHECKALL", psMicIdRegex, nMicArrNum, vecNode1);
    GetVidPidInfoFromXML("SETUPDRIVERS", "CAM", "CHECKALL", psMicIdRegex, nMicArrNum, vecNode3);
    GetVidPidInfoFromXML("CHECKDEVICE", "MIC", "MIC_NODE_1", psMicIdRegex, nMicArrNum, vecNode1);
    vecNode1.clear();
    vecNode1.shrink_to_fit();
    GetVidPidInfoFromXML("CHECKDEVICE", "MIC", "MIC_NODE_2", psMicIdRegex, nMicArrNum, vecNode1);
    GetVidPidInfoFromXML("CHECKDEVICE", "CAM", "CAM_NODE_1", psMicIdRegex, nMicArrNum, vecNode3);
    
    isMatchdVidPidFromPlugEvent("HOTPLUGEVENT", "TOUCH_REGEX", L"HID#VID_0457&PID_1548&Col03", vec2);
    isMatchdVidPidFromPlugEvent("HOTPLUGEVENT", "TOUCH_REGEX", L"", vec2);
    CXmlManager::GetInstance().GetNodeValue("CAM", vec);
    CXmlManager::GetInstance().GetNodeValue("HOTPLUGEVENT", "TOUCH_REGEX", vec2);
    CXmlManager::GetInstance().GetNodeValue("CAM", "NODE_VIDPID_6D", value);
    CXmlManager::GetInstance().GetNodeValue("MIC", "STR_MIC_HARDID_75_REGEX", value);
    CXmlManager::GetInstance().GetNodeAttribute("MIC", "STR_MIC_HARDID_75_REGEX", "name", value);
    CXmlManager::GetInstance().GetNodeAttribute("MIC", "STR_MIC_HARDID_55_REGEX", "name", value);
    
    delete[]psMicIdRegex;
    psMicIdRegex = nullptr;
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
