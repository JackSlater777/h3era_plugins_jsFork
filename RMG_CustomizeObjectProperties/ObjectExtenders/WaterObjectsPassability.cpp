// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "../pch.h"


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





void WaterObjectsPassability()
{
    // Непроходимые клетки на воде (1).
    _PI->WriteLoHook(0x40E23A, LoHook_WaterUnmoveableTriggers_1);
    // Непроходимые клетки на воде (2).
    _PI->WriteLoHook(0x42E25D, LoHook_WaterUnmoveableTriggers_2);
    // Непроходимые клетки на воде (3).
    _PI->WriteLoHook(0x42E349, LoHook_WaterUnmoveableTriggers_3);
}
