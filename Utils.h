#ifndef BASEHOOK_UTILS_H
#define BASEHOOK_UTILS_H

#include "random"
#include "Vector.h"

namespace Utils {
    extern bool WorldToScreen(const Vector &vOrigin, Vector &vScreen);
    extern void SetupInterfaces();
    extern void SetupHooks();
};

#endif //BASEHOOK_UTILS_H
