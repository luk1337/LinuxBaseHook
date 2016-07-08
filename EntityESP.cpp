#include "EntityESP.h"
#include "Utils.h"
#include "Vector.h"
#include "Hooks.h"
#include "Draw.h"

void EntityESP::DrawBoxESP(CBaseEntity* entity) {
    int r, g, b;

    // Esp color by team
    if (entity->GetTeamNum() == 2) {
        r = 255;
        g = 0;
        b = 0;
    } else {
        r = 0;
        g = 0;
        b = 255;
    }

    Vector vMax = entity->GetCollideable()->OBBMaxs();
    Vector vPos, vPos3D;
    Vector vTop, vTop3D;
    vPos3D = entity->GetOrigin();
    vTop3D = vPos3D + Vector(0, 0, vMax.z);

    if (!Utils::WorldToScreen(vPos3D, vPos) && !Utils::WorldToScreen(vTop3D, vTop)) {
        // Calculate the box width and height
        float height = (vPos.y - vTop.y);
        float width = height / 4.f;

        // Draw box ESP
        g_Draw.DrawOutlinedRect(vTop.x - width, vTop.y, width * 2, height, r, g, b, 255);
    }
}

void EntityESP::DrawNameESP(CBaseEntity* entity, int index) {
    int r = 255, g = 255, b = 255;

    Vector vMax = entity->GetCollideable()->OBBMaxs();
    Vector vPos, vPos3D;
    Vector vTop, vTop3D;
    vPos3D = entity->GetOrigin();
    vTop3D = vPos3D + Vector(0, 0, vMax.z);

    if (!Utils::WorldToScreen(vPos3D, vPos) && !Utils::WorldToScreen(vTop3D, vTop)) {
        CEngineClient::player_info_t pInfo;
        g_pEngine->GetPlayerInfo(index, &pInfo);

        // Calculate the box width and height
        float height = (vPos.y - vTop.y);
        float width = height / 4.f;

        // Draw name ESP
        g_Draw.DrawString(true, vTop.x, vTop.y, r, g, b, 255, pInfo.name);
    }
}