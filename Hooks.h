#ifndef BASEHOOK_HOOKS_H
#define BASEHOOK_HOOKS_H

#include "SDK.h"
#include "Draw.h"

extern HLClient* g_pClient;
extern CDebugOverlay* g_pDebugOverlay;
extern CEngineClient* g_pEngine;
extern CEntityList* g_pEntityList;
extern ISurface* g_pSurface;
extern IPanel* g_pPanel;

extern CDraw g_Draw;

using PaintTraverseFn = void(*)(void*, unsigned long long, bool, bool);
extern PaintTraverseFn oPaintTraverse;

namespace Hooks {
    extern void PaintTraverse(void* v1, unsigned long long vguiPanel, bool forceRepaint, bool allowForce);
}

#endif //BASEHOOK_HOOKS_H
