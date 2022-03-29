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

bool GetMicVidPidInfo(const char*nodeName, wchar_t** psMicIdRegex, int& nMicArrNum, vector<wstring>&vecNode)
{
    if (vecNode.empty())
    {
        CXmlManager::GetInstance().GetNodeValue("CHECKDEVICE", "MIC", nodeName, vecNode);
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

int main()
{
    Get_Node_MIC_55();
    wstring value;
    std::vector<wstring> vec;
    std::vector<wstring> vec2;
    std::vector<NODE_ATTRIBUTE_DEVICE> vec3;
    CXmlManager::GetInstance().GetNodeValue("CHECKDEVICE", "CAM", "NODE_VIDPID_6D", value);
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
    wchar_t* psMicIdRegex[8] = { 0 };
    static vector<wstring> vecNode1;
    static vector<wstring> vecNode3;
    GetMicVidPidInfo("MIC_NODE_1", psMicIdRegex, nMicArrNum, vecNode1);
    GetMicVidPidInfo("MIC_NODE_1", psMicIdRegex, nMicArrNum, vecNode1);
    GetMicVidPidInfo("MIC_NODE_3", psMicIdRegex, nMicArrNum, vecNode3);

    isMatchdVidPidFromPlugEvent("HOTPLUGEVENT", "TOUCH_REGEX", L"HID#VID_0457&PID_1548&Col03", vec2);
    isMatchdVidPidFromPlugEvent("HOTPLUGEVENT", "TOUCH_REGEX", L"", vec2);
    CXmlManager::GetInstance().GetNodeValue("CAM", vec);
    CXmlManager::GetInstance().GetNodeValue("HOTPLUGEVENT", "TOUCH_REGEX", vec2);
    CXmlManager::GetInstance().GetNodeValue("CAM", "NODE_VIDPID_6D", value);
    CXmlManager::GetInstance().GetNodeValue("MIC", "STR_MIC_HARDID_75_REGEX", value);
    CXmlManager::GetInstance().GetNodeAttribute("MIC", "STR_MIC_HARDID_75_REGEX", "name", value);
    CXmlManager::GetInstance().GetNodeAttribute("MIC", "STR_MIC_HARDID_55_REGEX", "name", value);
    
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
