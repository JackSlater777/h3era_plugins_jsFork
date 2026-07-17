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

OBJECT_EXTENDER_DECLARATOR(CreatureBanksExtender, cbanks)
OBJECT_EXTENDER_DECLARATOR(ShrinesExtender, shrines)
OBJECT_EXTENDER_DECLARATOR(SpellMarketExtender, spellMarket)
OBJECT_EXTENDER_DECLARATOR(UniversityExtender, university)
OBJECT_EXTENDER_DECLARATOR(WarehousesExtender, warehouses)
OBJECT_EXTENDER_DECLARATOR(WoGObjectsExtender, wog)

// JS Objects
// 141
OBJECT_EXTENDER_DECLARATOR(DreamTeacherExtender, dreamTeacher) // 0
OBJECT_EXTENDER_DECLARATOR(GraveExtender, grave) // 1 - Надо переместить в тип 212

// 144
OBJECT_EXTENDER_DECLARATOR(TempleOfLoyaltyExtender, templeOfLoyalty) // 0
OBJECT_EXTENDER_DECLARATOR(SkeletonTransformerExtender, skeletonTransformer) // 1
OBJECT_EXTENDER_DECLARATOR(ColosseumOfTheMagiExtender, colosseumOfTheMagi) // 2
OBJECT_EXTENDER_DECLARATOR(WateringPlaceExtender, wateringPlace) // 3
OBJECT_EXTENDER_DECLARATOR(MineralSpringExtender, mineralSpring) // 4
OBJECT_EXTENDER_DECLARATOR(HermitsShackExtender, hermitsShack) // 5
OBJECT_EXTENDER_DECLARATOR(GazeboExtender, gazebo) // 6
OBJECT_EXTENDER_DECLARATOR(JunkmanExtender, junkman) // 7
OBJECT_EXTENDER_DECLARATOR(WarlocksLabExtender, warlocksLab) // 9
OBJECT_EXTENDER_DECLARATOR(ProspectorExtender, prospector) // 10
OBJECT_EXTENDER_DECLARATOR(TrailblazerExtender, trailblazer) // 11

// 145
OBJECT_EXTENDER_DECLARATOR(AncientLampExtender, ancientLamp) // 0
OBJECT_EXTENDER_DECLARATOR(SeaBarrelExtender, seaBarrel) // 1
OBJECT_EXTENDER_DECLARATOR(JetsamExtender, jetsam) // 2
OBJECT_EXTENDER_DECLARATOR(VialOfManaExtender, vialOfMana) // 3

// 146
OBJECT_EXTENDER_DECLARATOR(SeafaringAcademyExtender, seafaringAcademy) // 0
OBJECT_EXTENDER_DECLARATOR(ObservatoryExtender, observatory) // 1
OBJECT_EXTENDER_DECLARATOR(AltarOfManaExtender, altarOfMana) // 2
OBJECT_EXTENDER_DECLARATOR(TownGateExtender, townGate) // 3

// rest
OBJECT_EXTENDER_DECLARATOR(HillFortExtender, hillFort) // type 35, subtype 1



namespace ExtendersInitializer
{

void InitObjectExtenders()
{

    if (auto mgr = extender::ObjectExtenderManager::Get())
    {
        extender::ObjectExtender *extendersList[] = {
            OBJECT_EXTENDER_GETTER(CreatureBanksExtender, cbanks),
            OBJECT_EXTENDER_GETTER(ShrinesExtender, shrines),
            OBJECT_EXTENDER_GETTER(SpellMarketExtender, spellMarket),
            OBJECT_EXTENDER_GETTER(UniversityExtender, university),
            OBJECT_EXTENDER_GETTER(WarehousesExtender, warehouses),
            OBJECT_EXTENDER_GETTER(WoGObjectsExtender, wog),
        
            // JS Objects
            // 141
            OBJECT_EXTENDER_GETTER(DreamTeacherExtender, dreamTeacher), // 0
            OBJECT_EXTENDER_GETTER(GraveExtender, grave), // 1 - Надо переместить в 212

            // 144
            OBJECT_EXTENDER_GETTER(TempleOfLoyaltyExtender, templeOfLoyalty), // 0
            OBJECT_EXTENDER_GETTER(SkeletonTransformerExtender, skeletonTransformer), // 1
            OBJECT_EXTENDER_GETTER(ColosseumOfTheMagiExtender, colosseumOfTheMagi), // 2
            OBJECT_EXTENDER_GETTER(WateringPlaceExtender, wateringPlace), // 3
            OBJECT_EXTENDER_GETTER(MineralSpringExtender, mineralSpring), // 4
            OBJECT_EXTENDER_GETTER(HermitsShackExtender, hermitsShack), // 5
            OBJECT_EXTENDER_GETTER(GazeboExtender, gazebo), // 6
            OBJECT_EXTENDER_GETTER(JunkmanExtender, junkman), // 7
            OBJECT_EXTENDER_GETTER(WarlocksLabExtender, warlocksLab), // 9
            OBJECT_EXTENDER_GETTER(ProspectorExtender, prospector), // 10
            OBJECT_EXTENDER_GETTER(TrailblazerExtender, trailblazer), // 11

            // 145
            OBJECT_EXTENDER_GETTER(AncientLampExtender, ancientLamp), // 0
            OBJECT_EXTENDER_GETTER(SeaBarrelExtender, seaBarrel), // 1
            OBJECT_EXTENDER_GETTER(JetsamExtender, jetsam), // 2
            OBJECT_EXTENDER_GETTER(VialOfManaExtender, vialOfMana), // 3

            // 146
            OBJECT_EXTENDER_GETTER(SeafaringAcademyExtender, seafaringAcademy), // 0
            OBJECT_EXTENDER_GETTER(ObservatoryExtender, observatory), // 1
            OBJECT_EXTENDER_GETTER(AltarOfManaExtender, altarOfMana), // 2
            OBJECT_EXTENDER_GETTER(TownGateExtender, townGate), // 3

            // rest
            OBJECT_EXTENDER_GETTER(HillFortExtender, hillFort), // type 35, subtype 1
        };

        constexpr size_t extendersCount =
            std::size(extendersList); // sizeof(extendersList) / sizeof(extender::ObjectExtender*);

        static_assert(extendersCount == 28, "Unexpected number of extenders");
        //! Get the extenders and initialize
        for (size_t i = 0; i < extendersCount; i++)
        {
            mgr->AddExtender(extendersList[i]);
        }
    }
}

} // namespace ExtendersInitializer
