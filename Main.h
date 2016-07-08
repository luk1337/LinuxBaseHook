#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <iostream>
#include <dlfcn.h>
#include <vector>
#include <thread>
#include <pthread.h>
#include <chrono>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <wchar.h>
#include "SDK.h"
#include "NetVarManager.h"
#include "Draw.h"

extern HLClient* g_pClient;
extern CEngineClient* g_pEngine;
extern ISurface* g_pSurface;
extern IPanel* g_pPanel;

extern CDraw g_Draw;

#endif // MAIN_H_INCLUDED
