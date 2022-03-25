#pragma once

class CXmlManager
{
public:
    static CXmlManager& GetInstance();

public:
    bool Init();
    bool GetNodeValue(const char* NodeName, std::vector<std::wstring>& vec);
    bool GetNodeValue(const char* NodePName, const char* NodeCName, std::vector<std::wstring>& vec);

    bool GetNodeValue(const char* NodePName, const char* NodeCName, std::wstring& value);
    bool GetNodeAttribute(const char* NodePName, const char* NodeCName, const char*attrName, std::wstring& value);

private:
    CXmlManager();
    ~CXmlManager(){}
};

