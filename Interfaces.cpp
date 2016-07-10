typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);

CreateInterfaceFn Client;
CreateInterfaceFn Engine;
CreateInterfaceFn InputSystem;
CreateInterfaceFn MaterialSystem;
CreateInterfaceFn Physprops;
CreateInterfaceFn StudioRender;
CreateInterfaceFn VGUI2;
CreateInterfaceFn VGUI;