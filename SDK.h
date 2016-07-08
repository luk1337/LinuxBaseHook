#ifndef SDK_H_INCLUDED
#define SDK_H_INCLUDED

#include "random"
#include "Vector.h"

/////////////////////////////////////////////
//not sure who to credit for this, sorry :'(
/////////////////////////////////////////////
inline void**& getvtable(void* inst, size_t offset = 0) {
    return *reinterpret_cast<void***>((size_t)inst + offset);
}

inline const void** getvtable(const void* inst, size_t offset = 0) {
    return *reinterpret_cast<const void***>((size_t)inst + offset);
}

template<typename Fn>
inline Fn getvfunc(const void* inst, size_t index, size_t offset = 0) {
    return reinterpret_cast<Fn>(getvtable(inst, offset)[index]);
}

class ICollideable
{
public:
    Vector& OBBMins() {
        return *(Vector*)((unsigned long long)this + 0x00000010);
    }

    Vector& OBBMaxs() {
        return *(Vector*)((unsigned long long)this + 0x0000001C);
    }
};

class CBaseEntity
{
public:
    int GetHealth() {
        return *(int*)(this + 0x0000012C);
    }

    int GetTeamNum() {
        return *(int*)(this + 0x000000120);
    }

    bool GetAlive() {
        return (bool)(*(int*)(this + 0x0000028B));
    }

    bool GetDormant() {
        return (bool)(*(int*)(this + 0x00000119));
    }

    Vector GetOrigin() {
        return *(Vector*)((unsigned long long)this + 0x00000164);
    }

    ICollideable* GetCollideable() {
        return (ICollideable*)(this + 0x00000370);
    }
};
class CEngineClient
{
public:
    typedef struct player_info_s {
        unsigned long long unknown;
        unsigned long long unknown1;
        char name[128];
        int userID;
        char guid[33];
        int32_t friendsID;
        char friendsName[128];
        char _pad[0x28];
    } player_info_t;

    void GetScreenSize(int& width, int& height) {
        typedef void(* OriginalFn)(void*, int& , int&);
        return getvfunc<OriginalFn>(this, 5)(this, width, height);
    }

    bool GetPlayerInfo(int ent_num, player_info_t *pinfo) {
        typedef bool(* OriginalFn)(void*, int, player_info_t *);
        return getvfunc<OriginalFn>(this, 8)(this, ent_num, pinfo);
    }

    bool Con_IsVisible(void) {
        typedef bool(* OriginalFn)(void*);
        return getvfunc<OriginalFn>(this, 11)(this);
    }

    int GetLocalPlayer(void) {
        typedef int(* OriginalFn)(void*);
        return getvfunc<OriginalFn>(this, 12)(this);
    }

    float Time(void) {
        typedef float(* OriginalFn)(void*);
        return getvfunc<OriginalFn>(this, 14)(this);
    }

    void GetViewAngles(Vector& va) {
        typedef void(* OriginalFn)(void*, Vector& va);
        return getvfunc<OriginalFn>(this, 19)(this, va);
    }

    void SetViewAngles(Vector& va) {
        typedef void(* OriginalFn)(void*, Vector& va);
        return getvfunc<OriginalFn>(this, 20)(this, va);
    }

    int GetMaxClients(void) {
        typedef int(* OriginalFn)(void*);
        return getvfunc<OriginalFn>(this, 21)(this);
    }

    bool IsInGame(void) {
        typedef bool(* OriginalFn)(void*);
        return getvfunc<OriginalFn>(this, 26)(this);
    }

    bool IsConnected(void) {
        typedef bool(* OriginalFn)(void*);
        return getvfunc<OriginalFn>(this, 27)(this);
    }

    bool IsDrawingLoadingImage(void) {
        typedef bool(* OriginalFn)(void*);
        return getvfunc<OriginalFn>(this, 28)(this);
    }

    const matrix3x4_t& WorldToScreenMatrix(void) {
        typedef const matrix3x4_t&(* OriginalFn)(void*);
        return getvfunc<OriginalFn>(this, 36)(this);
    }

    bool IsTakingScreenshot(void) {
        typedef bool(* OriginalFn)(void*);
        return getvfunc<OriginalFn>(this, 85)(this);
    }

    void ClientCmd_Unrestricted(const char* chCommandString) {
        typedef void(* OriginalFn)(void*, const char *);
        return getvfunc<OriginalFn>(this, 106)(this, chCommandString);
    }
};

class CEntityList
{
public:
    CBaseEntity* GetClientEntity(int index) {
        typedef CBaseEntity*(* OriginalFn)(void*, int);
        return getvfunc<OriginalFn>(this, 3)(this, index);
    }
};

class CDebugOverlay
{
public:
    bool ScreenPosition(const Vector& vIn, Vector& vOut) {
        typedef bool(* OriginalFn)(void*, const Vector&, Vector&);
        return getvfunc<OriginalFn>(this, 11)(this, vIn, vOut);
    }
};

class ISurface
{
public:
    void DrawSetColor(int r, int g, int b, int a) {
        typedef void(* OriginalFn)(void*, int, int, int, int);
        return getvfunc<OriginalFn>(this, 14)(this, r, g, b, a);
    }

    void DrawFilledRect(int x0, int y0, int x1, int y1) {
        typedef void(* OriginalFn)(void*, int, int, int, int);
        return getvfunc<OriginalFn>(this, 16)(this, x0, y0, x1, y1);
    }

    void DrawOutlinedRect(int x0, int y0, int x1, int y1) {
        typedef void(* OriginalFn)(void*, int, int, int, int);
        return getvfunc<OriginalFn>(this, 18)(this, x0, y0, x1, y1);
    }

    void DrawLine(int x0, int y0, int x1, int y1) {
        typedef void(* OriginalFn)(void*, int, int, int, int);
        return getvfunc<OriginalFn>(this, 19)(this, x0, y0, x1, y1);
    }

    void DrawPolyLine(int *px, int *py, int numPoints) {
        typedef void(* OriginalFn)(void*, int*, int*, int);
        return getvfunc<OriginalFn>(this, 20)(this, px, py, numPoints);
    }

    void DrawSetTextFont(unsigned long long font) {
        typedef void(* OriginalFn)(void*, unsigned long long);
        return getvfunc<OriginalFn>(this, 23)(this, font);
    }

    void DrawSetTextColor(int r, int g, int b, int a) {
        typedef void(* OriginalFn)(void*, int, int, int, int);
        return getvfunc<OriginalFn>(this, 24)(this, r, g, b, a);
    }

    void DrawSetTextPos(int x, int y) {
        typedef void(* OriginalFn)(void*, int, int);
        return getvfunc<OriginalFn>(this, 26)(this, x, y);
    }

    void DrawPrintText(const wchar_t *text, int textLen) {
        typedef void(* OriginalFn)(void*, const wchar_t *, int, int);
        return getvfunc<OriginalFn>(this, 28)(this, text, textLen, 0);
    }

    void DrawSetTextureRGBA(int id, const unsigned char *rgba, int wide, int tall) {
        typedef void(* OriginalFn)(void*, int, const unsigned char*, int, int);
        return getvfunc<OriginalFn>(this, 37)(this, id, rgba, wide, tall);
    }

    void DrawSetTexture(int id) {
        typedef void(* OriginalFn)(void*, int);
        return getvfunc<OriginalFn>(this, 38)(this, id);
    }

    unsigned long long CreateFont() {
        typedef unsigned long long(* OriginalFn)(void*);
        return getvfunc<OriginalFn>(this, 71)(this);
    }

    void SetFontGlyphSet(unsigned long long &font, const char *FontName, int tall, int weight, int blur, int scanlines, int flags) {
        typedef void(* OriginalFn)(void*, unsigned long long, const char*, int, int, int, int, int, int, int);
        return getvfunc<OriginalFn>(this, 72)(this, font, FontName, tall, weight, blur, scanlines, flags, 0, 0);
    }

    void GetTextSize(unsigned long long font, const wchar_t *text, int &wide, int &tall) {
        typedef void(* OriginalFn)(void*, unsigned long long font, const wchar_t *text, int &wide, int &tall);
        return getvfunc<OriginalFn>(this, 79)(this, font, text, wide, tall);
    }
};

class IPanel
{
public:
    const char *GetName(unsigned long long vguiPanel) {
        typedef const char* (* OriginalFn)(void*, unsigned long long);
        return getvfunc<OriginalFn>(this, 37)(this, vguiPanel);
    }
};

class HLClient
{
public:
    struct RecvProp;
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
        void* m_ArrayLengthProxy;
        void* m_ProxyFn;
        void* m_DataTableProxyFn;
        RecvTable  *m_pDataTable;
        int m_Offset;
        int m_ElementStride;
        int m_nElements;
        const char *m_pParentArrayPropName;
    };

    struct ClientClass {
        void* m_pCreateFn;
        void* m_pCreateEventFn;
        char *m_pNetworkName;
        RecvTable   *m_pRecvTable;
       	ClientClass *m_pNext;
        int m_ClassID;
    };

    ClientClass* GetAllClasses() {
     	typedef ClientClass*(* OriginalFn)(void*);
        return getvfunc<OriginalFn>(this, 8)(this);
    }
};

#endif // SDK_H_INCLUDED
