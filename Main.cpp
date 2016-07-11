#include <cstdint>
#include <cstdio>
#include <cstring>
#include <thread>
#include <zconf.h>
#include <pwd.h>
#include "NetVarManager.h"

// Linux basehook by Atex 6.7.2016
// Do not sell stuff based on this, quite demotivating. Also remember to give credit where it is due.
// Thanks to: n0xius, Cre3per, -napalm- and others who contribute to linux hacking and are cool kids. Ur all awesome to talk to ;)
// If I have forgotten you just hit me up.
// Sorry for the "bad" code. Somewhat intentional to make expanding on this a little harder if ur a complete spastic. For example no class for vmt hooking.

void inithooks() {
    std::this_thread::sleep_for(std::chrono::seconds(5));

    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;

    char* netvarsOutput;
    asprintf(&netvarsOutput, "%s/%s", homedir, ".steam/steam/steamapps/common/Counter-Strike Global Offensive/netvars.txt");

    Utils::SetupInterfaces();
    Utils::SetupHooks();

    NetVarManager->Initialize();
    NetVarManager->DumpNetvars(netvarsOutput);

    Offsets::GrabOffsets();
}

void __attribute__((constructor)) start() {
    std::thread inithack(inithooks);
    inithack.detach();
}

void __attribute__((destructor)) end() {
}
