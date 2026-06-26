// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "../pch.h"



//case PC_POSITIVE_LUCK:
//{
//    if (vSubType > 0)
//    {
//        int len = vsprintf((#356 *) & ZprPo, "%d", vSubType);
//        v95 = 0;
//        std::string::_M_append_dispatch(&Dlg8ItemPo->Mes, (H3RmgTemplate*)len, 0, MinusOne);
//        v95 = -1;
//        H3String::Clear((H3String*)&ZprPo, 1);
//    }
//    else
//    {
//        H3String::Assign(&Dlg8ItemPo->Mes, NullString, strlen(NullString));
//    }
//
//    PicType = strlen(aIlck82_def);
//    if (H3String::SetLength(&Dlg8ItemPo->text, PicType, 1))
//    {
//        int len = PicType;
//        qmemcpy(Dlg8ItemPo->text.m_string, aIlck82_def, len);
//        H3String::_Eos(&Dlg8ItemPo->text, len);
//    }
//
//    Dlg8ItemPo->DefPicInd = 4;
//    goto LABEL_100;
//}



H3Dlg8Item* globalDlg8Item = nullptr;
H3Dlg8Item* globalDlg8Item2 = nullptr; // Под картинку мув спидов


void H3Dlg8Item_Clear(H3Dlg8Item* this_)
{
    THISCALL_2(VOID, 0x404130, &this_->text, 1); // H3String::Clear
    THISCALL_2(VOID, 0x404130, &this_->message, 1); // H3String::Clear
    this_->defIndex = -1;
    this_->picSubType = -1;
    this_->picType = ePictureCategories::NONE;
}

char* sub_1149DF0(char* a1, char* a2)
{
    int v4 = strlen(a2);
    int v5 = 0;
    if (v4 > 0)
    {
        int v6 = a2 - a1;
        do
        {
            char v7 = a1[v6];
            if (v7 == 10)
                break;
            if (v7 == 13)
                break;
            if (!v7)
                break;
            *a1 = v7;
            ++v5;
            ++a1;
        } while (v5 < v4);
    }
    a1[v5] = 0;
    return a1;
}

void sub_114A5F0(char* a1, int a2, int a3)
{
    H3AdventureManager* advMgr = P_AdventureManager->Get();
    advMgr->infoPanelType = H3AdventureManager::ePanel::RESOURCE_MESSAGE;
    advMgr->endTime = CDECL_0(INT32, 0x4F8970) + 7000; // timeGetTime()
    advMgr->bottomViewResource = a2;
    advMgr->bottomViewResourceQty = a3;
    THISCALL_3(void, 0x404180, advMgr->bottomViewText, a1, strlen(a1)); // H3String::Assign
    THISCALL_4(void, 0x415D40, advMgr, 1, 1, 1); // H3AdventureManager::UpdateInfoPanel
}

void __stdcall HiHook3_004F6C00(HiHook* h, char* message, int messageType, int posX, int posY,
    ePictureCategories type1, int subtype1,
    ePictureCategories type2, int subtype2,
    int par, int time2Show,
    ePictureCategories type3, int subtype3)
{
    if (subtype3 == -777)
    {
        if (type1 == ePictureCategories::POSITIVE_LUCK && subtype1 == 1 && type2 == ePictureCategories::NONE && !subtype2)// Минеральный источник
        {
            H3Dlg8Item_Clear(globalDlg8Item);
            H3Dlg8Item_Clear(globalDlg8Item2);
            THISCALL_3(void, 0x4F5540, globalDlg8Item, ePictureCategories::POSITIVE_LUCK, 1); // H3Dlg8Item::Get
            THISCALL_3(void, 0x404180, &globalDlg8Item->message, "+1", 2); // H3String::Assign
            globalDlg8Item2->picType = ePictureCategories(77777);
            THISCALL_3(void, 0x404180, &globalDlg8Item2->text, "PMOVE.def", 9); // H3String::Assign
            globalDlg8Item2->defIndex = 0;
            THISCALL_3(void, 0x404180, &globalDlg8Item2->message, "+600", 4); // H3String::Assign
            char* v19 = CDECL_1(char*, 0x617492, strlen(message) + 1); // new
            char* v20 = sub_1149DF0(v19, message);
            sub_114A5F0(v20, 1000, 1);
            return CDECL_1(void, 0x60B0F0, v20); // MemFree
        }
        //v15 = -770;
    }

    return FASTCALL_12(void, h->GetDefaultFunc(), message, messageType, posX, posY, type1, subtype1,
        type2, subtype2, par, time2Show, type3, subtype3);
}


void HdModPatches()
{
    globalDlg8Item = new H3Dlg8Item();
    globalDlg8Item2 = new H3Dlg8Item(); 


    _PI->WriteHiHook(0x4F6C00, SPLICE_, EXTENDED_, FASTCALL_, HiHook3_004F6C00);






    //// RMC hints
    //_PI->WriteLoHook(0x41391C, LoHook_AdvMgr_GetObjectRightClickText);
    //// mouseover hints
    //_PI->WriteLoHook(0x40B158, LoHook_AdvMgr_GetObjectCommand);


    //// Stables - player flags
    //_PI->WriteLoHook(0x4A5D18, LoHook_004A5D18);

    //// Refugee camp - player flags
    //_PI->WriteHiHook(0x4A4270, SPLICE_, EXTENDED_, THISCALL_, HiHook_004A4270);
}
