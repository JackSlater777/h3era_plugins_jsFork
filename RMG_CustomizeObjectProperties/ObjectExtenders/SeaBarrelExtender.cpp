#include "../pch.h"
#include "SeaBarrelExtender.h"

namespace seaBarrel
{

SeaBarrelExtender::SeaBarrelExtender()
    : H3PickupableObject(
        globalPatcher->CreateInstance("EraPlugin.SeaBarrelExtender.daemon_n"))
{
    objectType = extender::HOTA_PICKUPABLE_OBJECT_TYPE;
    objectSubtype = SEA_BARREL_OBJECT_SUBTYPE;
    CreatePatches();
}

SeaBarrelExtender::~SeaBarrelExtender()
{
}

BOOL SeaBarrelExtender::SetAiMapItemWeight(
    H3MapItem *mapItem, H3Hero *hero, const H3Player *player,
    int &aiMapItemWeight, int* moveDistance, const H3Position pos) const noexcept
{
    if (auto objSetup = H3MapItemSeaBarrel::GetSeaBarrel(mapItem))
    {
        aiMapItemWeight = (int)(
            (player->aIPlayer.resourceImportance[3]
            + player->aIPlayer.resourceImportance[1]
            + player->aIPlayer.resourceImportance[4]
            + player->aIPlayer.resourceImportance[5])
            * 0.9);

        return true;
    }

    return false;
}

BOOL SeaBarrelExtender::VisitMapItem(H3Hero *hero, H3MapItem *mapItem, const H3Position pos,
                                  const BOOL isHuman) const noexcept
{
    if (const auto seaBarrel = H3MapItemSeaBarrel::GetSeaBarrel(mapItem))
    {
        int resType = seaBarrel->resType;
        int resQty = seaBarrel->resQty;
        
        if (resQty)
        {
            if (isHuman)
            {
                FASTCALL_12(void, 0x4F6C00, SeaBarrelExtender::GetVisitingMessage().String(),
                    1, -1, -1, resType, resQty, -1, 0, -1, 0, -1, -777);
            }
            // add resource
            THISCALL_3(void, 0x4E3870, hero, resType, resQty);
        }
        else if (isHuman)
        {
            FASTCALL_12(void, 0x4F6C00, SeaBarrelExtender::GetEmptyMessage().String(),
                1, -1, -1, -1, 0, -1, 0, -1, 0, -1, -777);
        }

        // Delete the object
        THISCALL_4(void, 0x49DDE0, P_AdventureManager->Get(), mapItem, pos.Mixed(), isHuman);
        
        return true;
    }

    return false;
}

BOOL SeaBarrelExtender::InitNewGameMapItemSetup(H3MapItem *mapItem) const noexcept
{

    if (const auto seaBarrel = H3MapItemSeaBarrel::GetSeaBarrel(mapItem))
    {
        *seaBarrel = {};
        // Рандомим тип ресурса
        seaBarrel->resType = static_cast<INT16>(rand() % 5); // от 0 до 4 включительно
        // Пустой и с ртутью не надо выравнивать.
        if (seaBarrel->resType > 1)
        {
            seaBarrel->resType += 1;
        }
        // Если бочка не пустая, рандомим количество ресурсов
        //seaBarrel->resQty = 0;
        if (seaBarrel->resType > 0)
        {
            seaBarrel->resQty = static_cast<INT16>(3 + rand() % 4); // от 3 до 6 включительно
        }
        
        return true;
    }

    return false;
}

BOOL SeaBarrelExtender::SetHintInH3TextBuffer(H3MapItem* mapItem, const H3Hero* hero, const int playerId, BOOL isRightClick) const noexcept
{
    if (H3MapItemSeaBarrel::GetSeaBarrel(mapItem))
    {
        H3String objName = RMGObjectInfo::GetObjectName(mapItem);
        sprintf(h3_TextBuffer, "%s", objName.String());

        return true;
    }

    return false;
}

void SeaBarrelExtender::CreatePatches()
{
    if (!m_isInited)
    {
        m_isInited = true;
    }
}

inline H3MapItemSeaBarrel* H3MapItemSeaBarrel::GetSeaBarrel(H3MapItem *mapItem) noexcept
{
    if (mapItem && mapItem->objectType == extender::HOTA_PICKUPABLE_OBJECT_TYPE &&
        mapItem->objectSubtype == SEA_BARREL_OBJECT_SUBTYPE)
    {
        return reinterpret_cast<H3MapItemSeaBarrel*>(&mapItem->setup);
    }

    return nullptr;
}

H3RmgObjectGenerator* SeaBarrelExtender::CreateRMGObjectGen(const RMGObjectInfo &objectInfo) const noexcept
{
    if (objectInfo.type == extender::HOTA_PICKUPABLE_OBJECT_TYPE && objectInfo.subtype == SEA_BARREL_OBJECT_SUBTYPE)
    {
        return extender::ObjectExtenderManager::CreateDefaultH3RmgObjectGenerator(objectInfo);
    }
    return nullptr;
}

SeaBarrelExtender* SeaBarrelExtender::instance = nullptr;

SeaBarrelExtender& SeaBarrelExtender::Get()
{
    if (!instance)
        instance = new SeaBarrelExtender();
    return *instance;
}
}
