#include "BattleSetup.hpp"
#include "Collision.hpp"

#include <new>

namespace th105 {

namespace {

// Constructor views retain only the observed member ABI: ECX receives the
// freshly allocated derived object and the sole stack argument is a Side.
// They intentionally do not assert original C++ class spellings or layouts.
#define DECLARE_FIGHTER_CTOR_VIEW(name) \
    struct name { explicit name(const MatchSetup::Side *setup); }

DECLARE_FIGHTER_CTOR_VIEW(ReimuFighterCtorView);
DECLARE_FIGHTER_CTOR_VIEW(MarisaFighterCtorView);
DECLARE_FIGHTER_CTOR_VIEW(SakuyaFighterCtorView);
DECLARE_FIGHTER_CTOR_VIEW(AliceFighterCtorView);
DECLARE_FIGHTER_CTOR_VIEW(PatchouliFighterCtorView);
DECLARE_FIGHTER_CTOR_VIEW(YoumuFighterCtorView);
DECLARE_FIGHTER_CTOR_VIEW(RemiliaFighterCtorView);
DECLARE_FIGHTER_CTOR_VIEW(YuyukoFighterCtorView);
DECLARE_FIGHTER_CTOR_VIEW(YukariFighterCtorView);
DECLARE_FIGHTER_CTOR_VIEW(SuikaFighterCtorView);
DECLARE_FIGHTER_CTOR_VIEW(UdongeFighterCtorView);
DECLARE_FIGHTER_CTOR_VIEW(AyaFighterCtorView);
DECLARE_FIGHTER_CTOR_VIEW(KomachiFighterCtorView);
DECLARE_FIGHTER_CTOR_VIEW(IkuFighterCtorView);
DECLARE_FIGHTER_CTOR_VIEW(TenshiFighterCtorView);

#undef DECLARE_FIGHTER_CTOR_VIEW

} // namespace

int BattleSlotState::create_fighter_for_slot(
    int slot,
    const MatchSetup::Side *setup)
{
    Fighter *fighter = 0;

    switch (setup->character_key_00) {
    case 0: {
        void *storage = operator new(0x7d0);
        if (storage) fighter = reinterpret_cast<Fighter *>(
            new (storage) ReimuFighterCtorView(setup));
        break;
    }
    case 1: {
        void *storage = operator new(0x7b4);
        if (storage) fighter = reinterpret_cast<Fighter *>(
            new (storage) MarisaFighterCtorView(setup));
        break;
    }
    case 2: {
        void *storage = operator new(0x7a8);
        if (storage) fighter = reinterpret_cast<Fighter *>(
            new (storage) SakuyaFighterCtorView(setup));
        break;
    }
    case 3: {
        void *storage = operator new(0x7d8);
        if (storage) fighter = reinterpret_cast<Fighter *>(
            new (storage) AliceFighterCtorView(setup));
        break;
    }
    case 4: {
        void *storage = operator new(0x7b8);
        if (storage) fighter = reinterpret_cast<Fighter *>(
            new (storage) PatchouliFighterCtorView(setup));
        break;
    }
    case 5: {
        void *storage = operator new(0x800);
        if (storage) fighter = reinterpret_cast<Fighter *>(
            new (storage) YoumuFighterCtorView(setup));
        break;
    }
    case 6: {
        void *storage = operator new(0x7a4);
        if (storage) fighter = reinterpret_cast<Fighter *>(
            new (storage) RemiliaFighterCtorView(setup));
        break;
    }
    case 7: {
        void *storage = operator new(0x7b4);
        if (storage) fighter = reinterpret_cast<Fighter *>(
            new (storage) YuyukoFighterCtorView(setup));
        break;
    }
    case 8: {
        void *storage = operator new(0x7cc);
        if (storage) fighter = reinterpret_cast<Fighter *>(
            new (storage) YukariFighterCtorView(setup));
        break;
    }
    case 9: {
        void *storage = operator new(0x7a8);
        if (storage) fighter = reinterpret_cast<Fighter *>(
            new (storage) SuikaFighterCtorView(setup));
        break;
    }
    case 10: {
        void *storage = operator new(0x7bc);
        if (storage) fighter = reinterpret_cast<Fighter *>(
            new (storage) UdongeFighterCtorView(setup));
        break;
    }
    case 11: {
        void *storage = operator new(0x7a4);
        if (storage) fighter = reinterpret_cast<Fighter *>(
            new (storage) AyaFighterCtorView(setup));
        break;
    }
    case 12: {
        void *storage = operator new(0x7ac);
        if (storage) fighter = reinterpret_cast<Fighter *>(
            new (storage) KomachiFighterCtorView(setup));
        break;
    }
    case 13: {
        void *storage = operator new(0x7b8);
        if (storage) fighter = reinterpret_cast<Fighter *>(
            new (storage) IkuFighterCtorView(setup));
        break;
    }
    case 14: {
        void *storage = operator new(0x844);
        if (storage) fighter = reinterpret_cast<Fighter *>(
            new (storage) TenshiFighterCtorView(setup));
        break;
    }
    }

    fighter->initialize_fighter_spell_resources();
    slot_characters[slot] = reinterpret_cast<Character *>(fighter);
    return slot;
}

} // namespace th105
