typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);
CreateInterfaceFn Client;
CreateInterfaceFn Engine;
CreateInterfaceFn VGUI;
CreateInterfaceFn VGUI2;