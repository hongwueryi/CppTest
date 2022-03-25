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
#define XMLPATH "E:\\Dten\\other demo\\CppTest\\Debug\\config.xml"

xml_node<>* g_root = 0;
std::mutex g_xmlMutex;

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
        rapidxml::xml_attribute<>* NodeAttribute = nodeC->first_attribute("name");
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