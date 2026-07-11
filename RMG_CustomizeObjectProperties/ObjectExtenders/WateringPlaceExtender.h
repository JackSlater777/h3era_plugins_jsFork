#pragma once

namespace wateringPlace
{
// 144
constexpr int WATERING_PLACE_OBJECT_SUBTYPE = 3;
constexpr int MOVE_POINTS_GIVEN = 1000;

struct H3MapItemWateringPlace
{
    static constexpr LPCSTR ErmVariableFormat = "wateringPlace_%d";

    static inline H3MapItemWateringPlace* GetWateringPlace(H3MapItem* mapItem) noexcept;

    static inline BOOL IsVisitedByHero(const H3Hero *hero) noexcept;
    static void SetAsVisited(H3Hero* hero) noexcept;
    static void SetAsNotVisited(H3Hero* hero) noexcept;
};

class WateringPlaceExtender : public extender::ObjectExtender
{
    static WateringPlaceExtender *instance;

    WateringPlaceExtender();

    virtual ~WateringPlaceExtender();

  private:
    virtual void CreatePatches();
    virtual BOOL SetHintInH3TextBuffer(H3MapItem *mapItem, const H3Hero *currentHero, const int interactPlayerId,
                                       const BOOL isRightClick) const noexcept override final;
    virtual BOOL VisitMapItem(H3Hero *currentHero, H3MapItem *mapItem, const H3Position pos,
                              const BOOL isHuman) const noexcept override final;
    virtual BOOL SetAiMapItemWeight(H3MapItem *mapItem, H3Hero *currentHero, const H3Player *activePlayer,
                                    int &aiMapItemWeight, int *moveDistance,
                                    const H3Position pos) const noexcept override final;
    virtual H3RmgObjectGenerator *CreateRMGObjectGen(const RMGObjectInfo &objectInfo) const noexcept override final;

  public:
    static WateringPlaceExtender &Get();
};

}
