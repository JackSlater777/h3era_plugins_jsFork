#pragma once


namespace warlocksLab
{
    // type 144, subtype 9
    constexpr int WARLOCKS_LAB_OBJECT_SUBTYPE = 9;

    constexpr int WARLOCKS_LAB_MARKET_BUILDING = 5;

    constexpr LPCSTR dlgHint_key = "RMG.objectGeneration.%d.%d.text.dlgHint";
    constexpr LPCSTR dlgHintDealDone_key = "RMG.objectGeneration.%d.%d.text.dlgHintDealDone";
    constexpr LPCSTR dlgHintAvalObjs_key = "RMG.objectGeneration.%d.%d.text.dlgHintAvalObjs";
    constexpr LPCSTR dlgHintDeal_key = "RMG.objectGeneration.%d.%d.text.dlgHintDeal";
    constexpr LPCSTR dlgHintButtonDeal_key = "RMG.objectGeneration.%d.%d.text.dlgHintButtonDeal";

    struct H3MapItemWarlocksLab
    {
        // Собственных данных в mapItem->setup пока нет.
    };

    class WarlocksLabExtender final
        : public H3ActiveObject<H3MapItemWarlocksLab>
    {
    private:
        static WarlocksLabExtender* instance;

        void CreatePatches() override final;

        WarlocksLabExtender();

        BOOL VisitMapItem(
            H3Hero* currentHero,
            H3MapItem* mapItem,
            H3Position pos,
            BOOL isHuman
        ) const noexcept override final;

    public:
        static WarlocksLabExtender& Get();
    };
}
