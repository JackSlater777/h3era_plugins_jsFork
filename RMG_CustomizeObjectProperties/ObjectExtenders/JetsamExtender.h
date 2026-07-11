#pragma once

namespace jetsam
{
// 145
constexpr int JETSAM_OBJECT_SUBTYPE = 2;

constexpr LPCSTR visit_1state_key = "RMG.objectGeneration.%d.%d.text.visit1state";
constexpr LPCSTR visit_2state_key = "RMG.objectGeneration.%d.%d.text.visit2state";
constexpr LPCSTR visit_3state_key = "RMG.objectGeneration.%d.%d.text.visit3state";


struct H3MapItemJetsam
{
    INT32 state;

    static inline H3MapItemJetsam* GetJetsam(H3MapItem* mapItem) noexcept;
};

class JetsamExtender : public H3PickupableObject
{
    static JetsamExtender* instance;

    JetsamExtender();

    virtual ~JetsamExtender();

  private:
    virtual void CreatePatches() override;
    virtual BOOL SetHintInH3TextBuffer(H3MapItem* mapItem, const H3Hero* currentHero, const int playerId,
        BOOL isRightClick) const noexcept override final;
    virtual BOOL InitNewGameMapItemSetup(H3MapItem *mapItem) const noexcept override final;
    virtual BOOL VisitMapItem(H3Hero *currentHero, H3MapItem *mapItem, const H3Position pos,
                              const BOOL isHuman) const noexcept override final;
    virtual BOOL SetAiMapItemWeight(H3MapItem *mapItem, H3Hero *currentHero, const H3Player *activePlayer,
                                    int &aiMapItemWeight, int* moveDistance, const H3Position pos) const noexcept override final;
    virtual H3RmgObjectGenerator *CreateRMGObjectGen(const RMGObjectInfo &objectInfo) const noexcept override final;

  public:
    static JetsamExtender&Get();


    H3String GetEmptyMessage() const
    {
        return GetStringMessage(empty_key);
    }

    H3String GetVisitingState1Message() const
    {
        return GetStringMessage(visit_1state_key);
    }

    H3String GetVisitingState2Message() const
    {
        return GetStringMessage(visit_2state_key);
    }

    H3String GetVisitingState3Message() const
    {
        return GetStringMessage(visit_3state_key);
    }
};

}
