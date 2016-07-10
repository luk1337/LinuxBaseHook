#include "Hooks.h"
#include "EntityESP.h"
#include "Draw.h"

PaintTraverseFn oPaintTraverse;

void Hooks::PaintTraverse(void* v1, unsigned long long vguiPanel, bool forceRepaint, bool allowForce) {
    oPaintTraverse(v1, vguiPanel, forceRepaint, allowForce);

    const char* name = g_pPanel->GetName(vguiPanel);
    if (name && name[0] == 'M' && name[2] == 't') {
        static bool bDidOnce = false;
        if(!bDidOnce) {
            g_Draw.InitFont(12, "Tahoma");
            bDidOnce = true;
        }

        // Draw watermark
        g_Draw.DrawString(false, 5, 5, 0, 0, 255, 255, "Basehook :3");

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
