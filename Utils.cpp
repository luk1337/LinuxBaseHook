#include <dlfcn.h>
#include "Utils.h"
#include "Interfaces.h"
#include "Hooks.h"
#include "VTableHook.h"

bool Utils::WorldToScreen(const Vector &vOrigin, Vector &vScreen) {
    return g_pDebugOverlay->ScreenPosition(vOrigin, vScreen);
}

void Utils::SetupInterfaces() {
    Client = (CreateInterfaceFn)dlsym(dlopen("./csgo/bin/linux64/client_client.so", RTLD_NOW), "CreateInterface");
    Engine = (CreateInterfaceFn)dlsym(dlopen("./bin/linux64/engine_client.so", RTLD_NOW), "CreateInterface");
    VGUI = (CreateInterfaceFn)dlsym(dlopen("./bin/linux64/vguimatsurface_client.so", RTLD_NOW), "CreateInterface");
    VGUI2 = (CreateInterfaceFn)dlsym(dlopen("./bin/linux64/vgui2_client.so", RTLD_NOW), "CreateInterface");
}

void Utils::SetupHooks() {
    g_pClient = (HLClient*)Client("VClient017", NULL);
    g_pEntityList = (CEntityList*)Client("VClientEntityList003", NULL);
    g_pEngine = (CEngineClient*)Engine("VEngineClient013", NULL);
    g_pDebugOverlay = (CDebugOverlay*)Engine("VDebugOverlay004", NULL);
    g_pSurface = (ISurface*)VGUI("VGUI_Surface031", NULL);
    g_pPanel = (IPanel*)VGUI2("VGUI_Panel009", NULL);

    oPaintTraverse = (PaintTraverseFn)vtablehook_hook(g_pPanel, (void*)Hooks::PaintTraverse, 42);
}