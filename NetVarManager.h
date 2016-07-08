#ifndef NETVARMANAGER_H_INCLUDED
#define NETVARMANAGER_H_INCLUDED

#include <fstream>
#include <vector>
#include "SDK.h"

struct RecvProp;

class DVariant {
public:
    union {
        float m_Float;
        long m_Int;
        char *m_pString;
        void *m_pData;
        float m_Vector[3];
    };
};

class CRecvProxyData {
public:
    const RecvProp *m_pRecvProp;
    DVariant m_Value;
    int m_iElement;
    int m_ObjectID;
};

typedef void(*RecvVarProxyFn)(const CRecvProxyData *pData, void *pStruct, void *pOut);

struct RecvTable {
    RecvProp *m_pProps;
    int m_nProps;
    void *m_pDecoder;
    char *m_pNetTableName;
    bool m_bInitialized;
    bool m_bInMainList;
};

struct RecvProp {
    char *m_pVarName;
    int m_RecvType;
    int m_Flags;
    int m_StringBufferSize;
    bool m_bInsideArray;
    const void *m_pExtraData;
    RecvProp *m_pArrayProp;
    void *m_ArrayLengthProxy;
    void *m_ProxyFn;
    void *m_DataTableProxyFn;
    RecvTable *m_pDataTable;
    int m_Offset;
    int m_ElementStride;
    int m_nElements;
    const char *m_pParentArrayPropName;
};

struct ClientClass {
    void *m_pCreateFn;
    void *m_pCreateEventFn;
    char *m_pNetworkName;
    RecvTable *m_pRecvTable;
    ClientClass *m_pNext;
    int m_ClassID;
};

class CNetVarManager {
public:
    void Initialize();
    void GrabOffsets();
    int GetOffset(const char *tableName, const char *propName);
    bool HookProp(const char *tableName, const char *propName, RecvVarProxyFn fun);
    void DumpNetvars(std::string path);

private:
    int Get_Prop(const char *tableName, const char *propName, HLClient::RecvProp **prop = 0);
    int Get_Prop(HLClient::RecvTable *recvTable, const char *propName, HLClient::RecvProp **prop = 0);
    HLClient::RecvTable *GetTable(const char *tableName);
    std::vector<HLClient::RecvTable *> m_tables;
    void DumpTable(HLClient::RecvTable *table, int depth);
    std::ofstream m_file;
};

extern CNetVarManager *NetVarManager;

#endif
