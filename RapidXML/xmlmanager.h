#pragma once
typedef struct _NODE_ATTRIBUTE_DEVICE
{
    std::wstring hardid;
    std::wstring inffile;
} NODE_ATTRIBUTE_DEVICE;

class CXmlManager
{
public:
    static CXmlManager& GetInstance();

public:
    bool Init();
    bool GetNodeValue(const char* NodeName, std::vector<std::wstring>& vec);
    bool GetNodeValue(const char* NodePName, const char* NodeCName, std::vector<std::wstring>& vec);
    bool GetNodeValue(const char* NodePName, const char* NodeCName, const char* NodeGName, std::vector<std::wstring>& vec);
    bool GetNodeValue(const char* NodePName, const char* NodeCName, const char* NodeGName, const char*NodeGSName, std::vector<std::wstring>& vec);

    bool GetNodeValue(const char* NodePName, const char* NodeCName, std::wstring& value);
    bool GetNodeValue(const char* NodePName, const char* NodeCName, const char* NodeGName, std::wstring& value);

    bool GetNodeAttribute(const char* NodePName, const char* NodeCName, const char*attrName, std::wstring& value);
    bool GetNodeAttribute(const char* NodePName, const char* NodeCName, const char* NodeGName, const char* attrName, std::wstring& value);
    bool GetNodeAttribute(const char* NodePName, const char* NodeCName, const char* NodeGName, const char* NodeGSName, const char* attrName, std::wstring& value);
    bool GetNodeAttribute(const char* NodePName, const char* NodeCName, const char* NodeGName, const char* NodeGSName, NODE_ATTRIBUTE_DEVICE& NodeInfo);

    bool GetNodeAttribute(const char* NodePName, const char* NodeCName, const char* NodeGName, std::vector<NODE_ATTRIBUTE_DEVICE>& vec);

private:
    CXmlManager();
    ~CXmlManager(){}
};

