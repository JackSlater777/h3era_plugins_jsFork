#include "../pch.h"
#include "JetsamExtender.h"

namespace jetsam
{

JetsamExtender::JetsamExtender() : ObjectExtender(globalPatcher->CreateInstance("EraPlugin.JetsamExtender.daemon_n"))
{
    objectType = extender::HOTA_PICKUPABLE_OBJECT_TYPE;
    objectSubtype = JETSAM_OBJECT_SUBTYPE;
    CreatePatches();
}

JetsamExtender::~JetsamExtender()
{
}

BOOL JetsamExtender::SetAiMapItemWeight(H3MapItem *mapItem, H3Hero *hero, const H3Player *player,
                                        int &aiMapItemWeight, int* moveDistance, const H3Position pos) const noexcept
{
    if (auto objSetup = H3MapItemJetsam::GetJetsam(mapItem))
    {
        aiMapItemWeight = (int)(player->aIPlayer.resourceImportance[2] * DoubleAt(0x63AC48)
            + player->aIPlayer.resourceImportance[6] * DoubleAt(0x6405A8));

        return true;
    }

    return false;
}

BOOL JetsamExtender::VisitMapItem(H3Hero *hero, H3MapItem *mapItem, const H3Position pos,
                                  const BOOL isHuman) const noexcept
{
    if (const auto seaBarrel = H3MapItemJetsam::GetJetsam(mapItem))
    {
        switch (mapItem->setup)
        {
        case 0:
            if (isHuman)
            {
                FASTCALL_12(void, 0x4F6C00, JetsamExtender::GetVisitedMessage().String(),
                    1, -1, -1, -1, 0, -1, 0, -1, 0, -1, -777);
            }  
            break;

        case 1:
            if (isHuman)
            {
                FASTCALL_12(void, 0x4F6C00, JetsamExtender::GetVisitMessage().String(),
                    1, -1, -1, eResource::ORE, 5, -1, 0, -1, 0, -1, -777);
            }
            // add resource
            THISCALL_3(void, 0x4E3870, hero, eResource::ORE, 5);
            break;

        case 2:
            if (isHuman)
            {
                FASTCALL_12(void, 0x4F6C00, JetsamExtender::GetVisitMessageState2().String(),
                    1, -1, -1, eResource::ORE, 5, eResource::GOLD, 200, -1, 0, -1, -777);
            }
            // add resource
            THISCALL_3(void, 0x4E3870, hero, eResource::ORE, 5);
            THISCALL_3(void, 0x4E3870, hero, eResource::GOLD, 200);
            break;

        case 3:
            if (isHuman)
            {
                FASTCALL_12(void, 0x4F6C00, JetsamExtender::GetVisitMessageState3().String(),
                    1, -1, -1, eResource::ORE, 10, eResource::GOLD, 500, -1, 0, -1, -777);
            }
            // add resource   
            THISCALL_3(void, 0x4E3870, hero, eResource::ORE, 10);
            THISCALL_3(void, 0x4E3870, hero, eResource::GOLD, 500);
            break;

        default:
            break;
        }

        // Delete the object
        THISCALL_4(void, 0x49DDE0, P_AdventureManager->Get(), mapItem, pos.Mixed(), 1);
        
        return true;
    }

    return false;
}

BOOL JetsamExtender::InitNewGameMapItemSetup(H3MapItem *mapItem) const noexcept
{

    if (const auto jetsam = H3MapItemJetsam::GetJetsam(mapItem))
    {
        *jetsam = {};
        // Рандомим тип ресурса
        jetsam->state = rand() % 4; // от 0 до 3 включительно
        
        return true;
    }

    return false;
}

BOOL JetsamExtender::SetHintInH3TextBuffer(H3MapItem* mapItem, const H3Hero* hero, const int playerId, BOOL isRightClick) const noexcept
{
    if (H3MapItemJetsam::GetJetsam(mapItem))
    {
        H3String objName = RMGObjectInfo::GetObjectName(mapItem);
        sprintf(h3_TextBuffer, "%s", objName.String());

        return true;
    }

    return false;
}

void JetsamExtender::CreatePatches()
{
    if (!m_isInited)
    {
        m_isInited = true;
    }
}

inline H3MapItemJetsam* H3MapItemJetsam::GetJetsam(H3MapItem *mapItem) noexcept
{
    if (mapItem && mapItem->objectType == extender::HOTA_PICKUPABLE_OBJECT_TYPE && mapItem->objectSubtype == JETSAM_OBJECT_SUBTYPE)
    {
        return reinterpret_cast<H3MapItemJetsam*>(&mapItem->setup);
    }

    return nullptr;
}

H3RmgObjectGenerator* JetsamExtender::CreateRMGObjectGen(const RMGObjectInfo &objectInfo) const noexcept
{
    if (objectInfo.type == extender::HOTA_PICKUPABLE_OBJECT_TYPE && objectInfo.subtype == JETSAM_OBJECT_SUBTYPE)
    {
        return extender::ObjectExtenderManager::CreateDefaultH3RmgObjectGenerator(objectInfo);
    }
    return nullptr;
}


JetsamExtender* JetsamExtender::instance = nullptr;

JetsamExtender& JetsamExtender::Get()
{
    if (!instance)
    {
        instance = new JetsamExtender();
    }
    
    return *instance;
}
}
