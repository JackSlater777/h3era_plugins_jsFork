#pragma once

// Не стоит определять глобалки в .h без extern, иначе получишь 
// multiple definition или странные ODR-проблемы.


// JSON-ключи текстов объектов
extern LPCSTR const VISIT_MESSAGE;
extern LPCSTR const VISITED_MESSAGE;
extern LPCSTR const CANNOT_VISIT_MESSAGE;
extern LPCSTR const HINT_MESSAGE;


// Настройка HD-mod
extern bool skipMapMessage;



void Globals_Init();
