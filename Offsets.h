//
// Created by luk on 7/10/16.
//

#ifndef BASEHOOK_OFFSETS_H
#define BASEHOOK_OFFSETS_H

struct COffsets {
    int m_iHealth;
    int m_iTeamNum;
    int m_bDormant;
    int m_bGunGameImmunity;
    int m_lifeState;
    int m_fFlags;
    int m_Local;
    int m_nTickBase;
    int m_nForceBone;
    int m_mBoneMatrix;
    int m_nModelIndex;
    int m_viewPunchAngle;
    int m_aimPunchAngle;
    int m_vecOrigin;
    int m_VecMins;
    int m_VecMaxs;
    int m_vecViewOffset;
    int m_vecVelocity;
    int m_szLastPlaceName;
    int m_flNextPrimaryAttack;
    int m_hActiveWeapon;
    int m_fAccuracyPenalty;
    int m_Collision;
    int m_iShotsFired;
    int m_iWeaponID;
    int m_nMoveType;
    int m_nHitboxSet;
    int m_bHasHelmet;
    int m_ArmorValue;
    int m_CollisionGroup;
    int m_iClass;
    int m_bIsBroken;
    int m_angEyeAngles;
    int m_hOwnerEntity;
    int m_flC4Blow;
    int m_flFlashDuration;
    int m_iGlowIndex;

    int m_nFallbackPaintKit;
    int m_nFallbackSeed;
    int m_flFallbackWear;
    int m_nFallbackStatTrak;
    int m_AttributeManager;
    int m_Item;
    int m_iEntityLevel;
    int m_iItemIDHigh;
    int m_iItemIDLow;
    int m_iAccountID;
    int m_iEntityQuality;
    int m_OriginalOwnerXuidLow;
    int m_OriginalOwnerXuidHigh;
    int m_iItemDefinitionIndex;
    int m_iClip1;
    int m_bReloadVisuallyComplete;
};
extern COffsets offsets;

namespace Offsets {
    extern void GrabOffsets();
}

#endif //BASEHOOK_OFFSETS_H
