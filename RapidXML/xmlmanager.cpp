#include <string>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "xmlmanager.h"
#include <iostream>
#include <mutex>
#include <vector>
#include <windows.h>
using namespace rapidxml;

#define DTEN_XML_FLAG "DTEN"
#define XMLPATH1 "E:\\Dten\\other demo\\CppTest\\Debug\\config.xml"
#define XMLPATH "E:\\Dten\\gitDten\\remote\\DTENOTA_G3\\DTENOTA\\config.xml"

xml_node<>* g_root = 0;
std::mutex g_xmlMutex;

int s2int(const char* source, int Radix)
{
    if (nullptr == source)
        return 0;
    char* endptr = nullptr;
    return strtol(source, &endptr, Radix);
}

std::wstring Utf8ToUnicode(const std::string& str)
{
    int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    wchar_t* pUnicode = (wchar_t*)malloc(sizeof(wchar_t) * unicodeLen);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, pUnicode, unicodeLen);
    std::wstring ret_str = pUnicode;
    free(pUnicode);
    return ret_str;
}

CXmlManager::CXmlManager()
{
    Init();
}

CXmlManager& CXmlManager::GetInstance()
{
    static CXmlManager pXML;
    return pXML;
}

bool CXmlManager::Init()
{ 
    std::lock_guard<std::mutex> lk(g_xmlMutex);
    if (0 != g_root)
    {
        return true;
    }
    try {
        static file<>fdoc(XMLPATH);
        static xml_document<> doc;
        doc.parse<0>(fdoc.data());
        g_root = doc.first_node();
        if (0 == g_root)
        {
            return false;
        }
        std::cout << g_root->name() << std::endl;
        if (0 != strcmp(g_root->name(), DTEN_XML_FLAG))
        {
            return false;
        }
    }
    catch (rapidxml::parse_error e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}

bool CXmlManager::GetNodeValue(const char* NodeName, std::vector<std::wstring>& vec)
{
    if (!Init() || nullptr == NodeName)
        return false;
    try {
        xml_node<>* node = g_root->first_node(NodeName);
        if (0 == node)
        {
            return false;
        }
        for (xml_node<>* childNode = node->first_node();
            childNode != NULL; childNode = childNode->next_sibling())
        {
            std::cout << childNode->name() << std::endl;
            std::cout << childNode->value() << std::endl;
            std::wstring value = Utf8ToUnicode(childNode->value());
            vec.push_back(value);
        }
    }
    catch (rapidxml::parse_error e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}

bool CXmlManager::GetNodeValue(const char* NodePName, const char* NodeCName, std::vector<std::wstring>& vec)
{
    if (!Init() || nullptr == NodePName || nullptr == NodeCName)
        return false;
    try {
        xml_node<>* nodeP = g_root->first_node(NodePName);
        if (0 == nodeP)
        {
            return false;
        }
        xml_node<>* nodeC = nodeP->first_node(NodeCName);
        if (0 == nodeC)
        {
            return false;
        }
        for (xml_node<>* childNode = nodeC->first_node();
            childNode != NULL; childNode = childNode->next_sibling())
        {
            std::cout << childNode->name() << std::endl;
            std::cout << childNode->value() << std::endl;
            std::wstring value = Utf8ToUnicode(childNode->value());
            vec.push_back(value);
        }
    }
    catch (rapidxml::parse_error e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}

bool CXmlManager::GetNodeValue(const char* NodePName, const char* NodeCName,
    const char* NodeGName, std::vector<std::wstring>& vec)
{
    if (!Init() || nullptr == NodePName || nullptr == NodeCName)
        return false;
    try {
        xml_node<>* nodeP = g_root->first_node(NodePName);
        if (0 == nodeP)
        {
            return false;
        }
        xml_node<>* nodeC = nodeP->first_node(NodeCName);
        if (0 == nodeC)
        {
            return false;
        }
        xml_node<>* nodeG = nodeC->first_node(NodeGName);
        if (0 == nodeG)
        {
            return false;
        }
        for (xml_node<>* childNode = nodeG->first_node();
            childNode != NULL; childNode = childNode->next_sibling())
        {
            std::cout << childNode->name() << std::endl;
            std::cout << childNode->value() << std::endl;
            std::wstring value = Utf8ToUnicode(childNode->value());
            vec.push_back(value);
        }
    }
    catch (rapidxml::parse_error e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}

bool CXmlManager::GetNodeValue(const char* NodePName, const char* NodeCName, 
    const char* NodeGName, const char* NodeGSName, std::vector<std::wstring>& vec)
{
    if (!Init() || nullptr == NodePName || nullptr == NodeCName)
        return false;
    try {
        xml_node<>* nodeP = g_root->first_node(NodePName);
        if (0 == nodeP)
        {
            return false;
        }
        xml_node<>* nodeC = nodeP->first_node(NodeCName);
        if (0 == nodeC)
        {
            return false;
        }
        xml_node<>* nodeG = nodeC->first_node(NodeGName);
        if (0 == nodeG)
        {
            return false;
        }
        xml_node<>* nodeGS = nodeG->first_node(NodeGSName);
        if (0 == nodeGS)
        {
            return false;
        }
        for (xml_node<>* childNode = nodeGS->first_node();
            childNode != NULL; childNode = childNode->next_sibling())
        {
            std::cout << childNode->name() << std::endl;
            std::cout << childNode->value() << std::endl;
            std::wstring value = Utf8ToUnicode(childNode->value());
            vec.push_back(value);
        }
    }
    catch (rapidxml::parse_error e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}

bool CXmlManager::GetNodeValue(const char* NodePName, const char* NodeCName, std::wstring& value)
{
    if (!Init() || nullptr == NodePName || nullptr == NodeCName)
        return false;
    try {
        xml_node<>* nodeP = g_root->first_node(NodePName);
        if (0 == nodeP)
        {
            return false;
        }
        xml_node<>* nodeC = nodeP->first_node(NodeCName);
        if (0 == nodeC)
        {
            return false;
        }
        value = Utf8ToUnicode(nodeC->value());
    }
    catch (rapidxml::parse_error e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}

bool CXmlManager::GetNodeValue(const char* NodePName, const char* NodeCName, const char* NodeGName, std::wstring& value)
{
    if (!Init() || nullptr == NodePName || nullptr == NodeCName)
        return false;
    try {
        xml_node<>* nodeP = g_root->first_node(NodePName);
        if (0 == nodeP)
        {
            return false;
        }
        xml_node<>* nodeC = nodeP->first_node(NodeCName);
        if (0 == nodeC)
        {
            return false;
        }
        xml_node<>* nodeG = nodeC->first_node(NodeGName);
        if (0 == nodeG)
        {
            return false;
        }
        value = Utf8ToUnicode(nodeG->value());
    }
    catch (rapidxml::parse_error e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}

bool CXmlManager::GetNodeAttribute(const char* NodePName,
    const char* NodeCName, const char* attrName, std::wstring& value)
{
    if (!Init() || nullptr == NodePName || nullptr == NodeCName)
        return false;
    try {
        xml_node<>* nodeP = g_root->first_node(NodePName);
        if (0 == nodeP)
        {
            return false;
        }
        xml_node<>* nodeC = nodeP->first_node(NodeCName);
        if (0 == nodeC)
        {
            return false;
        }
        rapidxml::xml_attribute<>* NodeAttribute = nodeC->first_attribute(attrName);
        if (0 == NodeAttribute)
        {
            return false;
        }
        value = Utf8ToUnicode(NodeAttribute->value());
    }
    catch (rapidxml::parse_error e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}

bool CXmlManager::GetNodeAttribute(const char* NodePName,
    const char* NodeCName, const char* NodeGName, const char* attrName, std::wstring& value)
{
    if (!Init() || nullptr == NodePName || nullptr == NodeCName)
        return false;
    try {
        xml_node<>* nodeP = g_root->first_node(NodePName);
        if (0 == nodeP)
        {
            return false;
        }
        xml_node<>* nodeC = nodeP->first_node(NodeCName);
        if (0 == nodeC)
        {
            return false;
        }
        xml_node<>* nodeG = nodeC->first_node(NodeGName);
        if (0 == nodeG)
        {
            return false;
        }
        rapidxml::xml_attribute<>* NodeAttribute = nodeG->first_attribute(attrName);
        if (0 == NodeAttribute)
        {
            return false;
        }
        value = Utf8ToUnicode(NodeAttribute->value());
    }
    catch (rapidxml::parse_error e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}

bool CXmlManager::GetNodeAttribute(const char* NodePName, const char* NodeCName,
    const char* NodeGName, const char* NodeGSName, const char* attrName, std::wstring& value)
{
    if (!Init() || nullptr == NodePName || nullptr == NodeCName)
        return false;
    try {
        xml_node<>* nodeP = g_root->first_node(NodePName);
        if (0 == nodeP)
        {
            return false;
        }
        xml_node<>* nodeC = nodeP->first_node(NodeCName);
        if (0 == nodeC)
        {
            return false;
        }
        xml_node<>* nodeG = nodeC->first_node(NodeGName);
        if (0 == nodeG)
        {
            return false;
        }
        xml_node<>* nodeGS = nodeG->first_node(NodeGSName);
        if (0 == nodeGS)
        {
            return false;
        }
        rapidxml::xml_attribute<>* NodeAttribute = nodeGS->first_attribute(attrName);
        if (0 == NodeAttribute)
        {
            return false;
        }
        value = Utf8ToUnicode(NodeAttribute->value());
    }
    catch (rapidxml::parse_error e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}

bool CXmlManager::GetNodeAttribute(const char* NodePName, const char* NodeCName,
    const char* NodeGName, NODE_ATTRIBUTE_DEVICE& NodeInfo)
{
    if (!Init() || nullptr == NodePName || nullptr == NodeCName)
        return false;
    try {
        xml_node<>* nodeP = g_root->first_node(NodePName);
        if (0 == nodeP)
        {
            return false;
        }
        xml_node<>* nodeC = nodeP->first_node(NodeCName);
        if (0 == nodeC)
        {
            return false;
        }
        xml_node<>* nodeG = nodeC->first_node(NodeGName);
        if (0 == nodeG)
        {
            return false;
        }

        rapidxml::xml_attribute<>* Nodeharid = nodeG->first_attribute("hardid");
        if (0 == Nodeharid)
        {
            return false;
        }
        std::wstring hardid = Utf8ToUnicode(Nodeharid->value());
        rapidxml::xml_attribute<>* Nodeinffile = nodeG->first_attribute("inffile");
        if (0 == Nodeinffile)
        {
            return false;
        }
        std::wstring inffile = Utf8ToUnicode(Nodeinffile->value());
        NodeInfo.hardid = hardid;
        NodeInfo.inffile = inffile;
    }
    catch (rapidxml::parse_error e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}

bool CXmlManager::GetNodeAttribute(const char* NodePName, const char* NodeCName,
    const char* NodeGName, std::vector<NODE_ATTRIBUTE_DEVICE>& vec)
{
    if (!Init() || nullptr == NodePName || nullptr == NodeCName)
        return false;
    try {
        xml_node<>* nodeP = g_root->first_node(NodePName);
        if (0 == nodeP)
        {
            return false;
        }
        xml_node<>* nodeC = nodeP->first_node(NodeCName);
        if (0 == nodeC)
        {
            return false;
        }
        xml_node<>* nodeG = nodeC->first_node(NodeGName);
        if (0 == nodeG)
        {
            return false;
        }

        for (xml_node<>* childNode = nodeG->first_node();
            childNode != NULL; childNode = childNode->next_sibling())
        {
            rapidxml::xml_attribute<>* Nodeharid = childNode->first_attribute("hardid");
            if (0 == Nodeharid)
            {
                return false;
            }
            std::wstring hardid = Utf8ToUnicode(Nodeharid->value());
            rapidxml::xml_attribute<>* Nodeinffile = childNode->first_attribute("inffile");
            if (0 == Nodeinffile)
            {
                return false;
            }
            std::wstring inffile = Utf8ToUnicode(Nodeinffile->value());
            NODE_ATTRIBUTE_DEVICE NodeInfo;
            NodeInfo.hardid = hardid;
            NodeInfo.inffile = inffile;
            vec.push_back(NodeInfo);
        } 
    }
    catch (rapidxml::parse_error e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}

bool CXmlManager::GetNodeAttribute(const char* NodePName, const char* NodeCName, const char* NodeGName, const char* NodeGSName, std::vector<NODE_ATTRIBUTE_DEVICE>& vec)
{
    if (!Init() || nullptr == NodePName || nullptr == NodeCName)
        return false;
    try {
        xml_node<>* nodeP = g_root->first_node(NodePName);
        if (0 == nodeP)
        {
            return false;
        }
        xml_node<>* nodeC = nodeP->first_node(NodeCName);
        if (0 == nodeC)
        {
            return false;
        }
        xml_node<>* nodeG = nodeC->first_node(NodeGName);
        if (0 == nodeG)
        {
            return false;
        }
        xml_node<>* nodeGS = nodeG->first_node(NodeGSName);
        if (0 == nodeG)
        {
            return false;
        }

        for (xml_node<>* childNode = nodeGS->first_node();
            childNode != NULL; childNode = childNode->next_sibling())
        {
            rapidxml::xml_attribute<>* Nodeharid = childNode->first_attribute("hardid");
            if (0 == Nodeharid)
            {
                return false;
            }
            std::wstring hardid = Utf8ToUnicode(Nodeharid->value());
            rapidxml::xml_attribute<>* Nodeinffile = childNode->first_attribute("inffile");
            if (0 == Nodeinffile)
            {
                return false;
            }
            std::wstring inffile = Utf8ToUnicode(Nodeinffile->value());
            NODE_ATTRIBUTE_DEVICE NodeInfo;
            NodeInfo.hardid = hardid;
            NodeInfo.inffile = inffile;
            vec.push_back(NodeInfo);
        }
    }
    catch (rapidxml::parse_error e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}

bool CXmlManager::GetNodeAttribute(const char* NodePName, const char* NodeCName, const char* NodeGName, const char* NodeGSName, NODE_ATTRIBUTE_DEVICE& NodeInfo)
{
    if (!Init() || nullptr == NodePName || nullptr == NodeCName)
        return false;
    try {
        xml_node<>* nodeP = g_root->first_node(NodePName);
        if (0 == nodeP)
        {
            return false;
        }
        xml_node<>* nodeC = nodeP->first_node(NodeCName);
        if (0 == nodeC)
        {
            return false;
        }
        xml_node<>* nodeG = nodeC->first_node(NodeGName);
        if (0 == nodeG)
        {
            return false;
        }
        xml_node<>* nodeGS = nodeG->first_node(NodeGSName);
        if (0 == nodeGS)
        {
            return false;
        }

        rapidxml::xml_attribute<>* Nodeharid = nodeGS->first_attribute("hardid");
        if (0 == Nodeharid)
        {
            return false;
        }
        std::wstring hardid = Utf8ToUnicode(Nodeharid->value());
        rapidxml::xml_attribute<>* Nodeinffile = nodeGS->first_attribute("inffile");
        if (0 == Nodeinffile)
        {
            return false;
        }
        std::wstring inffile = Utf8ToUnicode(Nodeinffile->value());
        NodeInfo.hardid = hardid;
        NodeInfo.inffile = inffile;
    }
    catch (rapidxml::parse_error e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}

bool CXmlManager::GetNodeAttribute(const char* NodePName, const char* NodeCName, std::vector<NODE_ATTRIBUTE_DEVICE_EX>& vec)
{
    if (!Init() || nullptr == NodePName || nullptr == NodeCName)
        return false;
    try {
        xml_node<>* nodeP = g_root->first_node(NodePName);
        if (0 == nodeP)
        {
            return false;
        }
        xml_node<>* nodeC = nodeP->first_node(NodeCName);
        if (0 == nodeC)
        {
            return false;
        }
        for (xml_node<>* childNode = nodeC->first_node();
            childNode != NULL; childNode = childNode->next_sibling())
        {
            rapidxml::xml_attribute<>* Nodeharid = childNode->first_attribute("hardid");
            if (0 == Nodeharid)
            {
                return false;
            }
            std::wstring hardid = Utf8ToUnicode(Nodeharid->value());

            rapidxml::xml_attribute<>* Nodeinffile = childNode->first_attribute("inffile");
            if (0 == Nodeinffile)
            {
                return false;
            }
            std::wstring inffile = Utf8ToUnicode(Nodeinffile->value());

            rapidxml::xml_attribute<>* NodeName = childNode->first_attribute("name");
            if (0 == NodeName)
            {
                return false;
            }
            std::wstring strName = Utf8ToUnicode(NodeName->value());

            rapidxml::xml_attribute<>* NodeVidPid = childNode->first_attribute("vidpid");
            if (0 == NodeVidPid)
            {
                return false;
            }
            std::wstring strVidPid = Utf8ToUnicode(NodeVidPid->value());


            NODE_ATTRIBUTE_DEVICE_EX NodeInfo;
            NodeInfo.hardid = hardid;
            NodeInfo.inffile = inffile;
            NodeInfo.name = strName;
            NodeInfo.vidpid = strVidPid;
            vec.push_back(NodeInfo);
        }
    }
    catch (rapidxml::parse_error e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}

bool CXmlManager::GetNodeAttribute(const char* NodePName, const char* NodeCName,
    const char* NodeGName, NODE_ATTRIBUTE_FIRMWARE& AttrFirmWare)
{
    if (!Init() || nullptr == NodePName || nullptr == NodeCName)
        return false;
    try {
        xml_node<>* nodeP = g_root->first_node(NodePName);
        if (0 == nodeP)
        {
            return false;
        }
        xml_node<>* nodeC = nodeP->first_node(NodeCName);
        if (0 == nodeC)
        {
            return false;
        }
        xml_node<>* nodeG = nodeC->first_node(NodeGName);
        if (0 == nodeG)
        {
            return false;
        }

        std::string temp = "";
        rapidxml::xml_attribute<>* NodeVid = nodeG->first_attribute("vid");
        if (0 == NodeVid || nullptr == NodeVid->value())
        {
            //return false;
        }
        else
        {
            temp = NodeVid->value();
        }
        AttrFirmWare.uVid = s2int(temp.c_str(), 16);

        rapidxml::xml_attribute<>* NodePid = nodeG->first_attribute("pid");
        if (0 == NodePid || nullptr == NodePid->value())
        {
            temp = "";
            //return false;
        }
        else
        {
            temp = NodePid->value();
        }
        AttrFirmWare.uPid = s2int(temp.c_str(), 16);

        rapidxml::xml_attribute<>* NodeVersion = nodeG->first_attribute("version");
        if (0 == NodeVersion || nullptr == NodeVersion->value())
        {
            return false;
        }
        AttrFirmWare.version = NodeVersion->value();

        rapidxml::xml_attribute<>* NodeBinfile = nodeG->first_attribute("binfile");
        if (0 == NodeBinfile || nullptr == NodeBinfile->value())
        {
            return false;
        }
        AttrFirmWare.binFile = NodeBinfile->value();

        rapidxml::xml_attribute<>* NodeFName = nodeG->first_attribute("friendlyname");
        if (0 == NodeFName || nullptr == NodeFName->value())
        {
            temp = "";
            //return false;
        }
        else
        {
            temp = NodeFName->value();
        }
        AttrFirmWare.friendlyName = temp;

        rapidxml::xml_attribute<>* NodeTName = nodeG->first_attribute("type");
        if (0 == NodeTName || nullptr == NodeTName->value())
        {
            temp = "";
            //return false;
        }
        else
        {
            temp = NodeTName->value();
        }
        AttrFirmWare.type = temp;
    }

    catch (rapidxml::parse_error e)
    {
        return false;
    }

    return true;
}

bool CXmlManager::GetAllNodeName(const char* NodePName, const char* NodeCName, std::vector<std::string>& vec)
{
    if (!Init() || nullptr == NodePName || nullptr == NodeCName)
        return false;
    try {
        xml_node<>* nodeP = g_root->first_node(NodePName);
        if (0 == nodeP)
        {
            return false;
        }
        xml_node<>* nodeC = nodeP->first_node(NodeCName);
        if (0 == nodeC)
        {
            return false;
        }
       
        for (xml_node<>* childNode = nodeC->first_node();
            childNode != NULL; childNode = childNode->next_sibling())
        {
            if (nullptr != childNode->name())
            {
                vec.push_back(childNode->name());
            }
        }
    }
    catch (rapidxml::parse_error e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}