#include "../pch.h"
#include "TownGateExtender.h"


namespace townGate
{
    TownGateExtender::TownGateExtender()
        : H3ActiveObject<H3MapItemTownGate>(
            "EraPlugin.TownGateExtender.daemon_n",
            extender::HOTA_UNREACHABLE_OBJECT_TYPE,
            TOWN_GATE_OBJECT_SUBTYPE)
    {
    }

    TownGateExtender* TownGateExtender::instance = nullptr;
    TownGateExtender& TownGateExtender::Get()
    {
        if (!instance) instance = new TownGateExtender();
        return *instance;
    }

    int g_townGateTargetTownId = -1;
    BOOL TownGateExtender::VisitMapItem(H3Hero* hero, H3MapItem* mapItem, const H3Position pos,
        const BOOL isHuman) const noexcept
    {
        // Посещается town gate
        if (GetFromMapItem(mapItem))
        {
            if (isHuman)
            {
                // movecost free teleport
                //0041D531 + 3 = C8
                auto patch = _PI->WriteHexPatch(0x41D531 + 3, "00");

                // mana free teleport
                //0041DA0B -> 0041DA2B
                auto patch2 = _PI->WriteJmp(0x41DA0B, 0x41DA2B);

                // patch spell name
                // get new name
                H3String str = H3String::Format("{%s}", RMGObjectInfo::GetObjectName(mapItem)).String();
                LPCSTR objName = str.String();
                // store old name
                LPCSTR spellName = P_Spell[eSpell::TOWN_PORTAL].name;
                // patch
                P_Spell[eSpell::TOWN_PORTAL].name = objName;

                // patch spell def
                Era::RedirectFile("SpellScr.def:0_9.png", "data/pcx/twngatem.png");

                P_MouseManager->SetCursor(eAdvCursor::ARROWPOINTER, eCursor::ADVENTURE);
                P_MouseManager->TurnOn();
                // H3AdventureManager::CastTownPortal
                THISCALL_2(void, 0x41D4E0, P_AdventureManager->Get(), eSecSkillLevel::EXPERT);

                // restore old name
                P_Spell[eSpell::TOWN_PORTAL].name = spellName;
                // restore old def
                Era::RedirectFile("SpellScr.def:0_9.png", "");

                // undo patches
                patch->Destroy();
                patch2->Destroy();
            }
            else
            {
                if (g_townGateTargetTownId > -1)
                {
                    H3Town* targetTown = &P_Game->towns[g_townGateTargetTownId];
                    THISCALL_7(void, 0x41DAB0, P_AdventureManager->Get(), hero, H3Position(targetTown->x, targetTown->y, targetTown->z), 0, 0, 1, 0);
                    g_townGateTargetTownId = -1;
                }
            }
        }

        return false;
    }

    BOOL TownGateExtender::SetAiMapItemWeight(
        H3MapItem* mapItem, H3Hero* hero, const H3Player* player,
        int& aiMapItemWeight, int* moveDistance, const H3Position pos) const noexcept
    {
        if (GetFromMapItem(mapItem))
        {
            H3Game* game = P_Game->Get();
            int playerTeamId = game->GetPlayerTeam(hero->owner);
            g_townGateTargetTownId = -1;

            for (size_t i = 0; i < limits::TOWNS_ON_MAP; i++)
            {
                H3Town* town = &game->towns[i];

                if (town->owner > -1 && town->visitingHero == -1 && playerTeamId == game->GetPlayerTeam(town->owner))
                {
                    // AI::H3Hero::CalculateMapPosWeight
                    int newAiTownVal = FASTCALL_3(int, 0x528520, hero, H3Position(town->x, town->y, town->z), moveDistance);

                    if (newAiTownVal > aiMapItemWeight)
                    {
                        aiMapItemWeight = newAiTownVal;
                        g_townGateTargetTownId = i;
                    }
                }
            }

            return true;
        }

        return false;
    }
}
