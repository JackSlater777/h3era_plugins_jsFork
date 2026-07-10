#include "pch.h"


// JSON-ключи текстов объектов
LPCSTR const VISIT_MESSAGE = "RMG.objectGeneration.%d.%d.text.visit";
LPCSTR const VISITED_MESSAGE = "RMG.objectGeneration.%d.%d.text.visited"; // разграблено/посещено и т.д.
LPCSTR const CANNOT_VISIT_MESSAGE = "RMG.objectGeneration.%d.%d.text.cannotVisit";
LPCSTR const HINT_MESSAGE = "RMG.objectGeneration.%d.%d.text.hint";


// Настройка HD-mod
bool skipMapMessage = false;





void Globals_Init()
{
    skipMapMessage = globalPatcher->VarValue<int>("HD.UI.AdvMgr.SkipMapMsgs");
    int a = 5;

    // Позже чтения текстовиков
    //_PI->WriteLoHook(0x4EEAF2, LoHook_AfterHDModInit);
}
