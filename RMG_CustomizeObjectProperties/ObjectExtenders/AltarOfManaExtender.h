#pragma once


namespace altarOfMana
{
    // type 146, subtype 2
    constexpr int ALTAR_OF_MANA_OBJECT_SUBTYPE = 2;

    constexpr LPCSTR dlgHint_key = "RMG.objectGeneration.%d.%d.text.dlgHint";
    constexpr LPCSTR dlgHintDealDone_key = "RMG.objectGeneration.%d.%d.text.dlgHintDealDone";
    constexpr LPCSTR dlgHintAvalObjs_key = "RMG.objectGeneration.%d.%d.text.dlgHintAvalObjs";
    constexpr LPCSTR dlgHintDeal_key = "RMG.objectGeneration.%d.%d.text.dlgHintDeal";
    constexpr LPCSTR dlgHintButtonDeal_key = "RMG.objectGeneration.%d.%d.text.dlgHintButtonDeal";

    struct H3MapItemAltarOfMana
    {
        // Собственных данных в mapItem->setup пока нет.
    };

    class AltarOfManaExtender final
        : public H3ActiveObject<H3MapItemAltarOfMana>
    {
    private:
        static AltarOfManaExtender* instance;

        void CreatePatches() override final;

        AltarOfManaExtender();

        BOOL VisitMapItem(
            H3Hero* currentHero,
            H3MapItem* mapItem,
            H3Position pos,
            BOOL isHuman
        ) const noexcept override final;

    public:
        static AltarOfManaExtender& Get();
    };
}
