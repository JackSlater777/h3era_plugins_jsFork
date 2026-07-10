// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "../pch.h"



// Временное хранение клетки.
H3MapItem* TempCell = nullptr;





// Можно ли зайти в триггер объекта
BOOL8 TriggerIsUnmoveable(H3GlobalObjectSettings* objSettings, int terrain)
{
    // 10085530 (hota.dll version 1.7.3)

    if (terrain != eTerrain::WATER)
    {
        return objSettings->cannotEnter;
    }

    // На воде у большинства объектов несещаемые триггеры.
    switch (objSettings->objectID)
    {
    case 0: // Пустое место
    case 3: // Якорь
    case 8: // Лодка
    case 9: // Страж границы
    case 26: // Событие
    case 33: // Гарнизон
    case 34: // Герой
    case 36: // Грааль
    case 43: // Монолит входа
    case 44: // Монолит выхода
    case 45: // Двухсторонний монолит
    case 54: // Монстр
    case 70: // Случайный герой
    case 71: // Случайный монстр
    case 72: // Случайный монстр 1
    case 73: // Случайный монстр 2
    case 74: // Случайный монстр 3
    case 75: // Случайный монстр 4
    case 77: // Случайный город
    case 80: // Святилище
    case 98: // Город
    case 103: // Врата подземного мира
    case 111: // Водоворот
    case 162: // Случайный монстр 5
    case 163: // Случайный монстр 6
    case 164: // Случайный монстр 7
    case 212: // Пограничные ворота
    case 214: // Лагерь героя
    case 215: // Страж задания
        return objSettings->cannotEnter;
    default:
        return true;
        break;
    }
}


_LHF_(LoHook_WaterUnmoveableTriggers_1)
{
    H3MapItem* cell = reinterpret_cast<H3MapItem*>(c->ebx);
    H3GlobalObjectSettings* type = reinterpret_cast<H3GlobalObjectSettings*>(c->edx + c->edi);

    c->return_address = TriggerIsUnmoveable(type, cell->land) != 0
        ? 0x40E24D
        : 0x40E240;

    return NO_EXEC_DEFAULT;
}

_LHF_(LoHook_WaterUnmoveableTriggers_2)
{
    H3MapItem* cell = reinterpret_cast<H3MapItem*>(c->ebx);
    H3GlobalObjectSettings* type = reinterpret_cast<H3GlobalObjectSettings*>(c->ecx + c->edx);

    c->return_address = TriggerIsUnmoveable(type, cell->land) != 0
        ? 0x42E263
        : 0x42E26C;

    return NO_EXEC_DEFAULT;
}

_LHF_(LoHook_WaterUnmoveableTriggers_3)
{
    H3MapItem* cell = reinterpret_cast<H3MapItem*>(c->ebx);
    H3GlobalObjectSettings* type = reinterpret_cast<H3GlobalObjectSettings*>(c->eax + c->ecx);

    char result = TriggerIsUnmoveable(type, cell->land) != 0;

    c->return_address = 8 * result + 0x42E34F;
    return NO_EXEC_DEFAULT;
}

_LHF_(LoHook_WaterUnmoveableTriggers_SaveTempCell)
{
    TempCell = reinterpret_cast<H3MapItem*>(c->eax);

    return EXEC_DEFAULT;
}

_LHF_(LoHook_WaterUnmoveableTriggers_4)
{
    H3GlobalObjectSettings* type = reinterpret_cast<H3GlobalObjectSettings*>(c->edx + 16 * c->ecx);

    c->return_address = TriggerIsUnmoveable(type, TempCell->land) != 0
        ? 0x42F9C7
        : 0x42FA70;

    return NO_EXEC_DEFAULT;
}

_LHF_(LoHook_WaterUnmoveableTriggers_5)
{
    H3GlobalObjectSettings* type = reinterpret_cast<H3GlobalObjectSettings*>(c->eax + c->ecx);

    c->return_address = TriggerIsUnmoveable(type, TempCell->land) != 0
        ? 0x42FB61
        : 0x42FAF2;

    return NO_EXEC_DEFAULT;
}

_LHF_(LoHook_WaterUnmoveableTriggers_6)
{
    H3MapItem* cell = reinterpret_cast<H3MapItem*>(c->ebx);
    H3GlobalObjectSettings* type = reinterpret_cast<H3GlobalObjectSettings*>(c->eax + c->ecx);

    c->return_address = TriggerIsUnmoveable(type, cell->land) != 0
        ? 0x48085A
        : 0x4805D5;

    return NO_EXEC_DEFAULT;
}

_LHF_(LoHook_WaterUnmoveableTriggers_7)
{
    H3MapItem* cell = reinterpret_cast<H3MapItem*>(c->ebx);
    H3GlobalObjectSettings* type = reinterpret_cast<H3GlobalObjectSettings*>(c->eax + c->ecx);
    
    c->return_address = TriggerIsUnmoveable(type, cell->land) != 0
        ? 0x480E15
        : 0x480E48;

    return NO_EXEC_DEFAULT;
}

_LHF_(LoHook_WaterUnmoveableTriggers_8)
{
    H3MapItem* cell = reinterpret_cast<H3MapItem*>(c->edi);

    H3GlobalObjectSettings* type = reinterpret_cast<H3GlobalObjectSettings*>(c->edx + c->ecx);

    if (TriggerIsUnmoveable(type, cell->land))
    {
        c->return_address = 0x4B2A9D;
    }
    else
    {
        c->return_address = 0x4B2A6D;
    }

    return NO_EXEC_DEFAULT;
}

_LHF_(LoHook_WaterUnmoveableTriggers_9)
{
    H3MapItem* cell = reinterpret_cast<H3MapItem*>(c->eax);
    H3GlobalObjectSettings* type = &P_GlobalObjectSettings[cell->objectType];

    c->return_address = TriggerIsUnmoveable(type, cell->land) != 0
        ? 0x4E602B
        : 0x4E6031;

    return NO_EXEC_DEFAULT;
}

_LHF_(LoHook_WaterUnmoveableTriggers_SaveEdi)
{
    TempCell = reinterpret_cast<H3MapItem*>(c->edi);

    return EXEC_DEFAULT;
}

_LHF_(LoHook_WaterUnmoveableTriggers_10)
{
    H3GlobalObjectSettings* type = reinterpret_cast<H3GlobalObjectSettings*>(c->edx + c->ecx);

    if (TriggerIsUnmoveable(type, TempCell->land))
    {
        c->eax = (c->eax & ~0xFF);
    }
    else
    {
        c->eax = (c->eax & ~0xFF) | 1;
    }

    return NO_EXEC_DEFAULT;
}


void WaterObjectsPassability()
{
    // Непроходимые клетки на воде (1).
    _PI->WriteLoHook(0x40E23A, LoHook_WaterUnmoveableTriggers_1);
    // Непроходимые клетки на воде (2).
    _PI->WriteLoHook(0x42E25D, LoHook_WaterUnmoveableTriggers_2);
    // Непроходимые клетки на воде (3).
    _PI->WriteLoHook(0x42E349, LoHook_WaterUnmoveableTriggers_3);
    // Сохраняем клетку.
    _PI->WriteLoHook(0x42F9A2, LoHook_WaterUnmoveableTriggers_SaveTempCell);
    // Непроходимые клетки на воде (4).
    _PI->WriteLoHook(0x42F9B8, LoHook_WaterUnmoveableTriggers_4);
    // Непроходимые клетки на воде (5).
    _PI->WriteLoHook(0x42FAEC, LoHook_WaterUnmoveableTriggers_5);
    // Непроходимые клетки на воде (6).
    _PI->WriteLoHook(0x480850, LoHook_WaterUnmoveableTriggers_6);
    // Непроходимые клетки на воде (7).
    _PI->WriteLoHook(0x480E0F, LoHook_WaterUnmoveableTriggers_7);
    // Непроходимые клетки на воде (8).
    _PI->WriteLoHook(0x4B2A67, LoHook_WaterUnmoveableTriggers_8);
    // Непроходимые клетки на воде (9).
    _PI->WriteLoHook(0x4E6019, LoHook_WaterUnmoveableTriggers_9);
    // Непроходимые клетки на воде (сохраняем edi).
    _PI->WriteLoHook(0x56AE2E, LoHook_WaterUnmoveableTriggers_SaveEdi);
    // Непроходимые клетки на воде (10).
    _PI->WriteLoHook(0x56B207, LoHook_WaterUnmoveableTriggers_10);
}
