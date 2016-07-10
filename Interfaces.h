#ifndef BASEHOOK_INTERFACES_H
#define BASEHOOK_INTERFACES_H

typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);
extern CreateInterfaceFn Client;
extern CreateInterfaceFn Engine;
extern CreateInterfaceFn InputSystem;
extern CreateInterfaceFn MaterialSystem;
extern CreateInterfaceFn Physprops;
extern CreateInterfaceFn StudioRender;
extern CreateInterfaceFn VGUI;
extern CreateInterfaceFn VGUI2;

#endif //BASEHOOK_INTERFACES_H
