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




////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

// Является ли текущий диалог диалогом таверны на воде.
bool IsWaterTavern = false;

// Пока не ясно, что это
bool IsBoatCreation = false;










// Посадка героя в лодку на том месте, где он стоит (герой должен быть на карте и не в лодке, если лодки там же нет, она создаётся, если есть - она должна там стоять с начала игры).
int HeroPlaceToBoat(H3Game* game, H3Hero* hero, char boatSubtype, H3Position coords, char playerId, bool notAddToReplayTurn)
{
    // Преобразуем координаты.
    int x, y, z;
    H3Position::UnpackXYZ(coords, x, y, z);

    // Если надо - добавляем информацию для просмотра хода и оппонента онлайн.
    if (!notAddToReplayTurn)
    {
        sub_10145120(game, 4);

        // Делаем это только при постановке самого героя.

        // Информация для оппонента.
        //PlaceBoat_SendMsg(game, coords, o_ActivePlayerID, boat_subtype);

        // Добавляем информмацию для просмотра хода.
        //CALL_3(void, __thiscall, 0x49C570, this, boat, coords);
    }

    IsBoatCreation = true;
    int boat_ix = THISCALL_7(int, 0x4BAF10, game, x, y, z, playerId, notAddToReplayTurn, boatSubtype);
    IsBoatCreation = false;

    // Не удалсь создать лодку.
    if (boat_ix < 0)
    {
        H3Boat boatObj;
        THISCALL_1(void, 0x4D76E0, &boatObj); // H3Boat::Ctor
        boatObj.exists = 0;
        game->boats.Insert(game->boats.end(), boatObj);

        IsBoatCreation = true;
        int boat_ix = THISCALL_7(int, 0x4BAF10, game, x, y, z, playerId, notAddToReplayTurn, boatSubtype);
        IsBoatCreation = false;

        if (boat_ix < 0)
        {
            return 0;
        }
    }

    H3Boat* boat = &game->boats[boat_ix];

    // Сажаем героя в лодку.
    // Убираем лодку (или героя) из информации клетки.
    THISCALL_1(void, 0x4D7950, boat);

    // Если надо - добавляем информацию для просмотра хода и оппонента онлайн.
    if (!notAddToReplayTurn)
    {
        MEMORY[0x49C1D0](game, boat, 1, hero->id); // H3Game::ReplayAction_HideBoat
        sub_10145120(game, 2);
        v11 = 1;
        MEMORY[0x49C790](game, hero, playerId, coords, v11);// H3Game::ReplayAction_PlaceHero
    }

    // Настраиваем героя.
    hero->flags |= 0x40000; // Герой в лодке
    hero->flyPower = -1; // Герой больше не в полёте
    hero->waterwalkPower = -1; // Герой больше не ходит по воде

    // Пересчитываем ходьбу героя в водную (new_mp = old_mp*new_max/old_max).
    if (!(hero->temp_mod_flags & 0x1000000))
    {
        _int_ new_max = CALL_2(_int32_, __thiscall, 0x4E4C00, hero, TRUE);
        if (hero->movement_points_max)
        {
            hero->movement_points = hero->movement_points * new_max / hero->movement_points_max;
        }
        else
        {
            hero->movement_points = 0;
        }
        hero->movement_points_max = new_max;
    }

    // Настраиваем лодку.
    boat->Field<_int32_>(32) = hero->id; // Герой в лодке
    boat->Field<_bool8_>(36) = TRUE; // Внутри есть герой
    boat->Field<_int8_>(28) = playerId; // Владелец лодки





    return TRUE;
}





















// При посещении водной таверны, запоминаем, что посещение длится сейчас.
void __stdcall HiHook_ObjTavernVisit_SetTavernIfWater(HiHook* h, _dword_ coords)
{
    // Определяем водную таверну (по клетке, где она стоит).
    if (THISCALL_2(H3MapItem*, 0x412B30, P_AdventureManager->Get(), coords)->land == 8)
    {
        IsWaterTavern = true;
    }

    // Обрабатываем посещение таверны.
    STDCALL_1(void, h->GetDefaultFunc(), coords);

    // Посещение водной таверны завершено.
    IsWaterTavern = false;
}

// Запрещаем покупку героя при отсутствии лодок.
_LHF_(LoHook_TavernDialog_RestrictIfNoBoats)
{
    // Если таверна на воде и лодок уже максимальное число, запрещаем покупку героя.
    if (IsWaterTavern && THISCALL_1(int, 0x4CCA90, P_Game->Get()) >= 64)
    {
        c->return_address = 0x5D8624;
        return NO_EXEC_DEFAULT;
    }
    // Иначе - как обычно.
    else
    {
        return EXEC_DEFAULT;
    }
}

// При создании героя во внешней таверне сажаем его в лодку, если это на воде.
void __stdcall HiHook_PlaceHeroWater_ObjTavern(
    HiHook* h, H3Hero* this_, int playerId, 
    _dword_ coords, bool resetFlags)
{
    // Клетка - водная...
    if (THISCALL_2(H3MapItem*, 0x412B30, P_AdventureManager->Get(), coords)->land == 8)
    {
        // Посадка героя в лодку.
        P_Game->HeroPlaceToBoat(this_, ((_int32_*)CasShipTable)[*(_int32_*)(HeroClassesTable + 64 * this_->_class)], coords, player_id, FALSE);

        // Не стираем флаг лодки.
        if (reset_temp_mod_flags)
        {
            // Сбрасываем флаг побега.
            this_->temp_mod_flags &= ~HTF_SURRENDED;

            // В самой постановке не будем сбрасывать флаги.
            resetFlags = false;
        }
    }

    // Создание героя.
    CALL_4(void, __thiscall, h->GetDefaultFunc(), this_, playerId, coords, reset_temp_mod_flags);
}

void WaterTaverns()
{
    // При посещении водной таверны, запоминаем, что посещение длится сейчас.
    _PI->WriteHiHook(0x5d8290, SPLICE_, EXTENDED_, STDCALL_, HiHook_ObjTavernVisit_SetTavernIfWater);

    // Запрещаем покупку героя при отсутствии лодок.
    _PI->WriteLoHook(0x5d860d, LoHook_TavernDialog_RestrictIfNoBoats);

    // При создании героя внешней таверной сажаем его в лодку, если это на воде.
    _PI->WriteHiHook(0x4d7b4b, CALL_, EXTENDED_, THISCALL_, HiHook_PlaceHeroWater_ObjTavern);
}


void WaterObjects()
{
    WaterObjectsPassability();
    WaterTaverns();
}
