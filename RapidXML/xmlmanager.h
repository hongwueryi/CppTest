#pragma once
#include <Windows.h>
typedef struct _NODE_ATTRIBUTE_DEVICE
{
    std::wstring hardid;
    std::wstring inffile;
} NODE_ATTRIBUTE_DEVICE;

typedef struct _NODE_ATTRIBUTE_DEVICE_EX
{
    std::wstring hardid;
    std::wstring name;
    std::wstring vidpid;
    std::wstring inffile;
} NODE_ATTRIBUTE_DEVICE_EX;

typedef struct _NODE_ATTRIBUTE_FIRMWARE
{
    USHORT uVid;
    USHORT uPid;
    std::string version;
    std::string binFile;
    std::string friendlyName;
    std::string type;
} NODE_ATTRIBUTE_FIRMWARE;


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

    bool GetNodeAttribute(const char* NodePName, const char* NodeCName, const char* NodeGName, NODE_ATTRIBUTE_DEVICE& NodeInfo);
    bool GetNodeAttribute(const char* NodePName, const char* NodeCName, const char* NodeGName, const char* NodeGSName, NODE_ATTRIBUTE_DEVICE& NodeInfo);

    bool GetNodeAttribute(const char* NodePName, const char* NodeCName, const char* NodeGName, std::vector<NODE_ATTRIBUTE_DEVICE>& vec);
    bool GetNodeAttribute(const char* NodePName, const char* NodeCName, const char* NodeGName, const char* NodeGSName, std::vector<NODE_ATTRIBUTE_DEVICE>& vec);
    bool GetNodeAttribute(const char* NodePName, const char* NodeCName, std::vector<NODE_ATTRIBUTE_DEVICE_EX>& vec);

    bool GetNodeAttribute(const char* NodePName, const char* NodeCName, const char* NodeGName, NODE_ATTRIBUTE_FIRMWARE& AttrFirmWare);

    bool GetAllNodeName(const char* NodePName, const char* NodeCName, std::vector<std::string>& vec);

private:
    CXmlManager();
    ~CXmlManager(){}
};

