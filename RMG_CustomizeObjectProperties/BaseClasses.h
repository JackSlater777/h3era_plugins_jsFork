#pragma once
//#include "ObjectExtender.h"


struct H3PickupableObject : public extender::ObjectExtender
{
    static constexpr LPCSTR empty_key = "RMG.objectGeneration.%d.%d.text.empty";

    using ObjectExtender::ObjectExtender;

    H3String GetEmptyMessage() const
    {
        return GetStringMessage(empty_key);
    }
};



//struct H3ActiveObject : public extender::ObjectExtender
//{
//    LPCSTR name = nullptr;
//    LPCSTR visitingMessage = nullptr;
//
//    static constexpr LPCSTR name_key = "RMG.objectGeneration.%d.%d.name";
//
//    LPCSTR GetString(LPCSTR key)
//    {
//        bool readSuccess = false;
//        sprintf(h3_TextBuffer, key, this->objectType, this->objectSubtype);
//        LPCSTR tempStr = EraJS::read(h3_TextBuffer, readSuccess);
//        if (!readSuccess)
//        {
//            sprintf(h3_TextBuffer,
//                "Couldnot find a string for object type %d, subtype %d !",
//                this->objectType, this->objectSubtype);
//            LPCSTR tempStr = h3_TextBuffer;
//            H3Messagebox::Show(tempStr);
//        }
//        return tempStr;
//    }
//
//    LPCSTR GetName()
//    {
//        return GetString(name_key);
//    }
//
//    LPCSTR GetVisitingMessage()
//    {
//        return GetString(visit_key);
//    }
//};
