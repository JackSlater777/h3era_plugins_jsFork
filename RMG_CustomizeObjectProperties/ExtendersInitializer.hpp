#include "pch.h"
#define OBJECT_EXTENDER_DECLARATOR(className, nameSpaceName)                                                           \
    namespace nameSpaceName                                                                                            \
    {                                                                                                                  \
    class className : public extender::ObjectExtender                                                                  \
    {                                                                                                                  \
      public:                                                                                                          \
        static className &className::Get();                                                                            \
    };                                                                                                                 \
    }
#define OBJECT_EXTENDER_GETTER(className, nameSpaceName) &nameSpaceName::className::Get()

OBJECT_EXTENDER_DECLARATOR(ColosseumOfTheMagiExtender, colosseumOfTheMagi)
OBJECT_EXTENDER_DECLARATOR(CreatureBanksExtender, cbanks)
OBJECT_EXTENDER_DECLARATOR(GazeboExtender, gazebo)
OBJECT_EXTENDER_DECLARATOR(ShrinesExtender, shrines)
OBJECT_EXTENDER_DECLARATOR(SpellMarketExtender, spellMarket)
OBJECT_EXTENDER_DECLARATOR(UniversityExtender, university)
OBJECT_EXTENDER_DECLARATOR(WarehousesExtender, warehouses)
OBJECT_EXTENDER_DECLARATOR(WateringPlaceExtender, wateringPlace)
OBJECT_EXTENDER_DECLARATOR(WoGObjectsExtender, wog)

// JS Objects
OBJECT_EXTENDER_DECLARATOR(AncientLampExtender, ancientLamp)
OBJECT_EXTENDER_DECLARATOR(DreamTeacherExtender, dreamTeacher)
OBJECT_EXTENDER_DECLARATOR(GraveExtender, grave)
OBJECT_EXTENDER_DECLARATOR(HermitsShackExtender, hermitsShack)
OBJECT_EXTENDER_DECLARATOR(HillFortExtender, hillFort)
OBJECT_EXTENDER_DECLARATOR(JunkmanExtender, junkman)
OBJECT_EXTENDER_DECLARATOR(MineralSpringExtender, mineralSpring)
OBJECT_EXTENDER_DECLARATOR(ObservatoryExtender, observatory)
OBJECT_EXTENDER_DECLARATOR(ProspectorExtender, prospector)
OBJECT_EXTENDER_DECLARATOR(SkeletonTransformerExtender, skeletonTransformer)
OBJECT_EXTENDER_DECLARATOR(TempleOfLoyaltyExtender, templeOfLoyalty)
OBJECT_EXTENDER_DECLARATOR(TownGateExtender, townGate)
OBJECT_EXTENDER_DECLARATOR(TrailblazerExtender, trailblazer)
OBJECT_EXTENDER_DECLARATOR(WarlocksLabExtender, warlocksLab)

namespace ExtendersInitializer
{

void InitObjectExtenders()
{

    if (auto mgr = extender::ObjectExtenderManager::Get())
    {
        extender::ObjectExtender *extendersList[] = {
            OBJECT_EXTENDER_GETTER(ColosseumOfTheMagiExtender, colosseumOfTheMagi),
            OBJECT_EXTENDER_GETTER(CreatureBanksExtender, cbanks), OBJECT_EXTENDER_GETTER(GazeboExtender, gazebo),
            OBJECT_EXTENDER_GETTER(ShrinesExtender, shrines), OBJECT_EXTENDER_GETTER(SpellMarketExtender, spellMarket),
            OBJECT_EXTENDER_GETTER(UniversityExtender, university),
            OBJECT_EXTENDER_GETTER(WarehousesExtender, warehouses),
            // OBJECT_EXTENDER_GETTER(WateringPlaceExtender, wateringPlace),
            OBJECT_EXTENDER_GETTER(WoGObjectsExtender, wog),
        
            // JS Objects
            OBJECT_EXTENDER_GETTER(AncientLampExtender, ancientLamp),
            OBJECT_EXTENDER_GETTER(DreamTeacherExtender, dreamTeacher),
            OBJECT_EXTENDER_GETTER(GraveExtender, grave),
            OBJECT_EXTENDER_GETTER(HermitsShackExtender, hermitsShack),
            OBJECT_EXTENDER_GETTER(HillFortExtender, hillFort),
            OBJECT_EXTENDER_GETTER(JunkmanExtender, junkman),
            OBJECT_EXTENDER_GETTER(MineralSpringExtender, mineralSpring),
            OBJECT_EXTENDER_GETTER(ObservatoryExtender, observatory),
            OBJECT_EXTENDER_GETTER(ProspectorExtender, prospector),
            OBJECT_EXTENDER_GETTER(SkeletonTransformerExtender, skeletonTransformer),
            OBJECT_EXTENDER_GETTER(TempleOfLoyaltyExtender, templeOfLoyalty),
            OBJECT_EXTENDER_GETTER(TownGateExtender, townGate),
            OBJECT_EXTENDER_GETTER(TrailblazerExtender, trailblazer),
            OBJECT_EXTENDER_GETTER(WarlocksLabExtender, warlocksLab),
            OBJECT_EXTENDER_GETTER(WateringPlaceExtender, wateringPlace)
        

        };

        constexpr size_t extendersCount =
            std::size(extendersList); // sizeof(extendersList) / sizeof(extender::ObjectExtender*);

        static_assert(extendersCount == 23, "Unexpected number of extenders");
        //! Get the extenders and initialize
        for (size_t i = 0; i < extendersCount; i++)
        {
            mgr->AddExtender(extendersList[i]);
        }
    }
}

} // namespace ExtendersInitializer
