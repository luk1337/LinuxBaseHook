#ifndef BASEHOOK_UTILS_H
#define BASEHOOK_UTILS_H

#include "random"
#include "Vector.h"

namespace Utils {
    extern bool WorldToScreen(const Vector &vOrigin, Vector &vScreen);
    extern void SetupInterfaces();
    extern void SetupHooks();

    inline void**& GetVTable(void* inst, size_t offset = 0) {
        return *reinterpret_cast<void***>((size_t)inst + offset);
    }

    inline const void** GetVTable(const void* inst, size_t offset = 0) {
        return *reinterpret_cast<const void***>((size_t)inst + offset);
    }

    template<typename Fn>
    inline Fn GetVFunc(const void* inst, size_t index, size_t offset = 0) {
        return reinterpret_cast<Fn>(GetVTable(inst, offset)[index]);
    }
};

#endif //BASEHOOK_UTILS_H
