#include <cstdint>
#include <cstdio>
#include <cstring>
#include <thread>
#include "Draw.h"
#include "EntityESP.h"
#include "Hooks.h"
#include "NetVarManager.h"
#include "Utils.h"

// Linux basehook by Atex 6.7.2016
// Do not sell stuff based on this, quite demotivating. Also remember to give credit where it is due.
// Thanks to: n0xius, Cre3per, -napalm- and others who contribute to linux hacking and are cool kids. Ur all awesome to talk to ;)
// If I have forgotten you just hit me up.
// Sorry for the "bad" code. Somewhat intentional to make expanding on this a little harder if ur a complete spastic. For example no class for vmt hooking.

uintptr_t** ppInstance;
uintptr_t*  pNewVMT, *pOldVMT;
uintptr_t   VMTSize;

template<typename T> T CallOriginalPT(int index) {
	return (T)(pOldVMT[index]);
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

            EntityESP::DrawBoxESP(pEnt);
            EntityESP::DrawNameESP(pEnt, i);
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

    Utils::SetupInterfaces();
    Utils::SetupHooks();

    NetVarManager->Initialize();
    NetVarManager->DumpNetvars("/home/luk/.steam/steam/steamapps/common/Counter-Strike Global Offensive/netvars.txt");

    Offsets::GrabOffsets();

    unsigned long int uintPanel = reinterpret_cast<unsigned long long>(g_pPanel);
    DoPTHook(&uintPanel);
}

void __attribute__((constructor)) start() {
    std::thread inithack(inithooks);
    inithack.detach();
}

void __attribute__((destructor)) end() {
}
