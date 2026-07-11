#pragma once

namespace seaBarrel
{
// 145
constexpr int SEA_BARREL_OBJECT_SUBTYPE = 1;

struct H3MapItemSeaBarrel
{
    INT16 resType;
    INT16 resQty;

    static inline H3MapItemSeaBarrel* GetSeaBarrel(H3MapItem* mapItem) noexcept;
};

class SeaBarrelExtender : public H3PickupableObject
{
    static SeaBarrelExtender* instance;

    SeaBarrelExtender();

    virtual ~SeaBarrelExtender();

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
    static SeaBarrelExtender&Get();
};

}
