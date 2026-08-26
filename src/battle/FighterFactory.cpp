#include "BattleSetup.hpp"
#include "Collision.hpp"

#include <new>

namespace th105 {

namespace {

// Constructor views retain the target-proved allocation extent and observed
// member ABI: ECX receives the freshly allocated derived object and the sole
// stack argument is a Side. They intentionally do not claim unobserved fields
// or original class spellings; the physical extent is required so ordinary
// typed new expressions reproduce the shipped new-expression lifetime.
#define DECLARE_FIGHTER_CTOR_VIEW(name, extent) \
    struct name { \
        unsigned char storage_00[extent]; \
        explicit name(const MatchSetup::Side *setup); \
    }

DECLARE_FIGHTER_CTOR_VIEW(ReimuFighterCtorView, 0x7d0);
DECLARE_FIGHTER_CTOR_VIEW(MarisaFighterCtorView, 0x7b4);
DECLARE_FIGHTER_CTOR_VIEW(SakuyaFighterCtorView, 0x7a8);
DECLARE_FIGHTER_CTOR_VIEW(AliceFighterCtorView, 0x7d8);
DECLARE_FIGHTER_CTOR_VIEW(PatchouliFighterCtorView, 0x7b8);
DECLARE_FIGHTER_CTOR_VIEW(YoumuFighterCtorView, 0x800);
DECLARE_FIGHTER_CTOR_VIEW(RemiliaFighterCtorView, 0x7a4);
DECLARE_FIGHTER_CTOR_VIEW(YuyukoFighterCtorView, 0x7b4);
DECLARE_FIGHTER_CTOR_VIEW(YukariFighterCtorView, 0x7cc);
DECLARE_FIGHTER_CTOR_VIEW(SuikaFighterCtorView, 0x7a8);
DECLARE_FIGHTER_CTOR_VIEW(UdongeFighterCtorView, 0x7bc);
DECLARE_FIGHTER_CTOR_VIEW(AyaFighterCtorView, 0x7a4);
DECLARE_FIGHTER_CTOR_VIEW(KomachiFighterCtorView, 0x7ac);
DECLARE_FIGHTER_CTOR_VIEW(IkuFighterCtorView, 0x7b8);
DECLARE_FIGHTER_CTOR_VIEW(TenshiFighterCtorView, 0x844);

#undef DECLARE_FIGHTER_CTOR_VIEW

} // namespace

int BattleSlotState::create_fighter_for_slot(
    int slot,
    const MatchSetup::Side *setup)
{
    Fighter *fighter = 0;

    switch (setup->character_key_00) {
    case 0: {
        fighter = reinterpret_cast<Fighter *>(new ReimuFighterCtorView(setup));
        break;
    }
    case 1: {
        fighter = reinterpret_cast<Fighter *>(new MarisaFighterCtorView(setup));
        break;
    }
    case 2: {
        fighter = reinterpret_cast<Fighter *>(new SakuyaFighterCtorView(setup));
        break;
    }
    case 5: {
        fighter = reinterpret_cast<Fighter *>(new YoumuFighterCtorView(setup));
        break;
    }
    case 3: {
        fighter = reinterpret_cast<Fighter *>(new AliceFighterCtorView(setup));
        break;
    }
    case 4: {
        fighter = reinterpret_cast<Fighter *>(new PatchouliFighterCtorView(setup));
        break;
    }
    case 6: {
        fighter = reinterpret_cast<Fighter *>(new RemiliaFighterCtorView(setup));
        break;
    }
    case 7: {
        fighter = reinterpret_cast<Fighter *>(new YuyukoFighterCtorView(setup));
        break;
    }
    case 8: {
        fighter = reinterpret_cast<Fighter *>(new YukariFighterCtorView(setup));
        break;
    }
    case 9: {
        fighter = reinterpret_cast<Fighter *>(new SuikaFighterCtorView(setup));
        break;
    }
    case 11: {
        fighter = reinterpret_cast<Fighter *>(new AyaFighterCtorView(setup));
        break;
    }
    case 10: {
        fighter = reinterpret_cast<Fighter *>(new UdongeFighterCtorView(setup));
        break;
    }
    case 12: {
        fighter = reinterpret_cast<Fighter *>(new KomachiFighterCtorView(setup));
        break;
    }
    case 13: {
        fighter = reinterpret_cast<Fighter *>(new IkuFighterCtorView(setup));
        break;
    }
    case 14: {
        fighter = reinterpret_cast<Fighter *>(new TenshiFighterCtorView(setup));
        break;
    }
    }

    fighter->initialize_fighter_spell_resources();
    slot_characters[slot] = reinterpret_cast<Character *>(fighter);
    return slot;
}

} // namespace th105
