#include <iomanip>
#include "Main.h"

using namespace std;

void CNetVarManager::Initialize() {
    m_tables.clear();

    HLClient::ClientClass *clientClass = g_pClient->GetAllClasses();
    if (!clientClass)
        return;

    while (clientClass) {
        HLClient::RecvTable *recvTable = clientClass->m_pRecvTable;
        m_tables.push_back(recvTable);

        clientClass = clientClass->m_pNext;
    }
}

int CNetVarManager::GetOffset(const char *tableName, const char *propName) {
    int offset = Get_Prop(tableName, propName);

    if (!offset) {
        return 0;
    }

    return offset;
}

bool CNetVarManager::HookProp(const char *tableName, const char *propName, RecvVarProxyFn fun) {
    HLClient::RecvProp *recvProp = 0;
    Get_Prop(tableName, propName, &recvProp);

    if (!recvProp)
        return false;

    recvProp->m_ProxyFn = fun;

    return true;
}

int CNetVarManager::Get_Prop(const char *tableName, const char *propName, HLClient::RecvProp **prop) {
    HLClient::RecvTable *recvTable = GetTable(tableName);
    if (!recvTable)
        return 0;

    int offset = Get_Prop(recvTable, propName, prop);
    if (!offset)
        return 0;

    return offset;
}

int CNetVarManager::Get_Prop(HLClient::RecvTable *recvTable, const char *propName, HLClient::RecvProp **prop) {
    int extraOffset = 0;

    for (int i = 0; i < recvTable->m_nProps; ++i) {
        HLClient::RecvProp *recvProp = &recvTable->m_pProps[i];
        HLClient::RecvTable *child = recvProp->m_pDataTable;

        if (child && (child->m_nProps > 0)) {
            int tmp = Get_Prop(child, propName, prop);
            if (tmp)
                extraOffset += (recvProp->m_Offset + tmp);
        }

        if (strcasecmp(recvProp->m_pVarName, propName))
            continue;

        if (prop)
            *prop = recvProp;

        return (recvProp->m_Offset + extraOffset);
    }

    return extraOffset;
}

HLClient::RecvTable *CNetVarManager::GetTable(const char *tableName) {
    if (m_tables.empty())
        return 0;

    for (int i = 0; i < m_tables.size(); i++) {
        HLClient::RecvTable *table = m_tables[i];

        if (!table)
            continue;

        if (strcasecmp(table->m_pNetTableName, tableName) == 0)
            return table;
    }

    return 0;
}

void CNetVarManager::DumpTable(HLClient::RecvTable *table, int depth) {
    string pre("");

    for (int i = 0; i < depth; i++)
        pre.append("\t");

    m_file << pre << table->m_pNetTableName << "\n";

    for (int i = 0; i < table->m_nProps; i++) {
        HLClient::RecvProp *prop = &table->m_pProps[i];
        if (!prop)
            continue;

        string varName(prop->m_pVarName);

        if (varName.find("baseclass") == 0 || varName.find("0") == 0 || varName.find("1") == 0 ||
            varName.find("2") == 0)
            continue;

        m_file << pre << "\t " << varName << " "
        << setfill('_') << setw((int) (60 - varName.length() - (depth * 4)))
        << "[0x" << setfill('0') << setw(8) << hex
        << uppercase << prop->m_Offset << "]\n";

        if (prop->m_pDataTable)
            DumpTable(prop->m_pDataTable, depth + 1);
    }
}

void CNetVarManager::DumpNetvars(string path) {
    // Get current time
    time_t t = time(0);
    struct tm *now = localtime(&t);

    m_file.open(path);
    m_file << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << " " << (now->tm_mday) << '/' <<
    (now->tm_mon + 1) << '/' << now->tm_year + 1900 << "\n";
    m_file << "NetVar Dump by A5 / teamgamerfood\n\nhaha look proper formatting \n\n";

    for (HLClient::ClientClass *pClass = g_pClient->GetAllClasses(); pClass != NULL; pClass = pClass->m_pNext) {
        HLClient::RecvTable *table = pClass->m_pRecvTable;
        DumpTable(table, 0);
    }

    m_file.close();
}

CNetVarManager *NetVarManager = new CNetVarManager;
