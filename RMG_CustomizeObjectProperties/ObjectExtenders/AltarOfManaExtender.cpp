#include "../pch.h"
#include "AltarOfManaExtender.h"


namespace altarOfMana
{
    int g_AltarOfMana = 0;

    _LHF_(LoHook_00560572)
    {
        if (g_AltarOfMana)
            c->eax = 3;

        return EXEC_DEFAULT;
    }

    _LHF_(LoHook_0056146a)
    {
        if (!g_AltarOfMana)
            return EXEC_DEFAULT;

        c->esp -= 4;
        *(DWORD*)c->esp = (_ptr_)"altrmana.pcx";
        return NO_EXEC_DEFAULT;
    }

    _LHF_(LoHook_00561e71)
    {
        if (!g_AltarOfMana)
            return EXEC_DEFAULT;

        c->return_address = 0x5621AF;
        return NO_EXEC_DEFAULT;
    }

    _LHF_(LoHook_00563507)
    {
        if (!g_AltarOfMana)
            return EXEC_DEFAULT;

        c->return_address = 0x563516;
        return NO_EXEC_DEFAULT;
    }

    _LHF_(LoHook_00564eec)
    {
        if (!g_AltarOfMana)
            return 1;

        c->edx = *(DWORD*)(c->esi + 120) + c->edi * *(DWORD*)(c->ebp + 12) / 10 - c->edi * *(DWORD*)(c->ebx + 312) / 10;
        c->edi = *(DWORD*)(c->ebp + 12);

        c->return_address = 0x564F38;
        return NO_EXEC_DEFAULT;
    }

    _LHF_(LoHook_005630af)
    {
        return g_AltarOfMana == 0;
    }

    _LHF_(LoHook_005630e1)
    {
        if (!g_AltarOfMana)
            return EXEC_DEFAULT;

        c->eax = static_cast<INT32>(c->edx) / 10;

        c->return_address = 0x5630F2;
        return NO_EXEC_DEFAULT;
    }


    void AltarOfManaExtender::CreatePatches()
    {
        static bool patchesCreated = false;
        if (patchesCreated) return;

        // H3SacrificeDlg::Ctor - переключаем режим на жертвование существ
        _PI->WriteLoHook(0x560572, LoHook_00560572);

        // H3SacrificeDlg::SacrificeCreaturesCtor
        // Подменяем задник
        _PI->WriteLoHook(0x56146a, LoHook_0056146a);
        // Перепрыгиваем через создание кнопок артефактов
        _PI->WriteLoHook(0x561e71, LoHook_00561e71);

        // H3SacrifaceDlg::CreaturesView::Prepare - перепрыгиваем виртуальную функцию?
        _PI->WriteLoHook(0x563507, LoHook_00563507);

        // Хз че за функция - че-то с опытом
        _PI->WriteLoHook(0x564eec, LoHook_00564eec);

        // Хз че за функция
        // Скип
        _PI->WriteLoHook(0x5630af, LoHook_005630af);
        // Количество даваемой маны = опыт / 10
        _PI->WriteLoHook(0x5630e1, LoHook_005630e1);



        patchesCreated = true;
    }

    AltarOfManaExtender::AltarOfManaExtender()
        : H3ActiveObject<H3MapItemAltarOfMana>(
            "EraPlugin.AltarOfManaExtender.daemon_n",
            extender::HOTA_UNREACHABLE_OBJECT_TYPE,
            ALTAR_OF_MANA_OBJECT_SUBTYPE)
    {
        CreatePatches();
    }

    AltarOfManaExtender* AltarOfManaExtender::instance = nullptr;
    AltarOfManaExtender& AltarOfManaExtender::Get()
    {
        if (!instance) instance = new AltarOfManaExtender();
        return *instance;
    }

    BOOL AltarOfManaExtender::VisitMapItem(H3Hero* hero, H3MapItem* mapItem, const H3Position pos,
        const BOOL isHuman) const noexcept
    {
        if (GetFromMapItem(mapItem))
        {
            if (isHuman)
            {
                
            }

            return true;
        }

        return false;
    }
}
