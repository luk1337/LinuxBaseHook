// Linux basehook by Atex 6.7.2016
// Do not sell stuff based on this, quite demotivating. Also remember to give credit where it is due.
// Thanks to: n0xius, Cre3per, -napalm- and others who contribute to linux hacking and are cool kids. Ur all awesome to talk to ;)
// If I have forgotten you just hit me up.
// Sorry for the "bad" code. Somewhat intentional to make expanding on this a little harder if ur a complete spastic. For example no class for vmt hooking.

#include "Main.h"

HLClient* g_pClient = NULL;
ISurface* g_pSurface = NULL;
CEntityList* g_pEntityList = NULL;
IPanel* g_pPanel = NULL;
CDebugOverlay* g_pDebugOverlay = NULL;
CEngineClient* g_pEngine = NULL;
CDraw g_Draw;
uintptr_t** ppInstance;
uintptr_t*  pNewVMT, *pOldVMT;
uintptr_t   VMTSize;
typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);

template<typename T> T CallOriginalPT(int index) {
	return (T)(pOldVMT[index]);
}

bool WorldToScreen(const Vector &vOrigin, Vector &vScreen) {
	return (g_pDebugOverlay->ScreenPosition(vOrigin, vScreen));
}

typedef void(*oPaintTraverse)(void*,unsigned long long, bool, bool);
void PaintTraverseHook(void* v1, unsigned long long vguiPanel, bool forceRepaint, bool allowForce) {
    CallOriginalPT<oPaintTraverse>(42)(v1, vguiPanel, forceRepaint, allowForce);

    const char* name = g_pPanel->GetName(vguiPanel);

    if (name && name[0] == 'F' && name[5] == 'O' && name[12] == 'P') {
        static bool bDidOnce = false;

        if(!bDidOnce) {
            g_Draw.InitFont(12, "Tahoma");
            bDidOnce = true;
        }

        CBaseEntity* pLocal = g_pEntityList->GetClientEntity(g_pEngine->GetLocalPlayer());

        if (!pLocal) return;

        for(int i = 0; i < 64; ++i) {
            CBaseEntity* pEnt = g_pEntityList->GetClientEntity(i);

            if (!pEnt ||pEnt == pLocal ||
                    pEnt->GetDormant() || pEnt->GetAlive() || pEnt->GetHealth() <= 0) continue;

            int r, g, b;

            // Esp color by team
            if (pEnt->GetTeamNum() == 2) {
                r = 255;
                g = 0;
                b = 0;
            } else {
                r = 0;
                g = 0;
                b = 255;
            }

            Vector vMax = pEnt->GetCollideable()->OBBMaxs();
            Vector vPos, vPos3D;
            Vector vTop, vTop3D;
            vPos3D = pEnt->GetOrigin();
            vTop3D = vPos3D + Vector(0, 0, vMax.z);

            if (!WorldToScreen(vPos3D, vPos) && !WorldToScreen(vTop3D, vTop)) {
                CEngineClient::player_info_t pInfo;
                g_pEngine->GetPlayerInfo(i, &pInfo);

                // Calculate the box width and height
                float height = (vPos.y - vTop.y);
                float width = height / 4.f;

                // Draw name ESP
                g_Draw.DrawString(true, vTop.x, vTop.y, r, g, b, 255, pInfo.name);

                // Draw box ESP
                g_Draw.DrawOutlinedRect(vTop.x - width, vTop.y, width * 2, height, r, g, b, 255);
            }
        }
    }
}

void DoPTHook(uintptr_t *Instance) {
    ppInstance = (*(uintptr_t***)Instance);
    pOldVMT = *ppInstance;
    uintptr_t index = 0;

    for(index = 0; pOldVMT[index]; ++index) {
        if (pOldVMT[index] == 0) break;
    }

    VMTSize = index;

    if (VMTSize > 0) {
	    pNewVMT = new uintptr_t[VMTSize];
	    memcpy(pNewVMT, pOldVMT, sizeof(uintptr_t) * VMTSize);

	    *ppInstance = (pNewVMT);

        if (pNewVMT && pOldVMT && index <= VMTSize) {
            pNewVMT[42] = (uintptr_t)PaintTraverseHook;
        }
    }
}

void inithooks() {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    CreateInterfaceFn Client = NULL;
    CreateInterfaceFn Engine = NULL;
    CreateInterfaceFn VGUI = NULL;
    CreateInterfaceFn VGUI2 = NULL;

    Client = (CreateInterfaceFn)dlsym(dlopen("./csgo/bin/linux64/client_client.so",RTLD_NOW),"CreateInterface");
    Engine = (CreateInterfaceFn)dlsym(dlopen("./bin/linux64/engine_client.so",RTLD_NOW),"CreateInterface");
    VGUI = (CreateInterfaceFn)dlsym(dlopen("./bin/linux64/vguimatsurface_client.so",RTLD_NOW), "CreateInterface");
    VGUI2 = (CreateInterfaceFn)dlsym(dlopen("./bin/linux64/vgui2_client.so", RTLD_NOW), "CreateInterface");

    g_pClient = (HLClient*)Client("VClient017", NULL);
    g_pEntityList = (CEntityList*)Client("VClientEntityList003", NULL);
    g_pEngine = (CEngineClient*)Engine("VEngineClient013", NULL);
    g_pDebugOverlay = (CDebugOverlay*)Engine("VDebugOverlay004", NULL);
    g_pSurface = (ISurface*)VGUI("VGUI_Surface031", NULL);
    g_pPanel = (IPanel*)VGUI2("VGUI_Panel009", NULL);

    NetVarManager->DumpNetvars("/home/luk/.steam/steam/steamapps/common/Counter-Strike Global Offensive/netvars.txt");

    unsigned long int uintPanel = reinterpret_cast<unsigned long long>(g_pPanel);
    DoPTHook(&uintPanel);
}

void __attribute__((constructor)) start() {
    std::thread inithack(inithooks);
    inithack.detach();
}

void __attribute__((destructor)) end() {
}
